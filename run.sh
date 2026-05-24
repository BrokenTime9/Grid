#!/bin/bash

mkdir -p build

gcc ./src/*.c -lncurses -o build/app

./build/app $1 $2 $3 $4
