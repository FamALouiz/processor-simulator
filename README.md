# Processor Simulator

A simulation of a RISC-based processor written in C. This project implements a custom instruction set architecture (ISA) with a configurable instruction set and a 5-stage pipeline for educational purposes.

## Overview

This processor simulator reads assembly code, translates it into machine code, and executes it through a detailed 5-stage pipeline simulation. It allows observation of memory states, register values, and pipeline behavior in real-time through a comprehensive logging system.

## Features

-   **Assembly Code Parsing**: Parses a custom assembly language with support for labels, comments, and multiple instruction formats.
-   **Instruction Encoding**: Encodes assembly instructions into a 32-bit binary format according to the defined ISA.
-   **Memory Management**:
    -   Simulates a memory space of 2048 words (8KB).
    -   Provides 31 general-purpose registers plus program counter (PC).
    -   Implements special read-only register R0 that always returns zero.
-   **Configurable Instruction Set**: Loads instruction mnemonics and opcodes from a configuration file (`config/InstructionMappings.config`).
-   **Pipeline Implementation**:
    -   Features a detailed 5-stage pipeline (IF, ID, EX, MEM, WB).
    -   Implements pipeline registers between stages.
    -   Includes interrupt handling for pipeline flushing.
    -   Simulates different cycle durations for each stage.
-   **Logging System**:
    -   Provides detailed logs with timestamps and source information.
    -   Supports multiple verbosity levels (DEBUG, INFO).
    -   Features color-coded terminal output.
    -   Includes special register file logging.

## Architecture

The simulator implements a simplified RISC-like architecture with:

-   **32-bit Word Size**: All instructions and data are 32 bits wide.
-   **Memory Space**: 2048 words of memory (8KB), with the first 1024 words typically used for instructions and the rest for data.
-   **Pipeline Structure**: Classic 5-stage pipeline:
    -   **IF**: Instruction Fetch (1 cycle)
    -   **ID**: Instruction Decode (2 cycles)
    -   **EX**: Execute (2 cycles)
    -   **MEM**: Memory Access (1 cycle)
    -   **WB**: Write Back (1 cycle)
-   **Instruction Formats**:
    -   **R-Type**: For register-register operations (ADD, SUB, etc.)
    -   **I-Type**: For operations with immediates or memory access (MOVI, JEQ, etc.)
    -   **J-Type**: For unconditional jumps (JMP)

## Supported Instructions

| Instruction | Format | Opcode | Description                         |
| ----------- | ------ | ------ | ----------------------------------- |
| ADD         | R-Type | 0000   | Add two registers                   |
| SUB         | R-Type | 0001   | Subtract second register from first |
| MUL         | R-Type | 0010   | Multiply two registers              |
| MOVI        | I-Type | 0011   | Move immediate value to register    |
| JEQ         | I-Type | 0100   | Jump if two registers are equal     |
| AND         | R-Type | 0101   | Bitwise AND of two registers        |
| XORI        | I-Type | 0110   | Bitwise XOR with immediate value    |
| JMP         | J-Type | 0111   | Unconditional jump                  |
| LSL         | R-Type | 1000   | Logical shift left                  |
| LSR         | R-Type | 1001   | Logical shift right                 |
| MOVR        | I-Type | 1010   | Move value from memory to register  |
| MOVM        | I-Type | 1011   | Move value from register to memory  |

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
    git clone <repository-url>
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
./build/Debug/processor-simulator.exe
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

Create a file named `test.asm` (or update the path in `main.c`) with your assembly code:

