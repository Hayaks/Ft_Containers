#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "RandomAccessIterator.hpp"
#include "ReverseIterator.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "./util/enable_if.hpp"
#include "./util/equal.hpp"
#include "./util/is_integral.hpp"
#include "util/lexicographical_compare.hpp"

namespace ft
{
    template < class T, class Allocator = std::allocator< T > >
    class vector
    {
      public:
        typedef T                                         value_type;
        typedef Allocator                                 allocator_type;
        typedef typename allocator_type::reference        reference;
        typedef typename allocator_type::const_reference  const_reference;
        typedef typename allocator_type::pointer          pointer;
        typedef typename allocator_type::const_pointer    const_pointer;
        typedef RandomAccessIterator< value_type, false > iterator;
        typedef RandomAccessIterator< value_type, true >  const_iterator;
        typedef ReverseIterator< iterator >               reverse_iterator;
        typedef ReverseIterator< const_iterator > const_reverse_iterator;
        typedef std::ptrdiff_t                    difference_type;
        typedef std::size_t                       size_type;

      private:
        pointer        _point;
        allocator_type _alloc;
        size_type      _capacity;
        size_type      _size;

      public:
        // Constructor
        explicit vector(const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _capacity(0), _size(0)
        {
            _point = _alloc.allocate(_capacity);
        }

        explicit vector(size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _capacity(n), _size(n)
        {
            _point = _alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(&_point[i], val);
        }

        template < class InputIterator >
        vector(typename enable_if< !is_integral< InputIterator >::value,
                                   InputIterator >::type first,
               InputIterator                             last,
               const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _capacity(0), _size(0)
        {
            InputIterator nb = first;

            for (; nb != last; nb++)
                _size++;

            _capacity = _size;
            _point = _alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++, first++) // first++
                _alloc.construct(&_point[i], *first);
        } //

        vector(const vector& x)
            : _alloc(x._alloc), _capacity(x._size), _size(x._size)
        {
            _point = _alloc.allocate(x._size);
            for (size_type i = 0; i < _size; ++i)
                _alloc.construct(&_point[i], x[i]);
        }

        // Destructor
        virtual ~vector()
        {
            clear();
            _alloc.deallocate(_point, _capacity);
        }

        vector& operator=(vector const& src)
        {
            if (this != &src)
            {
                clear();
                reserve(src.size());
                for (size_type i = 0; i < src.size(); ++i, ++_size)
                    _alloc.construct(&_point[i], src[i]);
                _size = src._size;
            }
            return (*this);
        }

        // Iterators
        iterator begin()
        {
            return iterator(_point);
        }

        const_iterator begin() const
        {
            return const_iterator(_point);
        }

        iterator end()
        {
            return iterator(_point + _size);
        }

        const_iterator end() const
        {
            return const_iterator(_point + _size);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        // Capacity
        size_type size() const
        {
            return (_size);
        }

        size_type max_size() const
        {
            return (_alloc.max_size());
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n < _size)
            {
                for (size_type i = n; i < _size; i++)
                    _alloc.destroy(&_point[i]);
            }
            else if (n > _size)
            {
                if (n > _capacity * 2)
                    reserve(n);
                else
                    reserve(_capacity * 2);
                for (; _size < n; ++_size)
                    _alloc.construct(&_point[_size], val);
            }
            _size = n;
        }

        size_type capacity() const
        {
            return (_capacity);
        }

        bool empty() const
        {
            return (_size == 0);
        }

        void reserve(size_type n)
        {
            if (n > max_size())
                throw std::length_error("Vector (reserve)");
            else if (n <= _capacity)
                return;
            else
            {
                pointer tmp;

                tmp = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    _alloc.construct(&tmp[i], _point[i]);
                    _alloc.destroy(&_point[i]);
                }
                _alloc.deallocate(_point, _capacity);
                _point = tmp;
                _capacity = n;
            }
        }

        // Element access
        reference operator[](size_type n)
        {
            return (_point[n]);
        }

        const_reference operator[](size_type n) const
        {
            return (_point[n]);
        }

        reference at(size_type n)
        {
            if (n < 0 || n >= _size)
                throw std::out_of_range("Vector index out of range");
            return (_point[n]);
        }

        const_reference at(size_type n) const
        {
            if (n < 0 || n >= _size)
                throw std::out_of_range("Vector index out of range");
            return (_point[n]);
        }

        reference front()
        {
            return (_point[0]);
        }

        const_reference front() const
        {
            return (_point[0]);
        }

        reference back()
        {
            return (_point[_size - 1]);
        }

        const_reference back() const
        {
            return (_point[_size - 1]);
        }

        // Modifiers
        template < class InputIterator >
        void assign(typename enable_if< !is_integral< InputIterator >::value,
                                        InputIterator >::type first,
                    InputIterator                             last)
        {
            InputIterator tmp = first;
            size_type     size = 0;

            for (; tmp != last; tmp++)
                size++;
            this->clear();
            if (size > _capacity)
                reserve(size);
            for (size_type i = 0; i < size; ++i)
            {
                _alloc.construct(&_point[i], *first);
                first++;
            }
            _size = size;
        }

        void assign(size_type n, const value_type& val)
        {
            this->clear();
            if (n > _capacity)
                reserve(n);
            for (size_type i = 0; i < n; ++i)
                _alloc.construct(&_point[i], val);
            _size = n;
        }

        void push_back(const value_type& val)
        {
            if (_size == _capacity)
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            _alloc.construct(&_point[_size], val);
            _size++;
        }

        void pop_back()
        {
            _alloc.destroy(&_point[_size - 1]);
            _size--;
        }

        iterator insert(iterator position, const value_type& val)
        {
            size_type pos = static_cast< size_type >(position - begin());

            if (_size == _capacity)
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            _size++;
            for (size_type i = _size - 1; i != pos; i--)
            {
                _alloc.construct(&_point[i], _point[i - 1]);
                _alloc.destroy(&_point[i - 1]);
            }
            _alloc.construct(&_point[pos], val);
            return iterator(&_point[pos]);
        }

        void insert(iterator position, size_type n, const value_type& val)
        {
            size_type pos = static_cast< size_type >(position - begin());

            if (_size + n > _capacity)
                reserve(_size + n);
            _size = _size + n;
            for (size_type i = _size - 1; i != pos + n - 1; i--)
            {
                _alloc.construct(&_point[i], _point[i - n]);
                _alloc.destroy(&_point[i - n]);
            }
            for (size_type i = pos; i != pos + n; i++)
                _alloc.construct(&_point[i], val);
        }

        template < class InputIterator >
        void insert(iterator                                  position,
                    typename enable_if< !is_integral< InputIterator >::value,
                                        InputIterator >::type first,
                    InputIterator                             last)
        {
            size_type pos = position - begin();
            size_type n = 0;

            for (InputIterator it = first; it != last; it++)
                n++;
            if (_size + n > _capacity * 2)
                reserve(_size + n);
            else if (_size + n > _capacity)
                reserve(_capacity * 2);
            _size = _size + n;
            for (size_type i = _size - 1; i != pos + n - 1; i--)
            {
                _alloc.construct(&_point[i], _point[i - n]);
                _alloc.destroy(&_point[i - n]);
            }
            for (size_type i = pos; i != pos + n; i++, first++)
                _alloc.construct(&_point[i], *first);
        }

        iterator erase(iterator position)
        {
            size_type pos = static_cast< size_type >(position - begin());

            for (size_type i = pos; i < _size + 1; ++i)
            {
                _alloc.destroy(&_point[i]);
                _alloc.construct(&_point[i], _point[i + 1]);
            }
            _alloc.destroy(&_point[_size - 1]);
            _size--;
            return iterator(position);
        }

        iterator erase(iterator first, iterator last)
        {
            size_type _begin = static_cast< size_type >(first - begin());
            size_type _end = static_cast< size_type >(last - begin());

            for (size_type i = _begin; i < _end; ++i)
                _alloc.destroy(&_point[i]);
            for (size_type i = _end; i < _size; ++i)
                _alloc.construct(&_point[i - (_end - _begin)], _point[i]);
            _size = _size - (_end - _begin);
            return iterator(first);
        }

        void swap(vector& x)
        {
            pointer   tmp_point = _point;
            size_type tmp_capacity = _capacity;
            size_type tmp_size = _size;

            _point = x._point;
            _capacity = x._capacity;
            _size = x._size;
            x._point = tmp_point;
            x._capacity = tmp_capacity;
            x._size = tmp_size;
        }

        void clear()
        {
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(&_point[i]);
            _size = 0;
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return (_alloc);
        }
    };

