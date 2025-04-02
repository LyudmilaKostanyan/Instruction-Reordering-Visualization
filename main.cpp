#include <iostream>
#include <cmath>
#include "kaizen.h"

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

int main(int argc, char** argv) {
    size_t iterations = 100000000;
    zen::cmd_args args(argv, argc);
    if (args.is_present("--n")) {
        auto num = std::stoi(args.get_options("--n")[0]);
        if (num > 0)
            iterations = num;
    }

    double indep = test_independent(iterations);
    double dep = test_dependent(iterations);

    std::cout << "Number of iterations: " << iterations << "\n\n";
    std::cout << std::setw(35) << std::left << "Operation Type" 
              << std::setw(20) << "Time (ms)" << "\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << std::setw(35) << "Independent Operations (ROB)" 
              << std::setw(20) << std::fixed << std::setprecision(2) << indep << "\n";
    std::cout << std::setw(35) << "Dependent Operations (No ROB)" 
              << std::setw(20) << dep << "\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << std::setw(35) << "Difference" 
              << std::setw(20) << std::abs(indep - dep) << "\n";

    return 0;
}