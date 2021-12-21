#include "./include/vector.hpp"
#include <algorithm>

// Colors
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string CLEAN = "\033[0m";

void ft_vector()
{
    // Constructor/Destructor
    std::cout << YELLOW + "\n=== Test 01 - vector ===" + CLEAN << std::endl;
    std::cout << ">> FT::vector< int > vec1(3, 42);" << std::endl;
}

int main()
{
    ft_vector();
}