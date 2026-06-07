#!/bin/bash

mkdir -p build

gcc ./src/*.c ./src/commands/*.c -o build/app -lform -lncurses

./build/app $1 $2 $3 $4
