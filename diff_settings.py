def apply(config, args):
    config["baseimg"] = "disks/us/SLUS_005.61"
    config["myimg"] = "build/us/main.bin"
    config["mapfile"] = "build/us/main.map"
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["source_directories"] = ["src", "include"]
    config["show_line_numbers_default"] = True
    config["arch"] = "mipsel"
    config["map_format"] = "gnu"
    config["build_dir"] = "build/us"
    config["expected_dir"] = "expected/us"
