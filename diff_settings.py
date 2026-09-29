import os


def apply(config, args):
    version = os.environ.get("VERSION", "us")
    config["baseimg"] = "disks/jp/SLPS_009.02" if version == "jp" else "disks/us/SLUS_005.61"
    config["myimg"] = f"build/{version}/main.bin"
    config["mapfile"] = f"build/{version}/main.map"
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["source_directories"] = ["src", "include"]
    config["show_line_numbers_default"] = True
    config["arch"] = "mipsel"
    config["map_format"] = "gnu"
    config["build_dir"] = f"build/{version}"
    config["expected_dir"] = f"expected/{version}"
