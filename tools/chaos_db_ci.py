"""CI-safe Chaos Viewer data generator: rebuilds chaos-db.json from COMMITTED
data only (no ROM, no local ledger), so GitHub Actions can refresh the
chaos-data branch on every push and the hosted viewer always shows current
modules and percentages.

Derived the same way as progress.py --write-readme:
  universe   config/**/symbols.txt  (name, addr, size per module)
  matched    src/<name>.c[pp] exists and is not marked // NONMATCHING
  near-miss  nearmiss/db.jsonl (committed) -> div badge
  author     git history: the FIRST contributor to land the surviving match for each
             function (see first_matchers) -- credit follows renames and is not stolen by
             a later duplicate submission (login from users.noreply emails, else author name)
  project    tools/chaosviewer.config.json (committed branding/prompt config)

Not derivable without the ROM (left to local regens): disasm/callee detail
chunks, coddog sim/sibling. The details/ directory on the chaos-data branch is
preserved as-is by the workflow.

Usage: python tools/chaos_db_ci.py [--out chaos-db.json]
"""
import argparse
import collections
import json
import pathlib
import re
import subprocess
import time

REPO = pathlib.Path(__file__).resolve().parent.parent
CONFIG = REPO / "config"
SRC = REPO / "src"

FUNC_RE = re.compile(
    r"^(\S+)\s+kind:function\((?:arm|thumb),size=0x([0-9a-fA-F]+)\).*?addr:0x([0-9a-fA-F]+)")
LOGIN_RE = re.compile(r"^(?:\d+\+)?([^@]+)@users\.noreply\.github\.com$")


def module_label(sym_path: pathlib.Path) -> str | None:
    """config/arm9/symbols.txt -> arm9; config/arm9/overlays/ovNNN -> ovNNN.
    itcm/dtcm are skipped to match the viewer's module universe."""
    rel = sym_path.parent.relative_to(CONFIG).as_posix()
    if rel == "arm9":
        return "arm9"
    m = re.fullmatch(r"arm9/overlays/(ov\d+)", rel)
    return m.group(1) if m else None


def _handle_from(name: str, email: str) -> str:
    """git identity -> canonical-ish handle: noreply login, else the email local-part
    (stable across author-name typos, usually equals the GitHub handle), else the name."""
    email = email.strip()
    m = LOGIN_RE.match(email)
    return m.group(1) if m else (email.split("@")[0].lower() or name.strip())


def first_matchers() -> dict[str, str]:
    """{'src/name.ext': handle} crediting each currently-tracked file to the FIRST
    contributor to land the match it descends from. Credit belongs to whoever matched a
    function first; a later duplicate submission of the same function does not steal it.

    We replay the whole src/ history oldest-first, tracking one 'origin author' per live
    path, and follow git's own add / delete / rename classification (-M):
      * add     -- starts a lineage: the adder owns it (setdefault, so re-processing is safe)
      * rename  -- CARRIES the origin author to the new path. This is why a maintainer's
                   mass symbol-rename (func_ovNN_ADDR -> the real _ZN...Ev name) keeps the
                   original matcher's credit instead of handing it to the renamer.
      * delete  -- ENDS the lineage. A later add at that path is a fresh match and credits
                   the new author -- this is the false-match case: a wrong match that was
                   deleted ('fix the false matches') and later redone correctly by someone
                   else must credit the person who actually landed the surviving match.
    The distinction between rename and delete+add is exactly git's content-similarity call,
    which is what separates 'same match, new name' from 'the first attempt was wrong.'"""
    # diff.renameLimit=0 lifts the exhaustive-rename cap: the actor-symbol pass renamed
    # ~2200 files in one commit, far over git's default limit, so without this those renames
    # degrade to delete+add and the mass-renamer wrongly inherits every matcher's credit.
    out = subprocess.run(
        ["git", "-c", "diff.renameLimit=0", "log", "--reverse", "--diff-filter=ADR", "-M",
         "--format=%x01%an%x02%ae", "--name-status", "--", "src/"],
        cwd=REPO, capture_output=True, text=True, encoding="utf-8", errors="replace").stdout
    origin: dict[str, str] = {}   # live path -> author of the earliest add in its lineage
    handle = None
    for line in out.splitlines():
        if line.startswith("\x01"):
            name, _, email = line[1:].partition("\x02")
            handle = _handle_from(name, email)
        elif handle and line and line[0] in "ADR":
            parts = line.split("\t")
            code = parts[0]
            if code.startswith("A") and len(parts) >= 2:
                origin.setdefault(parts[1].strip(), handle)
            elif code.startswith("D") and len(parts) >= 2:
                origin.pop(parts[1].strip(), None)
            elif code.startswith("R") and len(parts) >= 3:
                old, new = parts[1].strip(), parts[2].strip()
                origin[new] = origin.pop(old, handle)  # carry the matcher's credit forward
    return origin


