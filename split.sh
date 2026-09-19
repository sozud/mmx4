#!/bin/sh
if [ "${VERSION:-us}" = "us" ]; then
	SPLAT_CONFIG=SLUS_005.61.splat.yaml
else # jp
	SPLAT_CONFIG=SLPS_009.02.splat.yaml
fi
rm -rf asm && rm -rf assets && splat split ./config/${SPLAT_CONFIG}
