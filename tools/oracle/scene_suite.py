from pathlib import Path


PC_SCENES = (
    ("title", 1080),
    ("character-select", 900),
    ("mission-briefing", 1650),
    ("initial-stage", 1650),
)

MEDNAFEN_SCENES = (
    ("title", 2200),
    ("character-select", 2300),
    ("mission-briefing", 3000),
    ("initial-stage", 2600),
)


def validate_scene(scene: str, destination: Path):
    manifest = destination / "manifest.tsv"
    lines = manifest.read_text().splitlines()
    if len(lines) < 2:
        raise RuntimeError(f"{scene}: capture manifest is empty")
    header = lines[0].split("\t")
    rows = [dict(zip(header, line.split("\t"))) for line in lines[1:]]
    images = {row["filename"] for row in rows}
    marker = b"P6\n320 240\n255\n"
    for filename in images:
        data = (destination / filename).read_bytes()
        if not data.startswith(marker) or len(data) != len(marker) + 320 * 240 * 3:
            raise RuntimeError(f"{scene}: invalid capture {filename}")

    if scene == "title":
        values = {
            int(row["step"])
            for row in rows
            if row["trigger"] == "game_info" and int(row["state"]) == 1
        }
        expected = set(range(14))
    else:
        values = {
            int(row["state"])
            for row in rows
            if row["trigger"] == "engine_info"
        }
        expected = {
            "character-select": 1,
            "mission-briefing": 3,
            "initial-stage": 6,
        }[scene]
        expected = {expected}
    if values != expected:
        raise RuntimeError(
            f"{scene}: expected states {sorted(expected)}, got {sorted(values)}"
        )
    return len(images), len(rows)
