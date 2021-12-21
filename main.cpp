#include "./include/vector.hpp"
#include <algorithm>
#include <vector>

#ifndef FT
#define FT std
#endif

// Colors
/*const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string CLEAN = "\033[0m";*/

const std::string CLEAN = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string BOLDWHITE = "\033[1m\033[37m";

void ft_vector()
{
    // Constructor/Destructor
    std::cout << YELLOW + "\n=== Test 01 - vector ===" + CLEAN << std::endl;
    std::cout << ">> vector< int > vec1(3, 42);" << std::endl;

    FT::vector< int > vec1(3, 42);

    std::cout << BOLDWHITE + "\n=== Test 01 - vector ===" + CLEAN << std::endl;
    std::cout << ">> vector< int > vec1(3, 42);" << std::endl;
    std::cout << GREEN + "[" << vec1[0] << ", " << vec1[1] << ", " << vec1[2]
              << "]" + CLEAN << "\n";
    // size()
    std::cout << ">> vec1.size()" << std::endl;
    std::cout << GREEN << vec1.size() << CLEAN << std::endl;
}

int main()
{
    ft_vector();
}