def match_finishers() -> dict[str, str]:
    """{'src/name.ext': handle} crediting whoever turned a NONMATCHING draft into a real
    byte-match -- the person who actually FINISHED the function.

    first_matchers() only sees add/delete/rename, so closing out a draft lands as a plain
    MODIFY and credits nobody: the original draft's author kept the credit and the matcher
    got zero. That is backwards for the refine tier, where converting a near-miss into a
    byte-identical match is the hard part of the work.

    A finish is identified by content, not by message: the file carried the "// NONMATCHING"
    banner before the commit and does not after. Only commits that touch that banner are
    inspected (-G), so this is a few hundred blobs, not the whole history. Oldest-first, so
    if a file is re-drafted and re-finished later, the LAST finisher wins.

    EXTENSION CHANGES count too. Cracking a draft very often also corrects the extension -- a
    C++ function drafted as .c becomes .cpp in the same commit that makes it match. Git reports
    that either as a RENAME (small edit) or as a DELETE + ADD pair (rewritten enough that rename
    detection gives up). Both were silently missed, because looking for the banner at the NEW
    path's parent finds nothing there; for either shape the before-side must be read from the
    OLD path. Renames are handled in the pickaxe pass, but the D+A shape CANNOT be: the pickaxe
    lists only the files whose own diff contains the pattern, and the added .cpp is banner-free
    by definition, so the add half is never reported and the pair can never be formed. Those get
    their own unfiltered pass; there are only ~27 such pairs in all of history, so pairing is
    cheap. Both passes credit through the same chronological guard, so a later re-draft and
    re-finish still wins regardless of which pass saw it."""
    order = {s: i for i, s in enumerate(subprocess.run(
        ["git", "rev-list", "--reverse", "HEAD"], cwd=REPO, capture_output=True,
        text=True, encoding="utf-8", errors="replace").stdout.split())}

    finishers: dict[str, str] = {}
    credited_at: dict[str, int] = {}

    def blob(rev: str, path: str) -> str:
        return subprocess.run(["git", "show", f"{rev}:{path}"], cwd=REPO, capture_output=True,
                              text=True, encoding="utf-8", errors="replace").stdout[:200]

    def finished(sha: str, new: str, old: str) -> bool:
        """True when `old` carried the banner before this commit and `new` does not after."""
        if "// NONMATCHING" in blob(sha, new):
            return False                      # still a draft after this commit
        return "// NONMATCHING" in blob(f"{sha}^", old)

    def credit(sha: str, handle: str, new: str, old: str) -> None:
        i = order.get(sha, -1)
        if new.startswith("src/") and i >= credited_at.get(new, -1) and finished(sha, new, old):
            finishers[new], credited_at[new] = handle, i

    def walk(argv, on_entry):
        sha = handle = None
        pending: list[tuple[str, list[str]]] = []
        for line in subprocess.run(argv, cwd=REPO, capture_output=True, text=True,
                                   encoding="utf-8", errors="replace").stdout.splitlines():
            if line.startswith("\x01"):
                if sha:
                    on_entry(sha, handle, pending)
                pending = []
                sha, _, who = line[1:].partition("\x02")
                name, _, email = who.partition("\x03")
                handle = _handle_from(name, email)
                continue
            if not (handle and sha and line.strip()):
                continue
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 2:
                pending.append((parts[0], [p.strip() for p in parts[1:]]))
        if sha:
            on_entry(sha, handle, pending)

    def modifies(sha, handle, entries):
        for code, paths in entries:
            if code.startswith("R") and len(paths) >= 2:
                credit(sha, handle, paths[1], paths[0])   # banner moved path: compare across it
            elif code.startswith("M"):
                credit(sha, handle, paths[0], paths[0])

    def pairs(sha, handle, entries):
        """A draft deleted and a same-symbol file added in ONE commit is the extension-change
        shape rename detection gave up on. Pair strictly on identical path-minus-extension, so
        an unrelated delete can never be read as a finish."""
        adds = [p[0] for c, p in entries if c.startswith("A")]
        dels = [p[0] for c, p in entries if c.startswith("D")]
        for d in dels:
            base = d.rsplit(".", 1)[0]
            for a in adds:
                if a.rsplit(".", 1)[0] == base and a != d:
                    credit(sha, handle, a, d)

    walk(["git", "log", "--reverse", "-G", "// NONMATCHING", "--diff-filter=MR", "-M",
          "--format=%x01%H%x02%an%x03%ae", "--name-status", "--", "src/"], modifies)
    walk(["git", "log", "--reverse", "--diff-filter=AD",
          "--format=%x01%H%x02%an%x03%ae", "--name-status", "--", "src/"], pairs)
    return finishers


