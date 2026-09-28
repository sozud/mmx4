#!/usr/bin/env python3
import csv
import html
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
CHARACTERS = {"0": "X", "1": "Zero"}


def table(source, name):
    match = re.search(r"\(\*" + re.escape(name) + r"\[\]\)\(struct PlayerObj\*\) = \{(.*?)\};", source, re.S)
    return re.findall(r"\w+", match.group(1)) if match else []


def asm_names(source):
    return dict((func, name) for name, func in re.findall(r"^// (\w+)\nINCLUDE_ASM\(\"[^\"]+\", (\w+)\);", source, re.M))


def state_names(source):
    comments = asm_names(source)
    match = re.search(r"\(\*(\w+)\[\]\)\(struct PlayerObj\*\) = \{\s*\w+,\s*player_update_normal", source)
    top = table(source, match.group(1)) if match else []
    names = {}
    for state, handler in enumerate(top):
        names[(state, None)] = handler
    for state, table_name in ((1, "player_normal_state_funcs"), (2, "player_death_funcs")):
        for index, handler in enumerate(table(source, table_name)):
            names[(state, index)] = comments.get(handler, handler)
    return names


def trace(path, names):
    steps = []
    previous = None
    with open(path) as f:
        for row in csv.DictReader(f, delimiter="\t"):
            key = (int(row["state"]), int(row["unk5"]), int(row["unk6"]))
            if key != previous:
                label = names.get((key[0], key[1]), names.get((key[0], None), "?"))
                label = re.sub(r"^player_", "", label)
                steps.append(f"{row['frame']}: {label} [{key[0]}:{key[1]:02x}/{key[2]}]")
                previous = key
    return steps


def scenarios(script):
    result = []
    for line in script.read_text().splitlines():
        line = line.strip()
        if line and not line.startswith("#"):
            name, _, options = line.partition(" ")
            result.append((name, options))
    return result


def main():
    out = pathlib.Path(sys.argv[1])
    source = (ROOT / "src/main/player.c").read_text()
    names = state_names(source)
    runs = [line.split() for line in (ROOT / "tools/player_poke/runs.txt").read_text().splitlines() if line.strip() and not line.startswith("#")]
    sections = []
    seen = set()
    for group, script, stage, substage, character, loadout in runs:
        if (group, script) in seen:
            continue
        seen.add((group, script))
        rows = []
        for name, options in scenarios(ROOT / "tools/player_poke" / script):
            cells = []
            for character in ("0", "1"):
                image = out / group / f"{name}_c{character}.png"
                log = out / group / f"{name}_c{character}.tsv"
                if not image.exists():
                    continue
                steps = "<br>".join(html.escape(step) for step in trace(log, names))
                cells.append(
                    f"<div class='cell'><div class='who'>{CHARACTERS[character]}</div>"
                    f"<img src='{group}/{image.name}'><div class='trace'>{steps}</div></div>"
                )
            if cells:
                rows.append(
                    f"<section id='{group}-{name}'><h3>{html.escape(name)}</h3>"
                    f"<code>{html.escape(options)}</code>{''.join(cells)}</section>"
                )
        sections.append(f"<h2>{html.escape(group)} ({html.escape(script)})</h2>" + "".join(rows))
    page = (
        "<!doctype html><meta charset='utf-8'><title>Player sequences</title>"
        "<style>body{font:13px sans-serif;background:#111;color:#ddd;margin:16px}"
        "section{border-bottom:1px solid #333;padding:8px 0}h3{margin:4px 0}"
        "img{image-rendering:pixelated;max-width:100%}.cell{margin:6px 0}"
        ".who{color:#fc6;font-weight:bold}.trace{font:11px monospace;color:#9c9}"
        "code{color:#8af}</style>"
        "<h1>Player sequences</h1><p>Each strip is a grid of crops in frame order; "
        "the stride is in the options. Trace lines are frame: handler [state:unk5/unk6].</p>"
        + "".join(sections)
    )
    (out / "index.html").write_text(page)
    print(out / "index.html")


if __name__ == "__main__":
    main()
