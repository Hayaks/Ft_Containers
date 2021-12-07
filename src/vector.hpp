#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <memory>

namespace ft
{
    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
      public:
        typedef T                                        value_type;
        typedef Allocator                                allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef std::ptrdiff_t                           difference_type;
        typedef std::size_t                              size_type;

      private:
        pointer        _point;
        allocator_type _alloc;
        size_type      _capacity;
        size_type      _size;

      public:
        explicit vector(const allocator_type& alloc = allocator_type());
        explicit vector(size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type());
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type());
        vector(const vector& x);
        virtual ~vector();
    };

    template <class T, class Allocator>
    vector<T, Allocator>::vector(const allocator_type& alloc)
        : _alloc(alloc), _capacity(0), _size(0)
    {
        _point = _alloc.allocate(_capacity);
    }

    template <class T, class Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type& val,
                                 const allocator_type& alloc)
        : _alloc(alloc), _capacity(n), _size(n)
    {
        _point = _alloc.allocate(_capacity);
        for (size_type i = 0; i < _size; i++)
            _alloc.construct(&_point[i], val);
    }

    /*template <class T, class Allocator>
    template <class InputIterator>
    vector<T, Allocator>::vector(InputIterator first, InputIterator last,
                                 const allocator_type& alloc)*/

    /*template <class T, class Allocator>
    vector<T, Allocator>::vector(const vector& x)
        : _alloc(), _capacity(), _size()
    {
    }*/

    template <class T, class Allocator>
    vector<T, Allocator>::~vector()
    {
        for (size_type i = 0; i < _size; i++)
            _alloc.destroy(&_point[i]);
        _alloc.deallocate(_point, _capacity);
    }
} // namespace ft

#endif