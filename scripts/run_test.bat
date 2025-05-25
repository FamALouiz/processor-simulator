@echo off
setlocal enabledelayedexpansion

REM Define the root directory of the project (assuming this script is in scripts/ folder)
set "ROOT_DIR=%~dp0.."
set "BUILD_DIR=%ROOT_DIR%\build"

echo === Building Tests ===
cd "%BUILD_DIR%"

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