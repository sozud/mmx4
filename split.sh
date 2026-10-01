#!/bin/sh
case "${VERSION:-us}" in
us)
	SPLAT_CONFIG=SLUS_005.61.splat.yaml
	rm -rf asm/us assets/main
	;;
jp)
	SPLAT_CONFIG=SLPS_009.02.splat.yaml
	rm -rf asm/jp assets/jp
	;;
eu)
	SPLAT_CONFIG=SLES_011.76.splat.yaml
	rm -rf asm/eu assets/eu
	;;
esac
splat split ./config/${SPLAT_CONFIG}
