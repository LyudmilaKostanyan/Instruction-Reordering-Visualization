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
Here’s an example output from running the program with 1,000,000,000 iterations:

```
Number of iterations: 1000000000

Operation Type                     Time (ms)
--------------------------------------------------
Independent Operations (ROB)       5007.00
Dependent Operations (No ROB)      5503.00
--------------------------------------------------
Difference                         496.00
```

### Explanation of Output
- **Number of iterations**: The number of loop iterations in `delay_function` (1,000,000,000), controlling the workload size.
- **Independent Operations (ROB)**: Time taken (5007.00 ms) for three independent calls to `delay_function`. The CPU’s ROB can reorder or overlap these operations, leading to a shorter execution time compared to dependent operations.
- **Dependent Operations (No ROB)**: Time taken (5503.00 ms) for three dependent calls to `delay_function`. These must run sequentially due to data dependencies, resulting in a longer execution time.
- **Difference**: The difference between dependent and independent times (5503.00 - 5007.00 = 496.00 ms). A positive value indicates that dependent operations took more time, which aligns with expectations: the ROB optimizes independent operations, reducing their total runtime. This demonstrates the effectiveness of out-of-order execution for independent tasks. Factors influencing the result include:
  - **CPU Architecture**: The degree of reordering depends on the CPU’s ROB size and out-of-order execution capabilities.
  - **Workload Design**: The `delay_function` provides a measurable delay, and with a large iteration count (1 billion), the benefits of reordering become more pronounced.
  - **System Variability**: Minor fluctuations may occur due to background processes or caching, but the large iteration count helps minimize noise.

For even clearer results, averaging multiple runs or testing on different CPUs could further validate the ROB’s impact.

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
Example without arguments (uses default iteration count):
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
