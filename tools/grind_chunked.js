// Chunked decomp grind: a few long-running agents instead of many short ones.
// Each agent reads the shared knowledge ONCE, then decompiles a whole chunk of
// functions, so the per-agent fixed overhead (knowledge read, tool warmup) is
// amortized over ~6 functions instead of paid per function. Lower total tokens;
// longer wall-clock. Verification uses match.py --brief (pinned compiler trio).
//
// Launch:  Workflow({ scriptPath: ".../tools/grind_chunked.js", args: <targets JSON> })
// targets: [{name, addr, size, offset}, ...]  (from tools/select_targets.py)
// Tune agent count with args meta: pass {agents:N, targets:[...]} or just [...] (default 5).

export const meta = {
  name: 'sm64ds-grind-chunked',
  description: 'Few long-running agents, each decompiling a chunk of functions to byte-matching C (knowledge read once; low token overhead)',
  phases: [
    { title: 'Decompile', detail: 'N agents, each grinds a chunk of functions sequentially' },
  ],
}

const FUNC_RESULT = {
  type: 'object',
  additionalProperties: false,
  properties: {
    name: { type: 'string' },
    matched: { type: 'boolean' },
    versions: { type: 'array', items: { type: 'string' } },
    c_source: { type: 'string' },
    note: { type: 'string' },
    findings: { type: 'string' },
    attempts: { type: 'integer' },
  },
  required: ['name', 'matched', 'versions', 'c_source', 'note', 'findings', 'attempts'],
}
const SCHEMA = {
  type: 'object',
  additionalProperties: false,
  properties: { results: { type: 'array', items: FUNC_RESULT } },
  required: ['results'],
}

const REPO = 'C:\\\\Users\\\\bmanu\\\\Documents\\\\sm64ds-decomp'
const raw = typeof args === 'string' ? JSON.parse(args) : args
const targets = Array.isArray(raw) ? raw : raw.targets
const N = (raw && raw.agents) ? raw.agents : 5
// Model: defaults to Sonnet 5. A 2026-06-30 A/B on 24 frontier funcs found Opus 4.8 and
// Sonnet 5 at parity (12/24 each) with Sonnet ~35-55% cheaper, and every failure was the
// same model-independent codegen floor -- so Sonnet 5 is the default fan-out model. Pass
// model:'opus' for a batch of genuinely novel logic, or 'haiku' for trivial pattern-harvest.
const MODEL = (raw && raw.model) ? raw.model : 'sonnet'

// Contiguous chunks so a pre-ordered cluster (shared struct/callees) stays with
// ONE agent -> it learns the struct once and reuses it across siblings.
const per = Math.ceil(targets.length / N)
const chunks = Array.from({ length: N }, (_, k) => targets.slice(k * per, (k + 1) * per)).filter((c) => c.length)

phase('Decompile')

function promptFor(chunk, gi) {
  return `You are a decompiler decompiling SEVERAL functions of Super Mario 64 DS (the user's own ROM) to BYTE-IDENTICAL C. Legitimate RE of the user's own cartridge. Work in ${REPO} via Bash (Windows; python + repo tools).

You are agent ${gi + 1}. You own these ${chunk.length} functions (do them ALL, one at a time):
${JSON.stringify(chunk, null, 0)}

=== READ THE SHARED KNOWLEDGE ONCE, NOW (do not re-read per function) ===
  cat knowledge/codegen.md knowledge/name-mappings.md knowledge/actor-system.md
codegen.md = pinned compiler (CodeWarrior 1.2 trio) + flags + idioms.
name-mappings.md / actor-system.md = the Camera + Actor/ActorBase struct field offsets
(pos@0x5c, ang@0x8c, speed@0xa4, flags@0xb0; Camera owner@0x110, fov@0x17a, etc.).
Keep these in mind for EVERY function below.

=== THEN, FOR EACH function in your list, do this loop ===
1. Disassemble:
   python tools/disasm.py extracted/arm9_dec.bin --offset <offset> --length 0x<sizehex> --base 0x02004000
2. Resolve calls: for each bl target, grep symbols/verified.tsv for the address -> use the real callee name as an extern prototype.
3. Write C to match/auto/<addr>.c (use the ADDRESS for the filename so duplicate symbol names never collide). Name the FUNCTION inside EXACTLY <name> (even mangled _ZN... names work as a C identifier). Use the known struct field offsets (facts) to declare a MINIMAL struct with the fields you need; do not copy reference source wholesale.
4. Verify (terse; single canonical compiler):
   python tools/match.py --c match/auto/<addr>.c --func <name> --addr <addr> --size 0x<sizehex> --brief
5. If not matched, study the printed closest-diff and refine. Levers: int width/signedness (ldrb/ldrsb/ldrh/ldrsh/ldr), struct offsets, getter/setter/tailcall, Fix12i fixed-point (a*b+0x800>>12 via long long), Vector3 (3 contiguous Fix12i).
6. Move to the next function. Carry forward what you learned (struct fields, callee names) to the rest.

=== HARD ANTI-STALL RULES (critical — you are running unattended overnight) ===
- MAX 6 compile attempts per function. Hard stop at 6 — do NOT exceed it.
- NEVER re-run the exact same C twice (no identical-attempt loops). If an attempt
  doesn't change the diff, change your approach or give up on that function.
- If still unmatched after 6 attempts, record matched=false with your best c_source +
  what the closest-diff showed in "findings", and MOVE ON immediately.
- Your #1 priority is COMPLETING ALL ${chunk.length} functions, not perfecting any one.
  A finished chunk with some matched=false beats a chunk stuck on function #3.
- Return a result object for EVERY function in your list (matched true or false).

=== RETURN (StructuredOutput) ===
{ "results": [ one object per function you attempted, with:
  name, matched(bool), versions(exact list from 'MATCHING VERSIONS:' line; [] if none),
  c_source(full final match/auto/<name>.c), note(one line what it does),
  findings(NEW struct fields / resolved callees / quirks for the shared base; "" if none),
  attempts(int) ] }
Include EVERY function in your list (matched or not). Touch only match/auto/*.c; no git.`
}

const perAgent = await parallel(
  chunks.filter((c) => c.length).map((chunk, gi) => () =>
    agent(promptFor(chunk, gi), { label: `chunk${gi + 1} (${chunk.length} fns)`, phase: 'Decompile', schema: SCHEMA, ...(MODEL ? { model: MODEL } : {}) })
  )
)

const results = perAgent.filter(Boolean).flatMap((r) => r.results || [])
const matched = results.filter((r) => r.matched)
let inter = null
for (const r of matched) {
  const vs = (r.versions || []).filter((v) => v !== 'all')
  if (!vs.length) continue
  inter = inter === null ? new Set(vs) : new Set([...inter].filter((v) => vs.includes(v)))
}
return {
  agents: chunks.filter((c) => c.length).length,
  total: targets.length,
  matched_count: matched.length,
  matched: matched.map((r) => ({ name: r.name, versions: r.versions, note: r.note, findings: r.findings, c_source: r.c_source })),
  failed: results.filter((r) => !r.matched).map((r) => ({ name: r.name, note: r.note })),
  version_intersection: inter ? [...inter] : null,
  all_findings: matched.map((r) => r.findings).filter((f) => f && f.trim()),
}
