#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

#include "./util/enable_if.hpp"
#include "./util/is_const.hpp"

namespace ft
{
    template < class T, bool Is_const >
    class RandomAccessIterator
    {
      public:
        typedef typename ft::is_const< Is_const, const T, T >::type value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef value_type*                     pointer;
        typedef value_type&                     reference;
        typedef std::random_access_iterator_tag iterator_category;

      protected:
        pointer _point;

      public:
        // Constructor
        RandomAccessIterator() : _point(NULL)
        {
        }

        RandomAccessIterator(pointer src) : _point(src)
        {
        }

        template < bool is_const >
        RandomAccessIterator(const RandomAccessIterator< T, is_const >& src,
                             typename ft::enable_if< !is_const, T >::type* = 0)
        {
            _point = src.getPoint();
        }

        virtual ~RandomAccessIterator(){};

        pointer getPoint() const
        {
            return _point;
        }

        RandomAccessIterator& operator=(RandomAccessIterator const& src)
        {
            _point = src.getPoint();
            return (*this);
        }

        // Equivalence
        template < bool Isconst >
        bool operator==(RandomAccessIterator< T, Isconst > const& src) const
        {
            return (_point == src.getPoint());
        }

        template < bool Isconst >
        bool operator!=(RandomAccessIterator< T, Isconst > const& src) const
        {
            return !(*this == src); //
        }

        // Dereference
        reference operator*() const
        {
            return (*_point);
        }

        pointer operator->() const
        {
            return (_point);
        }

        reference operator[](difference_type n)
        {
            return (_point[n]);
        }

        // Increment/Decrement
        RandomAccessIterator& operator++(void)
        {
            ++_point;
            return (*this);
        }

        RandomAccessIterator& operator--(void)
        {
            --_point;
            return (*this);
        }

        RandomAccessIterator operator++(int)
        {
            RandomAccessIterator< T, Is_const > tmp(*this);
            ++_point;
            return (tmp);
        }

        RandomAccessIterator operator--(int)
        {
            RandomAccessIterator< T, Is_const > tmp(*this);
            --_point;
            return (tmp);
        }

        // Arithmetic
        RandomAccessIterator operator+(difference_type n) const
        {
            value_type* tmp = _point;
            return tmp += n;
        }

        RandomAccessIterator operator-(difference_type n) const
        {
            value_type* tmp = _point;
            return tmp -= n;
        }

        difference_type operator-(RandomAccessIterator const& src) const
        {
            return _point - src.getPoint();
        }

        // Relationnal
        template < bool Isconst >
        bool operator<(RandomAccessIterator< T, Isconst > const& src) const
        {
            return (_point < src.getPoint());
        }

        template < bool Isconst >
        bool operator>(RandomAccessIterator< T, Isconst > const& src) const
        {
            return (_point > src.getPoint());
        }

        template < bool Isconst >
        bool operator<=(RandomAccessIterator< T, Isconst > const& src) const
        {
            return (_point <= src.getPoint());
        }

        template < bool Isconst >
        bool operator>=(RandomAccessIterator< T, Isconst > const& src) const
        {
            return (_point >= src.getPoint());
        }

        // Assignment arithmetic
        RandomAccessIterator operator+=(difference_type value)
        {
            _point += value;
            return (*this);
        }

        RandomAccessIterator operator-=(difference_type value)
        {
            _point -= value;
            return (*this);
        }
    };

    template < class T, bool Is_const >
    RandomAccessIterator< T, Is_const >
    operator+(typename RandomAccessIterator< T, Is_const >::difference_type n,
              const RandomAccessIterator< T, Is_const >& rev_it)
    {
        return (RandomAccessIterator< T, Is_const >(rev_it + n));
    }

    template < class T, bool Is_const >
    RandomAccessIterator< T, Is_const >
    operator-(typename RandomAccessIterator< T, Is_const >::difference_type n,
              const RandomAccessIterator< T, Is_const >& rev_it)
    {
        return (RandomAccessIterator< T, Is_const >(-n - rev_it));
    }
} // namespace ft

#endif