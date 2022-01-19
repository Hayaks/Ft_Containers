#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template < class T, class Container = ft::vector< T > >
    class stack
    {
      public:
        typedef T         value_type;
        typedef Container container_type;
        typedef size_t    size_type;

      protected:
        container_type _cont;

      public:
        // Constructor
        explicit stack(const container_type& ctnr = container_type())
        {
            _cont = ctnr;
        }

        // Size
        bool empty() const
        {
            return (_cont.empty());
        }

        size_type size() const
        {
            return (_cont.size());
        }

        // Element access
        value_type& top()
        {
            return (_cont.back());
        }

        value_type& top() const
        {
            return (_cont.back());
        }

        // Modifiers
        void push(const value_type& val)
        {
            return (_cont.push_back(val));
        }

        void pop()
        {
            return (_cont.pop_back());
        }

        // Operators
        template < class _T, class _Container >
        friend bool operator==(const stack< _T, _Container >& lhs,
                               const stack< _T, _Container >& rhs);
        template < class _T, class _Container >
        friend bool operator!=(const stack< _T, _Container >& lhs,
                               const stack< _T, _Container >& rhs);
        template < class _T, class _Container >
        friend bool operator<(const stack< _T, _Container >& lhs,
                              const stack< _T, _Container >& rhs);
        template < class _T, class _Container >
        friend bool operator<=(const stack< _T, _Container >& lhs,
                               const stack< _T, _Container >& rhs);
        template < class _T, class _Container >
        friend bool operator>(const stack< _T, _Container >& lhs,
                              const stack< _T, _Container >& rhs);
        template < class _T, class _Container >
        friend bool operator>=(const stack< _T, _Container >& lhs,
                               const stack< _T, _Container >& rhs);
    };

    template < class T, class Container >
    bool operator==(const stack< T, Container >& lhs,
                    const stack< T, Container >& rhs)
    {
        return (lhs._cont == rhs._cont);
    }

    template < class T, class Container >
    bool operator!=(const stack< T, Container >& lhs,
                    const stack< T, Container >& rhs)
    {
        return (lhs._cont != rhs._cont);
    }

    template < class T, class Container >
    bool operator<(const stack< T, Container >& lhs,
                   const stack< T, Container >& rhs)
    {
        return (lhs._cont < rhs._cont);
    }

    template < class T, class Container >
    bool operator<=(const stack< T, Container >& lhs,
                    const stack< T, Container >& rhs)
    {
        return (lhs._cont <= rhs._cont);
    }

    template < class T, class Container >
    bool operator>(const stack< T, Container >& lhs,
                   const stack< T, Container >& rhs)
    {
        return (lhs._cont > rhs._cont);
    }

    template < class T, class Container >
    bool operator>=(const stack< T, Container >& lhs,
                    const stack< T, Container >& rhs)
    {
        return (lhs._cont >= rhs._cont);
    }

} // namespace ft

#endif