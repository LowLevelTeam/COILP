# COILP: COIL Processor

[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](https://unlicense.org)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)]()

## Overview

COILP is the official processor for COIL (Computer Oriented Intermediate Language), responsible for translating COIL binary format into target-specific output objects. It is the central component of the COIL toolchain that enables cross-architecture portability while maintaining native performance.

COILP processes COIL's type-determined instructions and variables, mapping them to the most efficient implementation for the target architecture.

## Features

- **Multiple Target Support**: x86-64, ARM64, and more architectures
- **Efficient Register Allocation**: Optimized variable-to-register mapping
- **Advanced Optimization**: Architecture-specific optimizations
- **ABI Integration**: Seamless handling of platform calling conventions
- **Platform-Specific Extensions**: Support for specialized instructions
- **Complete Variable System**: Automatic variable management
- **Comprehensive Output Format**: Support for all COILO features
- **Debugging Support**: Preserves debug information through processing

## Installation

### Prerequisites

- C++17 compliant compiler
- CMake 3.15+
- libcoil-dev 1.0.0+
- LLVM 13+ (optional, for enhanced optimization)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/LLT/coilp.git
cd coilp

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build
cmake --build .

# Install
cmake --install .
```

### Pre-built Binaries

Pre-built binaries are available for major platforms:

- [Windows x64](https://github.com/LLT/coilp/releases/download/v1.0.0/coilp-1.0.0-win-x64.zip)
- [macOS x64](https://github.com/LLT/coilp/releases/download/v1.0.0/coilp-1.0.0-macos-x64.tar.gz)
- [Linux x64](https://github.com/LLT/coilp/releases/download/v1.0.0/coilp-1.0.0-linux-x64.tar.gz)

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
| `-t <target>` | Target triple (device-arch-mode) |
| `-f <feature>` | Enable specific feature |
| `-S` | Output assembly instead of binary |
| `-j` | Generate JIT-friendly output |
| `-g` | Preserve debug information |
| `-v, --verbose` | Enable verbose output |
| `-h, --help` | Display help message |
| `--version` | Display version information |

### Example

```bash
# Process with optimization level 2 for x86-64
coilp -O2 -t cpu-x86-64 program.coil -o program.coilo

# Process with AVX extensions enabled
coilp -t cpu-x86-64 -f avx,avx2 program.coil -o program.coilo

# Output assembly instead of binary
coilp -S program.coil -o program.s
```

## Target Support

COILP currently supports the following targets:

| Target | Triple | Description | Status |
|--------|--------|-------------|--------|
| x86-64 | cpu-x86-64 | 64-bit x86 architecture | ✅ Full support |
| ARM64  | cpu-arm-64 | 64-bit ARM architecture | ✅ Full support |
| RISC-V | cpu-riscv-64 | 64-bit RISC-V architecture | 🚧 In development |
| WebAssembly | wasm-wasm32 | WebAssembly | 🚧 In development |
| CUDA   | gpu-cuda-sm75 | NVIDIA CUDA (SM 7.5) | 🚧 In development |

## Architecture

COILP uses a modular architecture with the following components:

1. **COIL Parser**: Reads and validates COIL binary format
2. **Variable Manager**: Allocates variables to registers or memory
3. **Target Backends**: Architecture-specific code generators
4. **ABI Manager**: Handles platform-specific calling conventions
5. **Optimization Pipeline**: Performs target-specific optimizations

## Code Example

Here's how a simple COIL instruction is processed to x86-64:

**COIL Input:**
```
MOV #1, 42       ; Move immediate 42 to variable #1
ADD #2, #1, 10   ; Add 10 to #1 and store in #2
```

**x86-64 Output:**
```asm
mov eax, 42      ; Variable #1 allocated to EAX
add ebx, eax, 10 ; Variable #2 allocated to EBX
```

**ARM64 Output:**
```asm
mov x0, #42      ; Variable #1 allocated to X0
add x1, x0, #10  ; Variable #2 allocated to X1
```

## Documentation

Comprehensive documentation is available in the `docs/` directory and online at [coil-lang.org/coilp/docs](https://coil-lang.org/coilp/docs):

- [User Guide](https://coil-lang.org/coilp/docs/user-guide.html)
- [Target Reference](https://coil-lang.org/coilp/docs/targets/)
- [Optimization Guide](https://coil-lang.org/coilp/docs/optimization.html)
- [ABI Reference](https://coil-lang.org/coilp/docs/abi/)
- [Examples](https://coil-lang.org/coilp/docs/examples/)

## Integration with Other Tools

COILP is designed to work seamlessly with other COIL ecosystem tools:

- `casm`: Generates COIL objects for processing
- `cbcrun`: Interprets CBC sections in COILO files
- `ld`/`link.exe`: OS-specific linkers for final executable generation

Typical workflow:
```bash
# Assemble CASM to COIL
casm program.casm -o program.coil

# Process COIL to target-specific code
coilp program.coil -o program.coilo

# Link with OS-specific linker (Linux example)
ld program.coilo -o program

# Run
./program
```

## Contributing

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to COILP.

## Implementation

For details on the implementation approach, architecture, and development plans, see [IMPLEMENTATION.md](IMPLEMENTATION.md).

## License

This project is released under the Unlicense. See [LICENSE](LICENSE) for details.