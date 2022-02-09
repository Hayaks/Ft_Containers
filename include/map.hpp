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
        typedef Key                                      key_type;
        typedef T                                        mapped_type;
        typedef pair< const key_type, mapped_type >      value_type;
        typedef Compare                                  key_compare;
        typedef Alloc                                    allocator_type;
        typedef Tree< value_type, Compare, Alloc >       tree;
        typedef Tree< const value_type, Compare, Alloc > const_tree;
        typedef typename tree::Node                      node;
        typedef typename tree::value_compare             value_compare;
        typedef typename tree::reference                 reference;
        typedef typename tree::const_reference           const_reference;
        typedef typename tree::pointer                   pointer;
        typedef typename tree::const_pointer             const_pointer;
        typedef Map_iterator< tree >                     iterator;
        typedef Map_iterator< const_tree, tree >         const_iterator;
        typedef ReverseIterator< iterator >              reverse_iterator;
        typedef ReverseIterator< const_iterator >        const_reverse_iterator;
        typedef std::ptrdiff_t                           difference_type;
        typedef size_t                                   size_type;
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

        /*map& operator=(const map& x)
        {
            (void)x;
            clear();
            insert(x.begin(), x.end());
            return *this;
        }*/

        // Iterators
        iterator begin()
        {
            return iterator(_tree.getBegin());
        }

        const_iterator begin() const
        {
            return const_iterator(_tree.getBegin());
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
            size_type              nb_element = size();
            pair< iterator, bool > ret;

            _tree.insert(_tree.getPoint(), val);
            _tree.updateEnd();
            ret.first = find(val.first);
            ret.second = (nb_element != size());
            return (ret);
        }

        iterator insert(iterator position, const value_type& val)
        {
            (void)position;
            return insert(val).first;
        }

        template < class InputIterator >
        void insert(InputIterator first, InputIterator last)
        {
            for (InputIterator it = first; it != last; ++it)
            {
                _tree.insert(_tree.getPoint(), *it);
                _tree.updateEnd();
            }
        }

        void erase(iterator position)
        {
            erase((*position).first);
        }

        size_type erase(const key_type& k)
        {
            size_type nb_element = size();

            _tree.erase(_tree.getPoint(), k);
            _tree.updateEnd();
            return (nb_element != size());
        }

        void erase(iterator first, iterator last)
        { //
            iterator tmp;
            while (first != last)
            {
                tmp = first;
                ++first;
                erase(tmp);
                _tree.updateEnd();
            }
        }

        void swap(map& x)
        {
            _tree.swap(x._tree);
        }

        void clear()
        {
            // if (_tree.getPoint())
            //  _tree.clear(_tree.getPoint());
            erase(begin(), end());
        }

        // Observers
        key_compare key_comp() const
        {
            return _tree.key_comp();
        }

        value_compare value_comp() const
        {
            return _tree.value_comp();
        }

        // Operations
        iterator find(const key_type& k)
        {
            if (_tree.size() == 0) // Verif
                return end();
            return (iterator(_tree.find(k)));
        }

        const_iterator find(const key_type& k) const
        {
            if (_tree.size() == 0) // Verif
                return end();
            return (const_iterator(_tree.find(k)));
        }

        size_type count(const key_type& k) const
        {
            if (find(k) == end())
                return (0);
            return (1);
        }

        iterator lower_bound(const key_type& k)
        {
            for (iterator it = begin(); it != end(); it++)
                if (!key_comp()(it->first, k))
                    return it;
            return end();
        }

        const_iterator lower_bound(const key_type& k) const
        {
            for (const_iterator it = begin(); it != end(); it++)
                if (!key_comp()(it->first, k))
                    return it;
            return end();
        }

        iterator upper_bound(const key_type& k)
        {
            for (iterator it = begin(); it != end(); it++)
                if (key_comp()(k, it->first))
                    return it;
            return end();
        }

        const_iterator upper_bound(const key_type& k) const
        {
            for (const_iterator it = begin(); it != end(); it++)
                if (key_comp()(k, it->first))
                    return it;
            return end();
        }

        pair< const_iterator, const_iterator >
        equal_range(const key_type& k) const
        {
            ft::pair< const_iterator, const_iterator > ret(lower_bound(k),
                                                           upper_bound(k));
            return ret;
        }

        pair< iterator, iterator > equal_range(const key_type& k)
        {
            ft::pair< iterator, iterator > ret(lower_bound(k), upper_bound(k));
            return ret;
        }

        // Allocator
        Alloc get_allocator() const
        {
            return (_tree.getAlloc());
        }
    };
} // namespace ft

#endif