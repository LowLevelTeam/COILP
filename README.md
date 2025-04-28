# COIL Object Processor

[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](https://unlicense.org)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)]()

## Overview

COIL Object Processor (COP) is the processor component of the COIL (Computer Oriented Intermediate Language) Toolchain. It translates COIL binary format into target-specific machine code, allowing programs written in COIL to execute natively on different architectures.

COP serves as the middle stage of the COIL compilation process, bridging the gap between optionally architecture-independent COIL code and architecture-specific executables.


```
                     [libcoil-dev]             [libcoil-dev][libnof-dev]          [UNKNOWN]
human language .* -> [Compiler]    -> .coil -> [COIL Object Proccesor]   -> .o -> [Linker]  -> .out (Native Executable)
                                               [libcoil-dev]
                                               [Linker]      -> .coil (COIL library)
```

After COP is just a linker which may be built specifically for COIL compatibility or could be the native linker. If a COIL focused linker is utilized then linking .coil files into one large .coil file for relocation and redistribution can be done for better libraries which are partially precompiled (compiled to COIL not native machine code).



## License

This project is released under the Unlicense. See [LICENSE](LICENSE) for details.