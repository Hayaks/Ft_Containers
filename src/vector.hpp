#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft
{
    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
        typedef T                                        value_type;
        typedef Allocator                                allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
    };
} // namespace ft

#endif