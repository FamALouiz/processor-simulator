#!/bin/bash

# Define the root directory of the project (assuming this script is in scripts/ folder)
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

echo "=== Building Tests ==="

# Create build directory if it doesn't exist
if [ ! -d "${BUILD_DIR}" ]; then
    mkdir "${BUILD_DIR}"
fi

# Navigate to the build directory
cd "${BUILD_DIR}"

echo "Building project..."

# Build the tests target
cmake ..
cmake --build .

if [ $? -ne 0 ]; then
    echo "ERROR: Failed to build tests"
    exit 1
fi

echo
echo "=== Running Tests ==="
ctest -C Debug --output-on-failure 

if [ $? -ne 0 ]; then
    echo "ERROR: Some tests failed"
    exit 1
fi

echo
echo "=== All Tests Passed ==="
exit 0
