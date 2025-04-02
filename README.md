# Instruction Reordering Visualization

## Overview
This project demonstrates the impact of CPU instruction reordering on execution time by comparing independent and dependent operations. It uses a simple C++ program to simulate workloads with artificial delays and measures their performance using a timing utility (`zen::timer`). The goal is to visualize how the CPU's Reorder Buffer (ROB) optimizes independent operations, potentially reducing runtime, while dependent operations must execute sequentially.

## Problem Description
Modern CPUs employ out-of-order execution to improve performance by reordering independent instructions. This experiment tests this concept by:
- Executing three independent operations that the CPU can potentially reorder or overlap.
- Executing three dependent operations that must run sequentially due to data dependencies.
- Measuring and comparing the execution times to highlight the effect of instruction reordering.

The code uses a `delay_function` with volatile operations to prevent compiler optimizations and ensure measurable workloads, simulating a scenario where the CPU’s reordering capabilities can be observed.

## What is ROB?
The **Reorder Buffer (ROB)** is a hardware component in modern CPUs that enables out-of-order execution. It temporarily holds instructions and their results, allowing the CPU to execute them in an order that maximizes efficiency (e.g., when operands are ready) rather than strictly following the program’s sequence. Once completed, the ROB ensures results are committed in the original program order to maintain correctness. In this experiment:
- **Independent Operations**: The ROB can reorder or parallelize these, potentially reducing total execution time.
- **Dependent Operations**: Data dependencies prevent reordering, forcing sequential execution.

## Example Output
Here’s an example output from running the program with 100,000,000 iterations:

```
Number of iterations: 100000000

Operation Type                     Time (ms)
--------------------------------------------------
Independent Operations (ROB)       1968.00
Dependent Operations (No ROB)      1890.00
--------------------------------------------------
Difference                         78.00
```

### Explanation of Output
- **Number of iterations**: The number of loop iterations in `delay_function` (100,000,000), controlling the workload size.
- **Independent Operations (ROB)**: Time taken (1968.00 ms) for three independent calls to `delay_function`. The CPU’s ROB might reorder or overlap these, but in this case, it took longer than expected (see below).
- **Dependent Operations (No ROB)**: Time taken (1890.00 ms) for three dependent calls to `delay_function`. These must run sequentially due to dependencies.
- **Difference**: The difference between independent and dependent times (1968.00 - 1890.00 = 78.00 ms). A positive value indicates independent operations took *more* time, which is unusual—typically, independent operations should be faster due to ROB optimization. This could result from:
  - **Measurement Noise**: Small iteration counts or system variability might skew results.
  - **CPU Behavior**: The specific CPU might not effectively reorder these operations, or caching effects could dominate.
  - **Workload**: The `delay_function` might not be complex enough to benefit from reordering on this scale.

For a clearer demonstration, increasing iterations or averaging multiple runs might better highlight ROB benefits (e.g., independent time < dependent time).


### Build the Project

### 1. Clone the Repository
```bash
git clone https://github.com/LyudmilaKostanyan/Instruction-Reordering-Visualization.git
cd Instruction-Reordering-Visualization
```

### 2. Build the Project
Use CMake to build the project:
```bash
cmake -S . -B build
cmake --build build
```
Ensure you have CMake and a C++ compiler (e.g., g++) installed.

### 3. Run the Program

#### For Windows Users
Example with arguments:
```bash
./build/main.exe --n 5000000
```
Example without arguments (uses default matrix size):
```bash
./build/main.exe
```

#### For Linux/macOS Users
The executable is named `main` instead of `main.exe`. Run it like this:
```bash
./build/main --n 5000000
```
Or without arguments:
```bash
./build/main
```
