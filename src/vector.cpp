#include "../include/container.hpp"
#include <string>

const std::string CLEAN = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[1m\033[37m";

void ft_vector_constructor()
{
    FT::vector< int >                        empty1;
    FT::vector< int, std::allocator< int > > empty2;
    FT::vector< int >                        vec1(4);
    FT::vector< int >                        vec2(5, 8);
    FT::vector< int >                        vec_copy(vec2);
    FT::vector< int >                        vec_assign;

    std::cout << WHITE + "\n||||| Constructor/Destructor |||||" + CLEAN
              << std::endl;
    std::cout << YELLOW + "\nEmpty:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty1.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nEmpty with allocator:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty2.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nVector int:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec1.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << vec1[0] << ", " << vec1[1] << ", " << vec1[2]
              << "]" + CLEAN << "\n";

    std::cout << YELLOW + "\nVector int with value:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec2.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << vec2[0] << ", " << vec2[1] << ", " << vec2[2]
              << "]" + CLEAN << "\n";

    std::cout << YELLOW + "\nVector copy:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec_copy.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << vec_copy[0] << ", " << vec_copy[1] << ", "
              << vec_copy[2] << "]" + CLEAN << "\n";

    vec_assign = vec1;
    std::cout << YELLOW + "\nVector assign:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec_copy.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: "
              << "[" << vec_assign[0] << ", " << vec_assign[1] << ", "
              << vec_assign[2] << "]" + CLEAN << "\n";
}

void ft_vector_iterator()
{
    FT::vector< std::string >           vec(7, "Hello");
    FT::vector< std::string >::iterator it;

    std::cout << WHITE + "\n||||| Iterators |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nVector (7, Hello):" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::vector< std::string >::iterator it2 = vec.begin();
         it2 != vec.end(); ++it2)
        std::cout << "\t\t- " << *it2 << std::endl;
    std::cout << CLEAN;

    it = vec.begin();
    std::cout << YELLOW + "\nChange it for (Hi):" + CLEAN << std::endl;
    *it = "Hi";
    std::cout << GREEN << "\t-it: " << *it << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it++ for (Hola):" + CLEAN << std::endl;
    it++;
    *it = "Hola";
    std::cout << GREEN << "\t-it++: " << *it << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it + 2 for (Adios):" + CLEAN << std::endl;
    it = it + 2;
    *it = "Adios";
    std::cout << GREEN << "\t-it + 2: " << *it << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it - 1 for (Bonjour):" + CLEAN << std::endl;
    it = it - 1;
    *it = "Bonjour";
    std::cout << GREEN << "\t-it - 1: " << *it << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it += 4 for (Au revoir):" + CLEAN
              << std::endl;
    it += 4;
    *it = "Au revoir";
    std::cout << GREEN << "\t-it += 4: " << *it << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it -= 2 for (Salut):" + CLEAN << std::endl;
    it -= 2;
    *it = "Salut";
    std::cout << GREEN << "\t-it -= 2: " << *it << CLEAN << std::endl;

    std::cout << YELLOW +
                     "\nChange it[5] at Begin for (J'ai plus d'idée):" + CLEAN
              << std::endl;
    it = vec.begin();
    it[5] = "J'ai plus d'idée";
    std::cout << GREEN << "\t-it[5]: " << it[5] << CLEAN << std::endl;

    std::cout << YELLOW + "\nResultat final:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::vector< std::string >::iterator it2 = vec.begin();
         it2 != vec.end(); ++it2)
        std::cout << "\t\t- " << *it2 << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nBegin/End/Rbegin/Rend" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Begin: " << *vec.begin() << CLEAN << std::endl;
    std::cout << GREEN << "\t-End: " << *vec.end() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Rbegin: " << *vec.rbegin() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Rend: " << *vec.rend() << CLEAN << std::endl;

    std::cout << YELLOW + "\nFront/Back" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Front: " << vec.front() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Back: " << vec.back() << CLEAN << std::endl;
}

void ft_vector_compare()
{
    FT::vector< int > vec(3);
    FT::vector< int > vec2;

    std::cout << WHITE + "\n||||| Comparaison |||||" + CLEAN << std::endl;
    for (unsigned long int i = 0; i < vec.size(); ++i)
        vec[i] = (vec.size() - i) * 3;
    vec2 = vec;

    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::vector< int >::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << "\t\t- " << *it << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nComparaison identique value:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-vec.front() == vec2.front() = "
              << (vec.front() == vec2.front()) << std::endl;
    std::cout << GREEN << "\t-vec.front() != vec2.front() = "
              << (vec.front() != vec2.front()) << std::endl;

    std::cout << YELLOW + "\nComparaison different value:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-vec.front() == vec2.back() = "
              << (vec.front() == vec2.back()) << std::endl;
    std::cout << GREEN << "\t-vec.front() != vec2.back() = "
              << (vec.front() != vec2.back()) << std::endl;
    std::cout << GREEN << "\t-vec.back() < vec2.front() = "
              << (vec.back() < vec2.front()) << std::endl;
    std::cout << GREEN
              << "\t-vec.back() < vec2.back() = " << (vec.back() < vec2.back())
              << std::endl;
    std::cout << GREEN << "\t-vec.back() <= vec2.back() = "
              << (vec.back() <= vec2.back()) << std::endl;
    std::cout << GREEN << "\t-vec.front() > vec2.back() = "
              << (vec.front() > vec2.back()) << std::endl;
    std::cout << GREEN << "\t-vec.front() > vec2.front() = "
              << (vec.front() > vec2.front()) << std::endl;
    std::cout << GREEN << "\t-vec.front() >= vec2.front() = "
              << (vec.front() >= vec2.front()) << std::endl;
}

void ft_vector_capacity()
{
}