
mkdir -p psxi
./tools/psximager/src/psxbuild -c ./psxi/psxripped.cat ./psxi/mmx4.bin
./tools/psximager/src/psxinject ./psxi/mmx4.cue SLUS_005.61 ./build/us/main.bin
cp tools/cue.cue ./psxi/mmx4.cue