def attribution_overrides() -> dict[str, str]:
    """Manual {'src/name.c': github_login} for matches the git-add author gets wrong -- e.g. a
    contributor's work that landed via a maintainer's consolidating PR/squash, which records the
    maintainer (not the matcher) as the commit author. Applied with HIGHEST priority. Lives in
    attribution.json at the repo root: {"overrides": {"src/x.c": "login", ...}}."""
    p = REPO / "attribution.json"
    if not p.is_file():
        return {}
    try:
        data = json.loads(p.read_text(encoding="utf-8"))
        ov = data.get("overrides", {}) if isinstance(data, dict) else {}
        return {k: v for k, v in ov.items()
                if isinstance(k, str) and k.startswith("src/") and isinstance(v, str) and v}
    except Exception as e:
        print(f"  (attribution.json skipped: {e})")
        return {}


def identity_aliases() -> dict[str, str]:
    """{'git_handle': 'github_login'} to collapse one person's many git identities into a single
    login -- git records vary the author email/name per machine and per squash, so the same human
    splits into several buckets (e.g. 'alexsobolew7' and 'ruspecial' are one person). Keys are the
    lowercased handles src_authors() produces; values are the canonical GitHub login. From
    attribution.json: {"aliases": {"alexsobolew7": "ruspecial", ...}}."""
    p = REPO / "attribution.json"
    if not p.is_file():
        return {}
    try:
        data = json.loads(p.read_text(encoding="utf-8"))
        al = data.get("aliases", {}) if isinstance(data, dict) else {}
        return {str(k).lower(): v for k, v in al.items() if isinstance(v, str) and v}
    except Exception:
        return {}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default="chaos-db.json")
    ap.add_argument("--contrib-out", default=None,
                    help="path for contributions.json (default: next to --out)")
    args = ap.parse_args()

    nm = {}
    nm_path = REPO / "nearmiss" / "db.jsonl"
    if nm_path.is_file():
        for l in nm_path.read_text(encoding="utf-8", errors="ignore").splitlines():
            if l.strip():
                try:
                    r = json.loads(l)
                    a = r["addr"]
                    nm[(r["module"], int(a, 0) if isinstance(a, str) else a)] = r
                except Exception:
                    continue

    finishers = match_finishers()        # src path -> who turned the draft into a real match
    firstmatch = first_matchers()        # src path -> first contributor to land the match
    overrides = attribution_overrides()  # manual fixes, highest priority
    aliases = identity_aliases()         # collapse one person's split git identities -> one login
    def canon(login):                    # apply the alias map (idempotent)
        return aliases.get(login.lower(), login)

    functions = []
    total_b = matched_b = matched_n = 0
    for sym in sorted(CONFIG.rglob("symbols.txt")):
        label = module_label(sym)
        if label is None:
            continue
        for line in sym.read_text(errors="ignore").splitlines():
            m = FUNC_RE.match(line)
            if not m:
                continue
            name, size, addr = m.group(1), int(m.group(2), 16), int(m.group(3), 16)
            src_path = None
            for ext in ("c", "cpp"):
                f = SRC / f"{name}.{ext}"
                if f.is_file():
                    src_path = f"src/{name}.{ext}"
                    break
            matched = bool(src_path) and "NONMATCHING" not in (
                (SRC / src_path.split("/", 1)[1]).read_text(errors="ignore")[:200] if src_path else "")
            total_b += size
            rec = {"id": f"{label}:0x{addr:08x}", "module": label, "name": name,
                   "addr": addr, "size": size, "matched": matched}
            if src_path:
                rec["srcPath"] = src_path
                if matched:
                    # Priority: manual override > whoever FINISHED the match (turned the
                    # NONMATCHING draft byte-identical) > whoever first added the file.
                    a = (overrides.get(src_path) or finishers.get(src_path)
                         or firstmatch.get(src_path))
                    if a:
                        rec["author"] = canon(a)
            if matched:
                matched_b += size
                matched_n += 1
            else:
                r = nm.get((label, addr))
                if r and r.get("divergences") is not None:
                    rec["div"] = r["divergences"]
            functions.append(rec)

    project = None
    pc = REPO / "tools" / "chaosviewer.config.json"
    if pc.is_file():
        project = json.loads(pc.read_text(encoding="utf-8"))

    db = {
        "generatedAt": time.strftime("%Y-%m-%d %H:%M", time.gmtime()) + " UTC",
        "project": project,
        "stats": {
            "totalFunctions": len(functions),
            "matchedFunctions": matched_n,
            "totalBytes": total_b,
            "matchedBytes": matched_b,
            "moduleCount": len({f["module"] for f in functions}),
        },
        "functions": functions,
    }
    out = pathlib.Path(args.out)
    out.write_text(json.dumps(db), encoding="utf-8")
    print(f"wrote {out} ({out.stat().st_size // 1024} KB): "
          f"{matched_n}/{len(functions)} funcs, {matched_b}/{total_b} bytes, "
          f"{db['stats']['moduleCount']} modules, "
          f"{sum(1 for f in functions if 'author' in f)} authored")

    # The single source of truth for the contributor chart: matched-function count per canonical
    # login. Regenerated on every merge (the workflow re-runs this), so "someone's number" is a
    # committed fact, not re-derived from git each time. --contrib-out defaults next to --out.
    tally = collections.Counter(f["author"] for f in functions if f.get("author"))
    contrib = {
        "generatedAt": db["generatedAt"],
        "note": "Matched functions per contributor (canonical GitHub login), credited to whoever "
                "landed each match FIRST (credit follows renames; a later duplicate match does not "
                "steal it). Auto-generated by tools/chaos_db_ci.py from committed matches, git "
                "history, attribution.json aliases (collapse split identities) + overrides. Do not "
                "hand-edit; fix names in attribution.json instead.",
        "totalMatched": matched_n,
        "contributors": [{"login": who, "matched": n} for who, n in tally.most_common()],
    }
    cpath = pathlib.Path(args.contrib_out) if args.contrib_out else out.with_name("contributions.json")
    cpath.write_text(json.dumps(contrib, indent=1), encoding="utf-8")
    print(f"wrote {cpath}: {len(tally)} contributors "
          f"(top: {', '.join(f'{w}={n}' for w, n in tally.most_common(4))})")


if __name__ == "__main__":
    main()
