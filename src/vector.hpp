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

        // Iterators
        iterator               begin();
        const_iterator         begin() const;
        iterator               end();
        const_iterator         end() const;
        reverse_iterator       rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator       rend();
        const_reverse_iterator rend() const;

        // Capacity
        size_type size() const;
        size_type max_size() const;
        void      resize(size_type n, value_type val = value_type());
        size_type capacity() const;
        bool      empty() const;
        void      reserve(size_type n);

        // Element access
        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;
        reference       at(size_type n);
        const_reference at(size_type n) const;
        reference       front();
        const_reference front() const;
        reference       back();
        const_reference back() const;

        // Modifiers
        template <class InputIterator>
        void     assign(InputIterator first, InputIterator last); // Faux
        void     assign(size_type n, const value_type& val);
        void     push_back(const value_type& val);
        void     pop_back();
        iterator insert(iterator position, const value_type& val);
        void     insert(iterator position, size_type n, const value_type& val);
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void     swap(vector& x);
        void     clear();

        // Allocator
        allocator_type get_allocator() const;
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