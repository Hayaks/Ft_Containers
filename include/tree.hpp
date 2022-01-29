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

      private:
        allocator_type _alloc;
        key_compare    _comp;
        Node*          _point;
        Node*          _end;

      public:
        Tree(const key_compare&    comp = key_compare(),
             const allocator_type& alloc = allocator_type())
            : _comp(comp), _alloc(alloc)
        {
            _point = _alloc.allocate(1);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
            _end = _point;
            // Peut etre le contraire. Allouer a end et non point
        }

        Tree(const Tree& x)
        {
            *this->x;
        }

        ~Tree()
        {
            clear();
        }
    };
} // namespace ft

#endif