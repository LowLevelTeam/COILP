# COIL Object Processor (COP)

The COIL Object Processor (COP) is a tool that translates COIL (Computer Oriented Intermediate Language) object files into native object files. It serves as a key component in the COIL toolchain, bridging the gap between architecture-independent COIL code and architecture-specific executables.

## Features

- Translates COIL instructions to native machine code
- Currently supports x86-32 architecture
- Preserves sections and symbols from COIL objects
- Integrates with standard object formats (ELF on Linux)

## Building

To build COP, you need:

1. A C compiler (GCC recommended)
2. The libcoil-dev library
3. The libnof-dev library

### Build Instructions

```bash
# Create build directories
mkdir -p obj bin

# Build the project
make

# The executable will be in the bin directory
./bin/cop --help
```

## Usage

```
Usage: cop [options] <input-file>

Options:
  -o, --output <file>    Specify output file name
  -a, --arch <arch>      Target architecture (default: x86_32)
                         Supported: x86_32
  -v, --verbose          Enable verbose output
  --version              Display version information
  -h, --help             Display this help and exit
```

### Examples

Basic usage:

```bash
# Process a COIL file with default options (outputs .o)
./cop input.coil

# Specify output file
./cop -o output.o input.coil

# Enable verbose output
./cop -v input.coil
```

## Supported Instructions

The current implementation supports the following COIL instructions:

- NOP - No operation
- MOV - Move data
- PUSH - Push data onto stack
- POP - Pop data from stack
- ADD - Addition
- SUB - Subtraction
- RET - Return from function
- JMP - Jump to location
- CALL - Call function
- CMP - Compare values

## Architecture

COP is designed with a modular architecture to allow easy extension to additional target architectures:

- `main.c` - Entry point and command-line interface
- `processor.c` - Core translation logic
- `codegen_x86.c` - x86-32 code generator
- `utils.c` - Utility functions

## License

This project is released under the Unlicense. See the LICENSE file for details.