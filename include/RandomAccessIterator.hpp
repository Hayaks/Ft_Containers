#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include <cstddef>
#include <iterator>

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
        RandomAccessIterator()
        {
            _point = NULL;
        }

        RandomAccessIterator(const pointer src)
        {
            _point = src;
        }

        RandomAccessIterator& operator=(RandomAccessIterator const& src)
        {
            _point = src._point;
        }

        virtual ~RandomAccessIterator(){};

        // Equivalence
        bool operator==(RandomAccessIterator const& src)
        {
            return (_point == src._point);
        }

        bool operator!=(RandomAccessIterator const& src)
        {
            return (_point != src._point);
        }

        // Dereference
        reference operator*()
        {
            return (*_point);
        }

        pointer operator->()
        {
            return (_point);
        }

        pointer operator[](difference_type n)
        {
            return (_point[n]);
        }

        // Increment/Decrement
        RandomAccessIterator& operator++(void)
        {
            _point++;
            return (*this);
        }

        RandomAccessIterator& operator--(void)
        {
            _point--;
            return (*this);
        }

        RandomAccessIterator operator++(int)
        {
            RandomAccessIterator< T, Is_const > tmp(*this);
            _point++;
            return (tmp);
        }

        RandomAccessIterator operator--(int)
        {
            RandomAccessIterator< T, Is_const > tmp(*this);
            _point--;
            return (tmp);
        }

        // Arithmetic
        RandomAccessIterator operator+(difference_type n)
        {
            value_type* tmp = _point;
            return tmp += n;
        }

        RandomAccessIterator operator-(difference_type n)
        {
            value_type* tmp = _point;
            return tmp -= n;
        }
        // deuxieme - (pointeur?)

        // Relationnal
        bool operator<(RandomAccessIterator const& src)
        {
            return (_point < src._point);
        }

        bool operator>(RandomAccessIterator const& src)
        {
            return (_point > src._point);
        }

        bool operator<=(RandomAccessIterator const& src)
        {
            return (_point <= src._point);
        }

        bool operator>=(RandomAccessIterator const& src)
        {
            return (_point >= src._point);
        }

        // Assignment arithmetic
        RandomAccessIterator& operator+=(difference_type value)
        {
            this->p += value;
            return (*this);
        }

        RandomAccessIterator& operator-=(difference_type value)
        {
            this->p -= value;
            return (*this);
        }
    };
} // namespace ft

#endif