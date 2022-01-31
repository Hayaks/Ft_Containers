#ifndef TREE_HPP
#define TREE_HPP

#include "iostream"

namespace ft
{
    template < class T, class Compare = std::less< typename T::first_type >,
               class Alloc = std::allocator< T > >
    class Tree
    {
      public:
        typedef typename T::first_type                   key_type;
        typedef typename T::second_type                  mapped_type;
        typedef T                                        value_type;
        typedef Compare                                  key_compare;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef size_t                                   size_type;

        struct Node
        {
          public:
            value_type value;
            Node*      parent;
            Node*      left;
            Node*      right;
        };

        class value_compare
        {
            friend class Tree;

          protected:
            Compare comp;
            value_compare(key_compare c) : comp(c)
            {
            }

          public:
            typedef bool       result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

      private:
        allocator_type _alloc;
        key_compare    _comp;
        Node*          _point;
        Node*          _end;
        size_type      _size;

      public:
        Tree(const key_compare&    comp = key_compare(),
             const allocator_type& alloc = allocator_type())
            : _comp(comp), _alloc(alloc), _size(0)
        {
            _point = _alloc.allocate(1);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
            _end = _point;
            // Peut etre le contraire. Allouer a end et non point
        }

        // Constructor
        Tree(const Tree& x)
        {
            *this->x;
        }

        // Destructor
        ~Tree()
        {
            clear();
        }

        // Iterators
        Node* getPoint() const
        {
            return (_point);
        }

        Node* getEnd() const
        {
            return (_end);
        }

        Node* getMin() const
        {
            Node* tmp = _point;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }

        // Capacity
        size_type size() const
        {
            return sizeNode(this->_point);
        }

        size_type sizeNode(Node* node) const
        {
            size_type s = 0;
            if (node)
            {
                s += sizeNode(node->right);
                s += sizeNode(node->left);
                ++s;
            }
            return s;
        }

        size_type max_size() const
        {
            return (_alloc.max_size());
        }

        // Observers
        key_compare key_comp(void) const
        {
            return _comp;
        }

        value_compare value_comp(void) const
        {
            return value_compare(_comp);
        }

        // Allocator
        Alloc getAlloc() const
        {
            return _alloc;
        }
    };
} // namespace ft

#endif