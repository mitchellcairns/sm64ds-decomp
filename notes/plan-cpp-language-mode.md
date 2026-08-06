# Plan: closing the C/C++ language-mode gap (issue #821)

**Status:** proposal.
**Provoked by:** [#821 "This is 100% fakematch"](https://github.com/tangosdev/sm64ds-decomp/issues/821).
**Prerequisite reading:** `notes/runbook-type-reconstruction.md` (the ladder, the safety
model, the dead ends). This plan schedules that runbook; it does not replace it.

---

## 1. What the issue claims, and what survives checking

Every number below is reproducible on a clean tree at `7b293af4`. Commands in §9.

| # | Claim | Verdict | Evidence |
|---|---|---|---|
| 1 | Name mangling proves C++, ignored | **Holds, partially** | 1,044 of 2,515 mangled-symbol files (41%) have a `.c` extension: the mangled name is spelled by hand and the file builds in C mode |
| 2 | Incorrect return types | **Holds** | `int _ZN10FaderColorD1Ev(int *self)` — the ARM C++ dtor ABI returns `this`, so this is `FaderColor* FaderColor::~FaderColor()` |
| 3 | Forced register usage | **Holds, smaller than stated** | 14 files carry inline `asm`; 67 name a codegen-forcing hack in a comment; 1,246 use `long long` (an unknown subset legitimately) |
| 4 | Incorrect argument types | **Holds** | `int *self` for `FaderColor*`; and per the runbook, 27% of local declarations contradict each other |
| 5 | Using a C compiler for C++ | **Holds in substance** | mwccarm does compile both, so "wrong compiler" is imprecise — but 8,125 files build as C and 1,044 of them define a C++ symbol. The mode is wrong where it matters |

What does **not** survive: *"every single function is fake matched."* The byte gate is
real and it is honest. 1,059 files already carry real C++ definitions, 79 of them real
destructors, and enrolled functions reproduce the ROM byte-for-byte. The rhetorical
core still lands, though, and this repo already said so first —
`notes/runbook-type-reconstruction.md` §1: **"The build is correct; the description is
not."** The types are wrong as *documentation*, not as *machinery*.

That distinction is the whole plan. Nothing below changes a single byte of output. It
changes what the source *claims*, and the byte gate is what proves each step didn't lie.

## 2. The measured backlog

**1,044 mangled-symbol files still in C mode**, by symbol kind:

| kind | count | migration status |
|---|---|---|
| plain methods | 579 | **proven** — 1,059 real method/namespace definitions landed |
| `D0` deleting dtor | 246 | **proven** — 15 landed |
| `D1` complete dtor | 170 | **proven** — 90 landed |
| `D2` base dtor | 15 | **proven** — 2 landed |
| `C1` complete ctor | 28 | **UNPROVEN — 0 landed** |
| `C2` base ctor | 6 | **UNPROVEN — 0 landed** |

Of the 579 methods, **36 carry `Fix12<int>` by value** and are blocked by the dead end in
runbook §7 (mwccarm homes `r0-r3` to the stack for any by-value class parameter, +0x14,
re-measured across all 25 sweep versions and every optimization level). They are not
work; they are a documented exclusion.

"Unproven" for constructors is literal. All five `C1` files that already carry a `.cpp`
extension still hand-spell the mangled symbol — `extern "C" void*
_ZN5ActorC1Ev(struct Actor *self)` — and `src/_ZN9ActorBaseC1Ev.cpp` uses `asm`. Renaming
a file to `.cpp` was never the same thing as migrating it.

**A second, quieter backlog.** The proven destructor pattern often bought its bytes with a
new lie. `src/_ZN6CannonD1Ev.cpp` is a genuine `Cannon::~Cannon()`, but it re-declares its
own base locally rather than including the real header:

```cpp
struct Actor { char pad[0xd0]; virtual ~Actor(); };
```

Tree-wide: **1,426** `.cpp` files define a struct or class body locally, **770** do so
while including no project header at all, and **690** use a `char pad[0x..]` shadow
layout. A shadow base is invisible to `tools/affected_src.py`, so a later header fix
silently misses it, and two files can disagree about the same class forever. This is the
same disease as the declaration debt in `notes/declaration-centralization.md` (**43,931**
`extern` lines across **8,950** files at `7b293af4`, 27% mutually inconsistent,
`ModelAnim::SetAnim` under 123 spellings) wearing a different coat. The runbook quotes
43,922/8,948 for those first two; the tree has since drifted by 9 lines and 2 files, so
re-measure rather than cite — that paragraph has been wrong once before and says so.

**The load-bearing consequence for sequencing:** migrating a destructor the quick way
*manufactures* shadow-declaration debt. That is how 770 files got there. So the unit of
work must be **a class**, not a file.

## 3. Principles

1. **Class-at-a-time vertical slices, not file-at-a-time.** A slice takes one class from
   rung 0/2 to rung 3 *with its real header*: fields named and typed, every method and
   dtor migrated, no local shadow struct left behind. Ten finished classes beat 300
   files converted into shadow-struct debt.
2. **Never trade a big lie for a small one silently.** If a slice must leave a shadow
   decl or a raw mangled call, say so in the file, as the runbook's rung-3 exemplar does.
3. **The byte gate is the only verdict, and `rombuild.py` alone is not it.** Bracket
   every header edit with `tools/eligible.py` before and after on a clean tree — it
   compiles only enrolled files, and a retype can un-match a non-enrolled includer while
   106/106 still passes.
4. **Order by blast radius, not by file count.** Layout-free work first.
5. **Same width unless a width change is intended and stated.** Equal width is necessary,
   not sufficient (`s16`→`u16` flips `ldrsh`/`ldrh`).

## 4. Phases

### Phase 0 — Instrument and gate *(prerequisite for everything)*

The gap is currently invisible: no tracked number, so no way to show progress to #821 and
no way to stop regression. Ship `tools/langmode_audit.py` reporting, as JSON and a one-line
summary:

- mangled-symbol files by extension and by symbol kind
- files with a local struct body / no project include / `char pad[` layout
- inline-`asm` and codegen-hack counts
- the `Fix12<int>` exclusion list, named

Wire it into CI as a **ratchet**: the counts may fall, never rise. This alone answers #821
with a number instead of an argument, and turns "we're working on it" into a chart.

Cost: small. Risk: none — no `src/` change.

### Phase 1 — SDK namespaces *(174 files, 33 namespaces) — zero layout risk*

33 of the mangled-name prefixes have no `include/<Name>.h` because they are not classes.
`_ZN2GX10EndLoadTexEv` is `GX::EndLoadTex()` — no `this`, no vtable, no struct, no
includers. The migration is a language-mode flip and nothing else:

```cpp
//cpp
// @symbol _ZN2GX10EndLoadTexEv
namespace GX { void EndLoadTex() { /* body unchanged */ } }
```

Largest prefixes: `GX` 18, `Sound` 17, `CP15` 16, `cstd` 14, `IRQ` 10, `G2S` 8, `GXS` 8.

This phase proves the pipeline (audit → migrate → byte-verify → ratchet) at the smallest
possible blast radius, and retires 17% of the backlog without touching one header.
Do it first for that reason, not because it is the biggest.

### Phase 2 — Destructors, class-at-a-time *(431 files)*

Proven pattern, largest single block, real header discipline required. Per §3.1 a slice
is a class, and `D0`/`D1`/`D2` for one class ship together — they share the vtable write
and the base-subobject call, so splitting them across commits means verifying the same
layout hypothesis three times.

Pilot targets — highest unmigrated count *and* an existing reconstructed header:

| class | `.c` left | header state |
|---|---|---|
| `Actor` | 56 | exists; 25 `unk_`, 12 `pad_` |
| `Particle` | 23 | exists; 30 `unk_`, 21 `pad_` |
| `Scene` | 17 | exists; largely named |
| `Stage` | 15 | exists; 14 `unk_`, 12 `pad_` |

Start with **`Scene`**, not `Actor`. Its header is already mostly named, so the slice
tests the *migration* rather than testing migration and field reconstruction at once.
`Actor` is the prize (56 files, and it is the base of the actor hierarchy) but it is also
the widest blast radius in the tree; take it third or fourth, once the procedure is boring.

Heed the runbook's warning on the C side: a polymorphic class needs an explicit
`void* vtable; /* 0x00 */` under `#else`, or every C includer's offsets shift by 4.

### Phase 3 — Plain methods *(543 of 579; 36 excluded)*

Same slices, same classes, after that class's dtors are done. Includes converting raw
mangled sibling calls into real calls where the callee now has a proper declaration —
migration is per-reference, not only per-function, so this phase shrinks the declaration
debt as a side effect.

### Phase 4 — Retire shadow declarations *(770 files)*

The phase that decides whether the critique actually stops being true. Point every
shadow struct at the real header and delete the local copy. Byte-neutral in intent and
therefore fully gated: `tools/affected_src.py` per header, then the `eligible.py` bracket.

Sequenced after 2–3 because those phases keep adding to it until the class-slice
discipline is habitual, and because a shadow struct whose class has no reconstructed
header yet has nowhere to point.

### Phase 5 — Constructors *(34 files) — timeboxed research spike*

Zero landed, so this is research, not throughput. The open question is whether mwccarm's
member-initializer-list and base-ctor codegen can be steered to the ROM's bytes at all,
or whether `C1`/`C2` are a genuine dead end like by-value `Fix12<int>`. Spike on one
already-understood class, measure across the sweep, and publish the answer **either way** —
a documented dead end in runbook §7 is a real deliverable and stops the next contributor
burning a week. Do not schedule the other 33 files until the spike returns.

### Phase 6 — Codegen hacks *(14 inline `asm`, 67 commented laundering)*

`#define LAUNDER(p) ((volatile u32 *)(int)(((long long)(int)(p))))` has no meaning in the
original C++; it exists to force address materialization. Small, and the most quotable
evidence in the issue, but each one is a bespoke codegen fight with no shared pattern —
so it pays worst per hour. Attack opportunistically when a slice already touches the file,
and treat the standalone 14 as last.

## 5. Explicit non-goals

- **Consolidating one-function files into real TUs.** Measured and declined: byte-safe,
  worth only 14–19% (runbook §4). The repo convention is one function per file, filename
  *is* the symbol (`AGENTS.md`). Do not reopen this without new numbers.
- **Declaring any method with a by-value class parameter** (`5Fix12IiE`). Dead end across
  all 25 compilers and every optimization level. Keep as `extern "C"` with scalar args.
- **Deriving a signature from call sites.** They disagree 27% of the time; the definition
  is the only non-guess.
- **Migrating before types are right.** A real `struct` on guessed member types is a lie
  every later file inherits.

## 6. Definition of done, per slice

Inherits runbook §6, plus:

- [ ] `ROM-build analysis: PASS`, module fidelity 106/106 exact
- [ ] `eligible.py` before/after on a clean tree: enrolled count did not fall
- [ ] attribution 0 changed, 0 lost; no commit both moves and rewrites a file
- [ ] **no file in the slice defines a struct body locally** — all include the real header
- [ ] every retyped field same-width, or the change deliberate and stated
- [ ] each field comment says what the value *means*, with range and encoding
- [ ] `langmode_audit.py` counts fell, and the CI ratchet reflects it

## 7. Risks

| risk | mitigation |
|---|---|
| Header retype silently un-matches a non-enrolled includer | the `eligible.py` bracket; never `rombuild.py` alone |
| Shadow structs make `affected_src.py` under-report | Phase 4; and §6 forbids new ones |
| Phase 2 volume tempts file-at-a-time throughput | slice = class; the ratchet counts shadow files too, so quick wins show up as debt |
| `Actor` blast radius (56 files + hierarchy base) | sequence it after two boring slices |
| Ctor spike open-ends | timeboxed; a documented dead end is an accepted outcome |

## 8. On answering #821

The strongest reply already in the thread is the collaborator's own audit, which conceded
1, 2, 4, most of 3, and half of 5 with counts attached. Phase 0 turns that one-off audit
into a standing number. Recommend replying with the audit output, this plan, and the
`Fix12<int>` and TU-consolidation exclusions stated as measured constraints rather than
preferences — the reporter's technical points are largely correct, and the repo's position
is stronger when it says so plainly and shows the ratchet.

## 9. Reproducing every number above

```sh
# mangled-symbol files by extension
git ls-files | grep -cE '^src/.*/_Z[^/]*\.c$|^src/_Z[^/]*\.c$'      # 1044
git ls-files | grep -cE '^src/.*/_Z[^/]*\.cpp$|^src/_Z[^/]*\.cpp$'  # 1471

# language mode overall
git ls-files | grep -cE '^src/.*\.c$'                                # 8125
git ls-files | grep -cE '^src/.*\.cpp$'                              # 3127

# landed real C++ definitions
grep -rlE '^\s*[A-Za-z_][A-Za-z0-9_]*::~[A-Za-z_]' src --include=*.cpp | wc -l   # 79

# shadow declarations
grep -rlE '^\s*(struct|class)\s+\w+\s*(:[^;{]*)?\{' src --include=*.cpp | wc -l  # 1426
grep -rlE 'char\s+pad\[0x' src --include=*.c --include=*.cpp | wc -l             # 690

# codegen hacks
grep -rlE '__asm|asm[[:space:]]*[({]' src --include=*.c --include=*.cpp | wc -l  # 14
grep -rliE 'launder|force.*(reg|codegen)' src --include=*.c --include=*.cpp | wc -l  # 67

# declaration debt (runbook §1) -- 43931 lines / 8950 files at 7b293af4
git grep -h -cE "^\s*extern " -- 'src/*' | awk '{s+=$1} END{print s}'
git grep -lE  "^\s*extern " -- 'src/*' | wc -l
```

Symbol-kind and per-class breakdowns come from `tools/langmode_audit.py` (Phase 0); until
it lands, the ad-hoc script in the session that wrote this plan is reproduced by matching
`(C1|C2|D0|D1|D2)Ev?$` against each mangled basename and the leading `_ZN(\d+)(\w+)`
length-prefixed class name.
