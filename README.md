# Processor Simulator

A simulation of a RISC-based processor written in C. This project implements a custom instruction set architecture (ISA) with a configurable instruction set.

## Overview

This processor simulator reads assembly code, translates it into machine code, and allows examination of memory and register states. It's designed for educational purposes to understand processor architecture and assembly language programming.

## Features

-   **Assembly Code Parsing**: Parses a custom assembly language with support for labels, comments, and various instruction formats.
-   **Instruction Encoding**: Encodes assembly instructions into a 32-bit binary format following the specified ISA.
-   **Memory Management**: Simulates a memory space for instructions and data.
    -   Supports reading and writing to a memory array of 2048 words.
    -   Includes a set of 31 general-purpose registers and a program counter (PC).
    -   Special read-only register R0 that always returns zero.
-   **Configurable Instruction Set**: Instruction mnemonics and their corresponding opcodes are loaded from a configuration file (`config/InstructionMappings.config`).
    -   Supports R-type, I-type, and J-type instruction formats.
-   **Logging System**: Provides a comprehensive logging mechanism with different verbosity levels (DEBUG, INFO) and output options (terminal, file, or both).
    -   Logs include timestamps, source file, line number, and log level.
    -   Color-coded output in the terminal for different message types.

## Architecture

The simulator implements a simplified RISC-like architecture with:

-   **32-bit Word Size**: All instructions and data are 32 bits wide.
-   **Memory Space**: 2048 words of memory (8KB), with the first 1024 words typically used for instructions and the rest for data.
-   **Instruction Formats**:
    -   **R-Type**: For register-register operations (ADD, SUB, etc.)
    -   **I-Type**: For operations with immediates or memory access (MOVI, JEQ, etc.)
    -   **J-Type**: For unconditional jumps (JMP)

## Supported Instructions

| Instruction | Format | Opcode | Description                             |
| ----------- | ------ | ------ | --------------------------------------- |
| ADD         | R-Type | 0000   | Add two registers                       |
| SUB         | R-Type | 0001   | Subtract second register from first     |
| MUL         | R-Type | 0010   | Multiply two registers                  |
| MOVI        | I-Type | 0011   | Move immediate value to register        |
| JEQ         | I-Type | 0100   | Jump if two registers are equal         |
| AND         | R-Type | 0101   | Bitwise AND of two registers            |
| XORI        | I-Type | 0110   | Bitwise XOR with immediate value        |
| JMP         | J-Type | 0111   | Unconditional jump                      |
| LSL         | R-Type | 1000   | Logical shift left                      |
| LSR         | R-Type | 1001   | Logical shift right                     |
| MOVR        | I-Type | 1010   | Move value from one register to another |
| MOVM        | I-Type | 1011   | Memory access (load/store)              |

## Instruction Encoding

### R-Type Format (32 bits)

```
+---------+---------+---------+---------+------------------+
| op (4)  | rd (5)  | rs (5)  | rt (5)  | shamt/unused(13) |
+---------+---------+---------+---------+------------------+
```

### I-Type Format (32 bits)

```
+---------+---------+---------+---------------------------+
| op (4)  | rd (5)  | rs (5)  |       immediate (18)      |
+---------+---------+---------+---------------------------+
```

### J-Type Format (32 bits)

```
+---------+---------------------------------------------+
| op (4)  |               address (28)                  |
+---------+---------------------------------------------+
```

## Getting Started

### Prerequisites

-   C compiler (GCC, Clang, or MSVC)
-   CMake (version 3.10 or higher)
-   Optional: PowerShell (for Windows) or Bash (for Linux/macOS)

### Building the Project

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/processor-simulator.git
    cd processor-simulator
    ```

2. Build with CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

### Running the Simulator

Run the simulator from the build directory:

```bash
./build/Debug/processor-simulator
```

Or use the provided scripts:

-   Windows (PowerShell):

    ```powershell
    .\scripts\run.bat
    ```

-   Linux/macOS:
    ```bash
    chmod +x ./scripts/run.sh
    ./scripts/run.sh
    ```

## Writing Assembly Programs

Create a file named `test.asm` (or change the filename in `main.c`) with your assembly code:

```assembly
# This is a comment
ADD R1, R2, R3  # Add R2 and R3, store in R1
SUB R4, R5, R6  # Subtract R6 from R5, store in R4
MOVI R7, 42     # Move immediate value 42 to R7
JMP 10          # Jump to memory address 10
```

### Assembly Syntax

-   One instruction per line
-   Comments start with `#`
-   Register names are prefixed with `R` (R0-R31)
-   R0 is a special register that always contains 0
-   R31 is the program counter (PC)
-   Commas between operands are optional

## Project Structure

```
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This documentation file
├── test.asm                    # Sample assembly code file
├── build/                      # Build output directory (created by CMake)
├── config/
│   └── InstructionMappings.config # Defines instruction opcodes
├── include/                    # Header files
│   ├── config_loader/          # Configuration loading functionality
│   ├── file_parser/            # Assembly file parsing
│   ├── log/                    # Logging system
│   └── memory_management/      # Memory and register simulation
├── libs/                       # Implementation source files
│   ├── config_loader/
│   ├── file_parser/
│   ├── log/
│   ├── memory_management/
│   └── util/                   # Utility functions
├── scripts/                    # Convenience scripts
│   ├── run.bat                 # Windows run script
│   └── run.sh                  # Linux/macOS run script
└── src/                        # Main application code
    └── main.c                  # Entry point
```

## Program Flow

When the simulator runs, it performs the following steps:

1. **Initialization**: Sets up the logging system and initializes memory structures.
2. **Configuration Loading**: Reads the instruction mappings from the config file.
3. **Assembly Parsing**: Reads and parses the assembly file into memory.
4. **Memory Inspection**: Displays the encoded instructions from memory.
5. **Cleanup**: Frees resources and closes the logger.

## Extending the Simulator

### Adding New Instructions

1. Add the instruction mnemonic and opcode to `config/InstructionMappings.config`.
2. Update the `get_format` function in `file_parser.c` if needed to specify the instruction type.
3. If it's a new instruction type, you may need to add parsing logic to the `parse_and_encode` function.

### Implementing Execution

Currently, the simulator only parses and encodes instructions without executing them. To implement execution:

1. Create a new module for instruction execution.
2. Add a fetch-decode-execute cycle in a new function.
3. Implement handlers for each instruction type.

## Memory Model

The memory model consists of:

-   **Memory Array**: 2048 words (8KB), divided into:
    -   **Instruction Memory**: First 1024 words (addresses 0-1023)
    -   **Data Memory**: Last 1024 words (addresses 1024-2047)
-   **Register File**: 31 general-purpose registers (R1-R31)
-   **Special Registers**:
    -   R0: Always contains the value 0 (read-only)
    -   PC: Program Counter (accessible as R31)

## Logging System

The simulator includes a flexible logging system that can:

-   Log to terminal, file, or both
-   Filter messages based on severity (INFO, WARNING, ERROR)
-   Include timestamp, source file, and line number information
-   Use color coding for different message types

## Known Limitations

-   No actual instruction execution (simulator only parses and encodes)
-   Limited error checking in assembly parsing
-   No support for pseudo-instructions or macros
-   No simulation of pipeline stages, hazards, or forwarding

## Contributing

Contributions are welcome! Here are some ways you can contribute:

1. Implement instruction execution
2. Add support for more instructions
3. Improve error handling and reporting
4. Add unit tests
5. Enhance the documentation

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

-   Inspired by educational processor simulators used in computer architecture courses
-   Thanks to all contributors who have helped improve this project
