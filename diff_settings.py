def apply(config, args):
    config["baseimg"] = "disks/us/SLUS_005.61"
    config["myimg"] = "build/us/main.bin"
    config["mapfile"] = "build/us/main.map"
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
