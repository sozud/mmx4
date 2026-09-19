#!/bin/sh
if [ "${VERSION:-us}" = "us" ]; then
	SPLAT_CONFIG=SLUS_005.61.splat.yaml
	rm -rf asm/us assets/main
else # jp
	SPLAT_CONFIG=SLPS_009.02.splat.yaml
	rm -rf asm/jp assets/jp
fi
splat split ./config/${SPLAT_CONFIG}
