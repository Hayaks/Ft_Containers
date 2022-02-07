#ifndef TREE_HPP
#define TREE_HPP

#include "./util/pair.hpp"
#include "iostream"
#include <iterator>

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

            Node* childMin()
            {
                Node* tmp = this;

                while (tmp->left)
                    tmp = tmp->left;
                return (tmp);
            }

            Node* childMax()
            {
                Node* tmp = this;

                while (tmp->right)
                    tmp = tmp->right;
                return (tmp);
            }
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
        allocator_type         _alloc;
        std::allocator< Node > _allocNode;
        key_compare            _comp;
        Node*                  _point;
        Node*                  _end;
        size_type              _size;

      public:
        Tree(const key_compare&    comp = key_compare(),
             const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _comp(comp), _point(NULL), _size(0)
        {
            _end = _allocNode.allocate(1);
            _end->parent = NULL;
            _end->left = NULL;
            _end->right = NULL;
        }

        // Constructor
        Tree(const Tree& x)
        {
            *this = x;
        }

        // Destructor
        ~Tree()
        {
            if (_point)
                clear(_point);
            _allocNode.deallocate(_end, 1);
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

        Node* getBegin() const
        {
            Node* tmp = _point;
            while (tmp->left)
                tmp = tmp->left;
            return tmp;
        }

        // Utils
        void updateEnd()
        {
            if (_point)
                _end->parent = _point->childMax();
            else
                _end->parent = NULL;
            _end->left = NULL;
            _end->right = NULL;
        }

        int sizeHeight(Node* node, int nb = 0) const
        {
            int nb_bis = 0;

            if (node)
            {
                nb++;
                nb_bis = nb;
                nb = sizeHeight(node->right, nb);
                nb_bis = sizeHeight(node->left, nb_bis);
                nb = nb > nb_bis ? nb : nb_bis; //
            }
            return (nb);
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
            return (_allocNode.max_size());
        }

        // Element access
        mapped_type& operator[](const key_type& k)
        { //
            Node* node = this->find(k);
            if (node)
                return node->value.second;
            _point = insertNode(
                _point,
                ft::make_pair< const key_type, mapped_type >(k, mapped_type()));
            updateEnd();
            return (*this)[k];
        }

        // Modifiers
        void firstNode(const value_type& val)
        {
            _point = _allocNode.allocate(1);
            _alloc.construct(&_point->value, val);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
        }

        void insertNode(Node* parent, value_type val)
        {
            Node* node;

            node = _allocNode.allocate(1);
            _alloc.construct(&node->value, val);
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
            if (_comp(parent->value.first, node->value.first))
                parent->right = node;
            else if (_comp(node->value.first, parent->value.first))
                parent->left = node;
        }

        void insert(Node* node, const value_type& val, Node* parent = 0)
        {
            if (_point == NULL)
            {
                firstNode(val);
                return;
            }
            else if (!node)
            {
                insertNode(parent, val);
                return;
            }
            if (_comp(val.first, node->value.first))
                insert(node->left, val, node);
            else if (_comp(node->value.first, val.first))
                insert(node->right, val, node);
            else
                return;
            balanceInsert(node, val.first);
            // updateEnd();
        }

        void endBranch(Node* node)
        {
            Node* tmp = node;
            if (node->left)
                node = node->left;
            else
                node->right;
            if (node)
                node->parent = tmp->parent;
            _alloc.destroy(&tmp->value);
            _allocNode.deallocate(tmp, 1);
        }

        void midBranch(Node* node)
        { //
            Node* tmp = node->right->min();

            // switch them
            if (tmp != node->right)
            {
                tmp->right = node->right;
                node->right->parent = tmp;
            }
            if (tmp != node->left)
            {
                tmp->left = node->left;
                node->left->parent = tmp;
            }
            tmp->parent->left = 0;
            tmp->parent = node->parent;
            _alloc.destroy(&node->value);
            _allocNode.deallocate(node, 1);
            node = tmp;
        }

        void erase(Node* node, const key_type key)
        {
            if (!node)
                return;
            if (_comp(key, node->value.first))
                node->left = erase(node->left, key);
            else if (_comp(node->value.first, key))
                node->right = erase(node->right, key);
            else
            {
                if (!node->left || !node->right)
                    endBranch(node);
                else
                    midBranch(node);
            }
            balanceErase(node);
            // updateEnd();
        }

        void clear(Node* node)
        {
            if (node)
            {
                clear(node->left);
                clear(node->right);
                this->_alloc.destroy(&node->value);
                this->_allocNode.deallocate(node, 1);
            }
        }

        void swap(Tree& x)
        {
            Node* tmp = _point;
            _point = x._point;
            x._point = tmp;
        }

        // Observers
        key_compare key_comp() const
        {
            return (_comp);
        }

        value_compare value_comp() const
        {
            return value_compare(_comp);
        }

        // Operations
        Node* find(const key_type& k) const
        {
            Node* tmp = _point;
            while (tmp)
            {
                if (_comp(k, tmp->value.first))
                    tmp = tmp->left;
                else if (_comp(tmp->value.first, k))
                    tmp = tmp->right;
                else
                    return tmp;
            }
            return NULL;
        }

        // Allocator
        Alloc getAlloc() const
        {
            return _alloc;
        }

        // Balancing
        void rotateLeft(Node* node)
        {
            Node* new_parent = node->right;
            Node* mid_node = new_parent->left;

            new_parent->parent = node->parent;
            new_parent->left = node;
            node->parent = new_parent;
            node->right = mid_node;
            if (mid_node)
                mid_node->parent = node;
        }

        void rotateRight(Node* node)
        {
            Node* new_parent = node->left;
            Node* mid_node = new_parent->right;

            new_parent->parent = node->parent;
            new_parent->right = node;
            node->parent = new_parent;
            node->left = mid_node;
            if (mid_node)
                mid_node->parent = node;
        }

        int getBalance(Node* node)
        {
            if (!node)
                return 0;
            return (sizeHeight(node->left) - sizeHeight(node->right));
        }

        void balanceInsert(Node* node, const key_type key)
        {
            if (!node)
                return;
            int nb = getBalance(node);

            // Left left case
            if (node->left)
                if (nb < -1 && _comp(key, node->left->value.first))
                {
                    rotateRight(node);
                    return;
                }
            // Right right case
            if (node->right)
                if (nb > 1 && _comp(node->right->value.first, key))
                {
                    rotateLeft(node);
                    return;
                }
            // Left right case
            if (node->left)
                if (nb < -1 && _comp(node->left->value.first, key))
                {
                    rotateLeft(node->left);
                    rotateRight(node);
                    return;
                }
            // Right left case
            if (node->right)
                if (nb > 1 && _comp(key, node->right->value.first))
                {
                    rotateRight(node->right);
                    rotateLeft(node);
                    return;
                }
            return;
        }

        void balanceErase(Node* node)
        {
            if (!node)
                return;

            int nb = getBalance(node);

            // Left left case
            if (nb < -1 && balanceFactor(node->left) <= 0)
            {
                rotateRight(node);
                return;
            }
            // Right right case
            if (nb > 1 && balanceFactor(node->right) >= 0)
            {
                rotateLeft(node);
                return;
            }
            // Left right case
            if (nb < -1 && balanceFactor(node->left) > 0)
            {
                rotateLeft(node->left);
                rotateRight(node);
                return;
            }
            // Right left case
            if (nb > 1 && balanceFactor(node->right) < 0)
            {
                rotateRight(node->right);
                rotateLeft(node);
                return;
            }
            return;
        }
    };
} // namespace ft

#endif