#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "../include/util/pair.hpp"
#include "./map.hpp"
#include "./stack.hpp"
#include "./vector.hpp"
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <vector>

#ifndef FT
#define FT std
#endif

#ifndef MODE
#define MODE full
#endif

// Vector
void ft_vector_constructor();
void ft_vector_iterator_element_access();
void ft_vector_compare();
void ft_vector_capacity();
void ft_vector_modifiers();

// Stack
void ft_stack_constructor();
void ft_stack_member_functions();
void ft_stack_relational();

// Map
void ft_map_constructor();
void ft_map_iterator_element_access();
void ft_map_compare();
void ft_map_capacity();
void ft_map_modifiers();
void ft_map_observers();
void ft_map_operations();

#endif