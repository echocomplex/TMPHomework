#include <Stack.hxx>
#include <StackAdapter.hxx>
#include <iostream>


int main () {
    unsigned long long nop = 0;
    StackAdapter <int> unit(&nop);
    unit.push(4);
    unit.push(3);
    unit.push(2);
    unit.push(1);
    unit.sort();
    std::cout << "Sorted stack >>> ";
    for (short i = 0; i < unit.size(); ++i) std::cout << unit[i] << ' ';
    std::cout << std::endl;
    std::cout << "NOP >>> " << nop << std::endl;
    return 0;
}