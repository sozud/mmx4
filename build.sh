rm -rf build && python3 ./build.py && ninja && sha1sum --check check.us.txt 