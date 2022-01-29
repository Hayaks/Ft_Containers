#ifndef MAP_HPP
#define MAP_HPP

#include "./util/pair.hpp"
#include "iostream"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "tree.hpp"

namespace ft
{
    template < class Key, class T, class Compare = std::less< Key >,
               class Alloc = std::allocator< pair< const Key, T > > >
    class map
    {
      public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef pair< const key_type, mapped_type >             value_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef Tree< value_type, key_compare, allocator_type > tree;
        typedef Tree< const value_type, key_compare, allocator_type >
                                                  const_tree;
        typedef typename tree::Node               node;
        typedef Map_iterator< tree, node >        iterator;
        typedef Map_iterator< const_tree, node >  const_iterator;
        typedef ReverseIterator< iterator >       reverse_iterator;
        typedef ReverseIterator< const_iterator > const_reverse_iterator;
        typedef std::ptrdiff_t                    difference_type;
        typedef size_t                            size_type;
        // size_type _size;
        tree _tree;

        // Constructor
        explicit map(const key_compare&    comp = key_compare(),
                     const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc)
        {
            /*_point = _alloc.allocate(1);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
            _end = _point;*/
        }

        template < class InputIterator >
        map(InputIterator first, InputIterator last,
            const key_compare&    comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc)
        {
            insert(first, last);
        }

        map(const map& x)
        {
            *this = x;
        }

        ~map(){};

        void clear()
        {
            erase(begin(), end());
        }
    };
} // namespace ft

#endif