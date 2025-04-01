# COILP: COIL Processor

[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](https://unlicense.org)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)]()

## Overview

COILP is the processor component of the COIL (Computer Oriented Intermediate Language) Toolchain. It translates COIL binary format into target-specific machine code, allowing programs written in COIL to execute natively on different architectures.

COILP serves as the middle stage of the COIL compilation process, bridging the gap between architecture-independent COIL code and architecture-specific executables.

## Features

- **Multiple Target Support**: x86-64, ARM64, and RISC-V backends
- **Efficient Register Allocation**: Optimized variable-to-register mapping
- **Advanced Optimization**: Architecture-specific code optimizations
- **Variable System Implementation**: Complete implementation of COIL's variable model
- **Debug Information**: Preserves debug information through processing
- **Platform-Specific Extensions**: Support for specialized hardware features

## COIL Toolchain Integration

COILP is typically the middle stage in the COIL compilation workflow:

```
Source code (.casm)
       |
       v
  CASM Assembler
       |
       v
 COIL object (.coil)
       |
       v
  COIL Processor (coilp) <-- YOU ARE HERE
       |
       v
COIL output object (.coilo)
       |
       v
OS-specific Linker
       |
       v
  Executable (.exe/.out)
```

## Installation

### Prerequisites

- C++17 compliant compiler
- CMake 3.15+
- libcoil-dev 1.0.0+

### Building from Source

```bash
git clone https://github.com/LLT/coilp.git
cd coilp
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

## Usage

### Basic Usage

```bash
coilp [options] input.coil -o output.coilo
```

### Command Line Options

| Option | Description |
|--------|-------------|
| `-o, --output <file>` | Specify output file |
| `-O <level>` | Set optimization level (0-3) |
| `-t <target>` | Target name (x86-64, arm64, riscv) |
| `-f <feature>` | Enable specific feature (avx, neon, etc.) |
| `-S` | Output assembly instead of binary |
| `-g` | Preserve debug information |
| `-v, --verbose` | Enable verbose output |
| `-h, --help` | Display help message |

### Example

```bash
# Process for x86-64 with optimization level 2
coilp -O2 -t x86-64 program.coil -o program.coilo

# Process for ARM64 with NEON feature enabled
coilp -t arm64 -f neon program.coil -o program.coilo

# Output assembly instead of binary
coilp -S program.coil -o program.s
```

## Target Support

COILP currently supports the following targets:

| Target | Description | Status |
|--------|-------------|--------|
| x86-64 | 64-bit x86 architecture | ✅ Full support |
| ARM64  | 64-bit ARM architecture | ✅ Full support |
| RISC-V | 64-bit RISC-V architecture | 🚧 In development |

## Code Examples

Here's how COILP translates COIL code to architecture-specific code:

**Original COIL:**
```
; Basic addition
VAR #1, TYPE_INT32, 10
VAR #2, TYPE_INT32, 20
VAR #3, TYPE_INT32
ADD #3, #1, #2
```

**x86-64 Output:**
```asm
; x86-64 output
movl $10, %eax   ; Variable #1 in EAX
movl $20, %ebx   ; Variable #2 in EBX
addl %ebx, %eax  ; Add EBX to EAX
movl %eax, %ecx  ; Result in ECX (Variable #3)
```

**ARM64 Output:**
```asm
; ARM64 output
mov w0, #10      ; Variable #1 in W0
mov w1, #20      ; Variable #2 in W1
add w2, w0, w1   ; W2 = W0 + W1 (Variable #3)
```

## Documentation

Documentation is available in the `docs/` directory:

- [User Guide](docs/user-guide.md)
- [Target Reference](docs/targets/)
- [Optimization Guide](docs/optimization.md)
- [Feature Reference](docs/features.md)

## Workflow Integration

COILP works seamlessly with other COIL ecosystem tools:

```bash
# Assemble with CASM
casm program.casm -o program.coil

# Process with COILP
coilp program.coil -o program.coilo

# Link with OS-specific linker
ld program.coilo -o program

# Run
./program
```

## License

This project is released under the Unlicense. See [LICENSE](LICENSE) for details.