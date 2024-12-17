#include <Stack.hxx>
#include <StackAdapter.hxx>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>


int main (int argc, const char** argv) {
    unsigned int n;
    if (argc >= 2) {
        n = std::atoi(argv[1]);
    }
    else {
        n = 300;
    }
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    
    unsigned long long nop = 0;
    StackAdapter <short> unit(&nop);

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        unit.push(rand() % 30000);
    }
    
    start = std::chrono::high_resolution_clock::now();

    unit.sort();

    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "N = " << n << std::endl << "Time: " << elapsed.count() << std::endl << "NOP = " << nop << std::endl;
    
    return 0;
}