#!/bin/bash

echo "[1/3] Compiling precompile.cpp..."
g++ ./scripts/precompile.cpp -o precompile.exe
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "[2/3] Running precompiler on test.asm..."
./precompile.exe ./test.asm
if [ $? -ne 0 ]; then
    echo "Precompilation failed!"
    exit 1
fi

echo "[3/3] Done."