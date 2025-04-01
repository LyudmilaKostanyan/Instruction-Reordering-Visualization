#include <iostream>
#include "kaizen.h"

void delay_function(volatile int& value, const size_t iterations) {
    for (int i = 0; i < iterations; ++i) {
        value = value * 2 + 1;
    }
}

void test_independent(const size_t iterations) {
    volatile int a = 0, b = 0, c = 0;

    auto timer = zen::timer();
    timer.start();

    delay_function(a, iterations);
    delay_function(b, iterations);
    delay_function(c, iterations);

    timer.stop();

    std::cout << "Independent operations: " << timer.duration<zen::timer::msec>().count() << " ms\n";
}

void test_dependent(const size_t iterations) {
    volatile int a = 0;

    auto start = std::chrono::high_resolution_clock::now();

    delay_function(a, iterations);
    a += 1;
    delay_function(a, iterations);
    a += 1;
    delay_function(a, iterations);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Dependent operations: " << duration.count() << " ms\n";
}

int main() {
    const size_t iterations = 5000000000;
    std::cout << "Number of iterations: " << iterations << "\n";

    std::cout << "Test 1: Independent operations (ROB possible)\n";
    test_independent(iterations);

    std::cout << "\nTest 2: Dependent operations (no ROB)\n";
    test_dependent(iterations);

    return 0;
}