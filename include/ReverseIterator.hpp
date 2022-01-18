#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include <iostream>

#include "./IteratorTraits.hpp"

namespace ft
{

    template < class Iterator >
    class ReverseIterator
    {
      public:
        typedef Iterator                                         iterator_type;
        typedef typename iterator_traits< Iterator >::value_type value_type;
        typedef typename iterator_traits< Iterator >::reference  reference;
        typedef typename iterator_traits< Iterator >::pointer    pointer;
        typedef typename iterator_traits< Iterator >::difference_type
            difference_type;
        typedef typename iterator_traits< Iterator >::iterator_category
            iterator_category;

      protected:
        Iterator _it;

      public:
        // Constructors
        ReverseIterator() : _it(NULL)
        {
        }
        explicit ReverseIterator(iterator_type it) : _it(it)
        {
        }
        ReverseIterator(ReverseIterator< iterator_type >& rev_it)
            : _it(rev_it.base())
        {
        }
        template < class T >
        ReverseIterator(const ReverseIterator< T >& rev_it) : _it(rev_it.base())
        {
        }

        virtual ~ReverseIterator()
        {
        }

        // Access element
        Iterator base() const
        {
            return _it;
        }

        // Dereference
        reference operator*() const
        {
            iterator_type tmp(_it);
            return *(--tmp);
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[](difference_type n) const
        {
            return base()[-n - 1];
        }

        // Arithmetic
        ReverseIterator operator+(difference_type n) const
        {
            return ReverseIterator(_it - n);
        }

        ReverseIterator operator-(difference_type n) const
        {
            return ReverseIterator(_it + n);
        }

        // Increment and Decrement
        ReverseIterator& operator++()
        {
            --_it;
            return (*this);
        }

        ReverseIterator operator++(int)
        {
            ReverseIterator tmp = *this;
            --_it;
            return (tmp);
        }

        ReverseIterator& operator--()
        {
            ++_it;
            return (*this);
        }

        ReverseIterator operator--(int)
        {
            ReverseIterator tmp = *this;
            ++_it;
            return (tmp);
        }

        // Assignment arithmetic
        ReverseIterator& operator+=(difference_type n)
        {
            _it -= n;
            return (*this);
        }

        ReverseIterator& operator-=(difference_type n)
        {
            _it += n;
            return (*this);
        }
    };

    template < class Iterator, class ConstIterator >
    bool operator==(const ReverseIterator< Iterator >&      lhs,
                    const ReverseIterator< ConstIterator >& rhs)
    {
        if (lhs.base() == rhs.base())
            return (true);
        else
            return (false);
    }

    template < class Iterator, class ConstIterator >
    bool operator!=(const ReverseIterator< Iterator >&      lhs,
                    const ReverseIterator< ConstIterator >& rhs)
    {
        if (!(lhs == rhs))
            return (true);
        else
            return (false);
    }

    template < class Iterator, class ConstIterator >
    bool operator<(const ReverseIterator< Iterator >&      lhs,
                   const ReverseIterator< ConstIterator >& rhs)
    {
        if (lhs.base() > rhs.base())
            return (true);
        else
            return (false);
    }

    template < class Iterator, class ConstIterator >
    bool operator<=(const ReverseIterator< Iterator >&      lhs,
                    const ReverseIterator< ConstIterator >& rhs)
    {
        if (lhs.base() >= rhs.base())
            return (true);
        else
            return (false);
    }

    template < class Iterator, class ConstIterator >
    bool operator>(const ReverseIterator< Iterator >&      lhs,
                   const ReverseIterator< ConstIterator >& rhs)
    {
        if (lhs.base() < rhs.base())
            return (true);
        else
            return (false);
    }

    template < class Iterator, class ConstIterator >
    bool operator>=(const ReverseIterator< Iterator >&      lhs,
                    const ReverseIterator< ConstIterator >& rhs)
    {
        if (lhs.base() <= rhs.base())
            return (true);
        else
            return (false);
    }

    template < class Iterator >
    ReverseIterator< Iterator >
    operator+(typename ReverseIterator< Iterator >::difference_type n,
              const ReverseIterator< Iterator >&                    rev_it)
    {
        return ReverseIterator< Iterator >(rev_it + n);
    }

    template < class Iterator, class ConstIterator >
    typename ReverseIterator< Iterator >::difference_type
    operator-(const ReverseIterator< Iterator >&      lhs,
              const ReverseIterator< ConstIterator >& rhs)
    {
        return (rhs.base() - lhs.base());
    }
} // namespace ft

#endif