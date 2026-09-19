#!/bin/sh

VERSION=${VERSION:-us}

mkdir -p expected/${VERSION}
cp build/${VERSION}/main.o expected/${VERSION}/main.o
cp build/${VERSION}/main.bin expected/${VERSION}/main.bin
cp build/${VERSION}/main.map expected/${VERSION}/main.map
mkdir -p expected/build/${VERSION}
cp -r build/${VERSION}/src expected/build/${VERSION}/src