```assembly
# Example program
MOVI R1 20     # Move immediate value 20 to R1
MOVI R2 20     # Move immediate value 20 to R2
JEQ R1 R2 1    # If R1 equals R2, jump ahead by 1 instruction
MUL R6 R1 R2   # Multiply R1 and R2, store in R6
ADD R5 R1 R2   # Add R1 and R2, store in R5
SUB R7 R5 R2   # Subtract R2 from R5, store in R7
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
├── CMakeLists.txt                # CMake build configuration
├── README.md                     # This documentation file
├── test.asm                      # Sample assembly code
├── build/                        # Build directory (generated)
├── config/
│   └── InstructionMappings.config # Instruction opcode definitions
├── include/                      # Header files
│   ├── config_loader/            # Configuration loading functionality
│   ├── datapath/                 # Pipeline stages and execution
│   ├── file_parser/              # Assembly file parsing
│   ├── log/                      # Logging functionality
│   ├── memory_management/        # Memory and register simulation
│   ├── parser/                   # Instruction parsing
│   └── util/                     # Utility functions
├── libs/                         # Implementation source files
│   ├── config_loader/
│   ├── datapath/
│   ├── file_parser/
│   ├── log/
│   ├── memory_management/
│   ├── parser/
│   └── util/
├── scripts/                      # Convenience scripts
│   ├── run.bat                   # Windows run script
│   └── run.sh                    # Linux/macOS run script
└── src/                          # Main application code
    └── main.c                    # Entry point
```

## Program Flow

1. **Initialization**: Sets up logging system and memory structures.
2. **Configuration Loading**: Reads instruction mappings from the config file.
3. **Assembly Parsing**: Reads and parses the assembly file into memory.
4. **Pipeline Setup**: Initializes the 5-stage pipeline and pipeline registers.
5. **Execution**: Runs the pipeline cycle by cycle:
    - **IF stage**: Fetches instructions from memory.
    - **ID stage**: Decodes instructions (2 cycles).
    - **EX stage**: Executes operations (2 cycles).
    - **MEM stage**: Accesses memory if needed.
    - **WB stage**: Writes results back to registers.
6. **Logging and Display**: Shows pipeline state and register values throughout execution.
7. **Completion**: Displays final register values and cleans up resources.

## Extending the Simulator

### Adding New Instructions

1. Add the instruction mnemonic and opcode to `config/InstructionMappings.config`.
2. Update the processor to handle the new instruction format if needed.
3. Implement the instruction's functionality in the appropriate library.
4. Add parsing logic in the word parser.

### Enhancing the Pipeline

To improve the pipeline implementation:

1. Add hazard detection and forwarding paths.
2. Implement branch prediction.
3. Add support for out-of-order execution.
4. Implement a cache hierarchy.

## Memory Model

The memory model consists of:

-   **Memory Array**: 2048 words (8KB), divided into:
    -   **Instruction Memory**: First 1024 words (addresses 0-1023)
    -   **Data Memory**: Last 1024 words (addresses 1024-2047)
-   **Register File**: 31 general-purpose registers (R1-R31)
-   **Special Registers**:
    -   R0: Always contains the value 0 (read-only)
    -   PC: Program Counter (accessible as R31)
-   **Pipeline Registers**: 5 special registers for holding data between pipeline stages (RIF, RID, REX, RMEM, RWB)

## Logging System

The simulator includes a flexible logging system that can:

-   Log to terminal, file, or both
-   Filter messages based on severity (INFO, WARNING, ERROR)
-   Include timestamp, source file, and line number information
-   Use color coding for different message types

## Pipeline Simulation

The simulator implements a realistic pipeline that:

-   Executes stages in parallel when possible
-   Handles data dependencies between instructions
-   Implements pipeline flushing on branches/jumps
-   Simulates different execution times for various pipeline stages
-   Uses pipeline registers (RIF, RID, REX, RMEM, RWB) to transfer data between stages

## Testing

The project includes a testing framework with test cases for:

-   Branch instructions
-   Config loading
-   File parsing
-   Instruction pipeline operation
-   Basic instructions
-   Memory management
-   Memory operations
-   Path utilities
-   Word parsing

## Contributing

Contributions are welcome! Here are some ways to contribute:

1. Implement missing instruction execution logic
2. Add hazard detection and forwarding
3. Improve error handling and reporting
4. Enhance documentation
5. Add more test cases

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

-   Developed for educational purposes in computer architecture courses
-   Inspired by MIPS and other RISC processor architectures
