# Mosaic

Overview

Runtime

Kernels
 - Compilation into comparable (JSON or XML)

Modules
  - Language agnostic
  - Definitions
  - Kernel configurations

Language

Flow

```mermaid
graph TD;
    "Progam Start"-->"Parse Command Line Options"'
    "Parse Command Line Options"-->"Load System Configurations";
    Load System Configuration-->Load Engine;
    Load Engine-->Load Program Configuration;
    Load Program Configuration-->Load Program Data'
    Load Program Data-->Run Program;
```