    template < class T, class Alloc >
    bool operator==(const vector< T, Alloc >& lhs,
                    const vector< T, Alloc >& rhs)
    {
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) &&
                lhs.size() == rhs.size()); // je sais pas
    }

    template < class T, class Alloc >
    bool operator!=(const vector< T, Alloc >& lhs,
                    const vector< T, Alloc >& rhs)
    {
        return !(lhs == rhs);
    }

    template < class T, class Alloc >
    bool operator<(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs)
    {
        if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end()))
            return true;
        else
            return false; // Verif
    }

    template < class T, class Alloc >
    bool operator<=(const vector< T, Alloc >& lhs,
                    const vector< T, Alloc >& rhs)
    {
        return !(rhs < lhs);
    }

    template < class T, class Alloc >
    bool operator>(const vector< T, Alloc >& lhs, const vector< T, Alloc >& rhs)
    {
        return (rhs < lhs);
    }

    template < class T, class Alloc >
    bool operator>=(const vector< T, Alloc >& lhs,
                    const vector< T, Alloc >& rhs)
    {
        return !(lhs < rhs);
    }

    template < class T, class Allocator >
    void swap(vector< T, Allocator >& x, vector< T, Allocator >& y)
    {
        x.swap(y);
    }
} // namespace ft

#endif