wget https://github.com/decompals/old-gcc/releases/download/0.9/gcc-2.7.2.tar.gz &&
mkdir -p bin &&
tar -xvf ./gcc-2.7.2.tar.gz -C bin &&
rm -rf ./gcc-2.7.2.tar.* &&
wget https://github.com/decompals/old-gcc/releases/download/0.15/gcc-2.8.1-psx.tar.gz &&
mkdir -p bin/compilers/gcc-2.8.1 &&
tar -xvf ./gcc-2.8.1-psx.tar.gz -C bin/compilers/gcc-2.8.1 &&
rm -rf ./gcc-2.8.1-psx.tar.*
