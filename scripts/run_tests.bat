@echo off
REM filepath: c:\Users\fam\OneDrive\Desktop\GIU\Semester 6\CA\Project\processor-simulator\scripts\run_tests.bat

echo ========== Building Processor Simulator Tests ==========

REM Create build directory if it doesn't exist
if not exist build mkdir build
cd build

REM Configure and build with CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --target run_tests

if %ERRORLEVEL% neq 0 (
    echo ========== Tests failed! ==========
    exit /b %ERRORLEVEL%
)

echo ========== All tests passed successfully ==========
