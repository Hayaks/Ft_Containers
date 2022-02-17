#include "../include/container.hpp"
#include "../include/map.hpp"
#include "../include/stack.hpp"
#include <algorithm>
#include <string>
#include <time.h>

void ft_vector()
{
    ft_vector_constructor();
    ft_vector_iterator_element_access();
    ft_vector_compare();
    ft_vector_capacity();
    ft_vector_modifiers();
}

void ft_stack()
{
    ft_stack_constructor();
    ft_stack_member_functions();
    ft_stack_relational();
}

void ft_map()
{
    ft_map_constructor();
    ft_map_iterator_element_access();
    ft_map_compare();
    ft_map_capacity();
    ft_map_modifiers();
    ft_map_observers();
    ft_map_operations();
}

int main()
{
    clock_t begin = clock();

    ft_vector();
    ft_stack();
    ft_map();
    clock_t end = clock();
    double  time_nb = (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "\n\nTime: " << time_nb << std::endl;
}