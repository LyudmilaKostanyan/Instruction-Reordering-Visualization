#include <iostream>
#include "kaizen.h" // Assuming this provides zen::timer

void delay_function(volatile size_t& value, const size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        value = (value * 13 + 7) % 1000000;
    }
}

double test_independent(const size_t iterations) {
    volatile size_t a = 0, b = 0, c = 0;

    auto timer = zen::timer();
    timer.start();

    delay_function(a, iterations);
    delay_function(b, iterations);
    delay_function(c, iterations);

    timer.stop();
    double duration = timer.duration<zen::timer::msec>().count();
    
    return duration;
}

double test_dependent(const size_t iterations) {
    volatile size_t a = 0;
    
    auto timer = zen::timer();
    timer.start();
    
    delay_function(a, iterations);
    a += 1;
    delay_function(a, iterations);
    a += 1;
    delay_function(a, iterations);
    
    timer.stop();
    double duration = timer.duration<zen::timer::msec>().count();
    
    return duration;
}

int main() {
    const size_t iterations = 1000000000;
    std::cout << "Number of iterations: " << iterations << "\n";
    
    std::cout << "Test 1: Independent operations (ROB possible)\n";
    std::cout << "Independent operations: " << test_independent(iterations) << " ms\n";
    
    std::cout << "\nTest 2: Dependent operations (no ROB)\n";
    std::cout << "Dependent operations: " << test_dependent(iterations) << " ms\n";

    return 0;
}