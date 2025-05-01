# COIL Object Processor (COP)

## Overview

The COIL Object Processor (COP) is a core component of the COIL toolchain responsible for translating COIL Intermediate Representation (IR) into native machine code. COP processes `.coil` files and generates `.coilo` files containing both the original IR and native code optimized for specific target architectures.

COP sits between the COIL C Compiler (CCC) and the COIL Latent Linker (CLL) in the COIL toolchain pipeline:

```
Source Code → COIL C Compiler (CCC) → COIL IR (.coil) → COIL Object Processor (COP) → COIL Native Objects (.coilo) → COIL Latent Linker (CLL) → Executable
```

## Features

- Reads and parses COIL IR files (`.coil`)
- Generates native machine code for multiple targets
- Support for various Processing Units (PUs) and architectures
- Modular backend system for easy extension
- Produces COIL object files with native code (`.coilo`)
- Fine-grained control over architecture-specific optimizations

Current support:
- **Processing Units**: CPU (more coming soon)
- **CPU Architectures**: x86 (16-bit, 32-bit, 64-bit)

## Building

### Prerequisites

- C99 compatible compiler (GCC or Clang recommended)
- GNU Make
- libcoil-dev (COIL Development Library)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/coil-project/cop.git
cd cop

# Build the library and CLI tool
make

# Run tests
make test

# Install (optional)
make install
```

## Usage

### Command Line Interface

```bash
# Basic usage
cop -o output.coilo input.coil

# Specify target architecture
cop --pu=CPU --arch=x86-64 -o output.coilo input.coil

# Enable specific architecture features
cop --pu=CPU --arch=x86-64 --features=AVX2 -o output.coilo input.coil

# Generate code for multiple targets
cop --pu=CPU --arch=x86-64 --pu=CPU --arch=x86-32 -o multi_target.coilo input.coil

# Specify per-section architecture targeting
cop --section=.text --pu=CPU --arch=x86-64 \
    --section=.data --pu=CPU --arch=x86-32 \
    -o mixed_sections.coilo input.coil

# Get help
cop --help
```

### Programmatic API

COP provides a C API for integration into other tools:

```c
#include <cop.h>

int main() {
  // Initialize COP
  cop_context_t* ctx = cop_init();
  
  // Configure target
  cop_config_add_target(ctx, COP_PU_CPU, COP_ARCH_X86_64, COP_FEATURE_AVX2);
  
  // Load input file
  cop_load_file(ctx, "input.coil");
  
  // Process and generate native code
  cop_process(ctx);
  
  // Write output file
  cop_write_file(ctx, "output.coilo");
  
  // Clean up
  cop_cleanup(ctx);
  
  return 0;
}
```

## Architecture

COP uses a hierarchical backend system to support different processing units and architectures:

1. **Processing Unit (PU) Layer**: Defines the type of processor (CPU, GPU, etc.)
2. **Architecture Layer**: Defines the specific architecture within a PU (x86-64, ARM64, etc.)
3. **Feature Layer**: Implements architecture-specific optimizations (AVX, NEON, etc.)

This design allows for:
- Clean separation of concerns
- Easy addition of new targets
- Consistent interface across all backends
- Flexible configuration options

## Contributing

Contributions are welcome! Areas where help is particularly appreciated:

- Adding support for new CPU architectures (ARM, RISC-V, etc.)
- Implementing GPU backends (NVIDIA, AMD, Intel)
- Performance optimizations for existing backends
- Test case improvements

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License

This project is licensed under the terms of the LICENSE file included in the repository.