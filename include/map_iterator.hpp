#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

#include "./util/enable_if.hpp"
#include "./util/is_const.hpp"

namespace ft
{
    template < class T, class N >
    class Map_iterator
    {
      public:
        typedef typename T::value_type          value_type;
        typedef typename T::key_type            key_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef value_type*                     pointer;
        typedef value_type&                     reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename N::Node                Node;

      protected:
        Node* _point;
        Node* _end;

      public:
        // Constructor
        Map_iterator() : _point(NULL), _end(NULL)
        {
        }

        Map_iterator(const Map_iterator< T, N >& src)
            : _point(src.getPoint()), _end(src.getEnd())
        {
        }

        Map_iterator(Node* point) : _point(point), _end(NULL)
        {
            _end = search_end();
        }

        Map_iterator(Node* point, Node* end) : _point(point), _end(end)
        {
        }

        virtual ~Map_iterator(){};

        Node* getPoint() const
        {
            return _point;
        }

        Node* getEnd() const
        {
            return _end;
        }

        Map_iterator& operator=(Map_iterator const& src)
        {
            _point = src.getPoint();
            _end = src.getEnd();
            return (*this);
        }

        // Equivalence
        friend bool operator==(const Map_iterator& lhs, const Map_iterator& rhs)
        {
            return (lhs._point == rhs._point);
        }

        friend bool operator!=(const Map_iterator& lhs, const Map_iterator& rhs)
        {
            return (lhs._point != rhs._point);
        }

        // Dereference
        reference operator*() const
        {
            return (_point->value);
        }

        pointer operator->() const
        {
            return (&(_point->value));
        }

        reference operator[](difference_type n)
        {
            return (_point[n]);
        }

        // Increment/Decrement
        Map_iterator& operator++(void)
        {
            ++_point;
            return (*this);
        }

        Map_iterator& operator--(void)
        {
            --_point;
            return (*this);
        }

        Map_iterator operator++(int)
        {
        }

        Map_iterator operator--(int)
        {
        }

        Node* search_end()
        {
            if (_point)
            {
                Node* tmp = _point;
                while (tmp && tmp->parent)
                    tmp = tmp->parent;
                while (tmp && tmp->right)
                    tmp = tmp->right;
                return (static_cast< Node* >(tmp));
            }
            return (NULL);
        }
    };
} // namespace ft

#endif