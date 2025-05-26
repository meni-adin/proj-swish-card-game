// main.cpp
import math; // Imports the 'math' module

#include <iostream> // For standard I/O (not part of our module)

int main() {
    int result = MyMath::add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;
    std::cout << "The value of PI is: " << MyMath::PI << std::endl;

    return 0;
}