@echo off
echo Processor Simulator
echo Building and running project...
echo.

REM Create build directory if it doesn't exist
if not exist ".\build" mkdir ".\build"

REM Navigate to the build directory
cd ".\build"

REM Build the project
echo Building project...
cmake ..
cmake --build .

REM Run the main executable
echo.
echo Running main application...
echo.
cd ..
.\build\Debug\processor-simulator.exe

echo.
echo Script execution completed.
pause