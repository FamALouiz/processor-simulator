#!/bin/bash
# filepath: c:\Users\fam\OneDrive\Desktop\GIU\Semester 6\CA\Project\processor-simulator\scripts\run_tests.sh

# Exit on error
set -e

echo "========== Building Processor Simulator Tests =========="

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --target run_tests

echo "========== All tests passed successfully =========="
