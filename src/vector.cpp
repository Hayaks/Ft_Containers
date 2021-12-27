#include "../include/container.hpp"

const std::string CLEAN = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[1m\033[37m";

void ft_vector_constructor()
{
    FT::vector< int >                        empty1;
    FT::vector< int, std::allocator< int > > empty2;
    FT::vector< int >                        int_size1(4);
    FT::vector< int >                        int_size2(5, 8);

    std::cout << WHITE + "\n||||| Constructor/Destructor |||||" + CLEAN
              << std::endl;
    std::cout << YELLOW + "\nEmpty:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty1.size() << CLEAN << std::endl;
    std::cout << YELLOW + "\nEmpty with allocator:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty2.size() << CLEAN << std::endl;
    std::cout << YELLOW + "\nVector int:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << int_size1.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << int_size1[0] << ", " << int_size1[1] << ", "
              << int_size1[2] << "]" + CLEAN << "\n";
    std::cout << YELLOW + "\nVector int with value:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << int_size2.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << int_size2[0] << ", " << int_size2[1] << ", "
              << int_size2[2] << "]" + CLEAN << "\n";
}