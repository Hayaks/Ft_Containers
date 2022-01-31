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
        typedef Tree< value_type, key_compare, allocator_type > tree;
        typedef Tree< const value_type, key_compare, allocator_type >
                                                  const_tree;
        typedef typename tree::Node               node;
        typedef typename tree::value_compare      value_compare;
        typedef typename tree::reference          reference;
        typedef typename tree::const_reference    const_reference;
        typedef typename tree::pointer            pointer;
        typedef typename tree::const_pointer      const_pointer;
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

        // Destructor
        ~map(){};

        // Iterators
        iterator begin()
        {
            return iterator(_tree->getMin());
        }

        const_iterator begin(void) const
        {
            return const_iterator(_tree->getMin());
        }

        iterator end()
        {
            return iterator(_tree.getEnd());
        }

        const_iterator end() const
        {
            return const_iterator(_tree.getEnd());
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
            return iterator(begin());
        }

        const_iterator rend() const
        {
            return const_iterator(begin());
        }

        // Capacity
        size_type size() const
        {
            return (_tree.size());
        }

        size_type max_size() const
        {
            return (_tree.max_size());
        }

        bool empty() const
        {
            return (_tree.size() == 0);
        }

        // Element access
        mapped_type& operator[](const key_type& k)
        {
            return _tree[k];
        }

        // Modifiers
        pair< iterator, bool > insert(const value_type& val)
        {
        }

        iterator insert(iterator position, const value_type& val)
        {
        }

        template < class InputIterator >
        void insert(InputIterator first, InputIterator last)
        {
        }

        iterator erase(iterator position)
        {
        }

        iterator erase(iterator first, iterator last)
        {
        }

        void swap(map& x)
        {
        }

        void clear()
        {
            erase(begin(), end());
        }

        // Observers
        key_compare key_comp() const
        {
            return this->_tree.key_comp();
        }

        value_compare value_comp() const
        {
            return this->_tree.value_comp();
        }

        // Operations

        // Allocator
        Alloc get_allocator() const
        {
            return (_tree.getAlloc());
        }
    };
} // namespace ft

#endif