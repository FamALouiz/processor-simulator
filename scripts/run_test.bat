@echo off
setlocal enabledelayedexpansion

REM Define the root directory of the project (assuming this script is in scripts/ folder)
set "ROOT_DIR=%~dp0.."
echo === Building Tests ===

REM Create build directory if it doesn't exist
if not exist ".\build" mkdir ".\build"

REM Navigate to the build directory
cd ".\build"

REM Build the project
echo Building project...

REM Build the tests target
cmake ..
cmake --build .

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to build tests
    exit /b %ERRORLEVEL%
)

echo.
echo === Running Tests ===
ctest -C Debug --output-on-failure --verbose

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Some tests failed
    exit /b %ERRORLEVEL%
)

echo.
echo === All Tests Passed ===
exit /b 0