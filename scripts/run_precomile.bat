@echo off
echo [1/3] Compiling precompile.cpp...
g++ .\scripts\precompile.cpp -o precompile.exe

if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

echo [2/3] Running precompiler on test.asm...
.\precompile.exe .\test.asm

if errorlevel 1 (
    echo Precompilation failed!
    exit /b 1
)

echo [3/3] Done.