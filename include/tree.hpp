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
            Node*      pointEnd;

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

            Node* parentMax()
            {
                Node* tmp = this;

                while (tmp->parent)
                    tmp = tmp->parent;
                return (tmp);
            }

            void setParent(Node* src)
            {
                parent = src;
            }

            void setLeft(Node* src)
            {
                left = src;
            }

            void setRight(Node* src)
            {
                right = src;
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

      public:
        Tree(const key_compare&    comp = key_compare(),
             const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _comp(comp), _point(NULL)
        {
            _end = _allocNode.allocate(1);
            _end->parent = NULL;
            _end->left = NULL;
            _end->right = NULL;
            _end->pointEnd = _end;
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

        Node* copyNode(Node* dest, Node* src)
        {
            if (src)
            {
                dest = copyNode(dest, src->left);
                dest = copyNode(dest, src->right);
                dest = insertNode(dest, src->value);
            }
            return dest;
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
            if (!_point)
                return (_end);
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
            _end->pointEnd = NULL;
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
            return (_alloc.max_size());
        }

        // Element access
        mapped_type& operator[](const key_type& k)
        { //
            Node* node = this->find(k);
            if (node)
                return node->value.second;
            insert(_point, ft::make_pair< const key_type, mapped_type >(
                               k, mapped_type()));
            updateEnd();
            return (*this)[k];
        }

        // Modifiers
        Node* firstNode(const value_type& val)
        {
            _point = _allocNode.allocate(1);
            _alloc.construct(&_point->value, val);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
            _point->pointEnd = _end;
            return (_point);
        }

        Node* insertNode(Node* parent, value_type val)
        {
            Node* node;

            node = _allocNode.allocate(1);
            _alloc.construct(&node->value, val);
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
            node->pointEnd = _end;
            if (_comp(parent->value.first, node->value.first))
                parent->right = node;
            else if (_comp(node->value.first, parent->value.first))
                parent->left = node;
            return (node);
        }

        Node* newInsert(Node* node, const value_type& val, Node* parent = 0)
        {
            if (_point == NULL)
                return (firstNode(val));
            else if (!node)
                return (insertNode(parent, val));
            if (_comp(val.first, node->value.first))
                node->left = newInsert(node->left, val, node);
            else if (_comp(node->value.first, val.first))
                node->right = newInsert(node->right, val, node);
            else
                return (node);
            node = balanceInsert(node, val.first);
            return (node);
        }

        void insert(Node* node, const value_type& val, Node* parent = 0)
        {
            node = newInsert(node, val, parent);
            _point = _point->parentMax();
            updateEnd();
        }

        Node* endBranch(Node* node)
        {
            Node* tmp = NULL;
            if (node->parent)
            {
                tmp = node->parent;
                if (node->parent->left == node)
                    node->parent->left = NULL;
                else
                    node->parent->right = NULL;
            }
            _alloc.destroy(&node->value);
            _allocNode.deallocate(node, 1);
            return (tmp);
        }

        Node* oneBranch(Node* node)
        {
            Node* tmp = node;
            if (node->left)
                node = node->left;
            else
                node = node->right;
            if (tmp->parent)
            {
                if (_comp(tmp->parent->value.first, tmp->value.first))
                    tmp->parent->right = node;
                else
                    tmp->parent->left = node;
            }
            node->setParent(tmp->parent);
            // node->parent = tmp->parent;
            _alloc.destroy(&tmp->value);
            _allocNode.deallocate(tmp, 1);
            return (node);
        }

        Node* midBranch(Node* node)
        {
            Node* tmp = node->right->childMin();

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
            tmp->parent->left = NULL;
            tmp->parent = node->parent;
            _alloc.destroy(&node->value);
            _allocNode.deallocate(node, 1);
            node = tmp;
            return (node);
        }

        Node* newErase(Node* node, const key_type key)
        {
            if (!node)
                return (node);
            if (_comp(key, node->value.first))
                node->left = newErase(node->left, key);
            else if (_comp(node->value.first, key))
                node->right = newErase(node->right, key);
            else
            {
                if (!node->left && !node->right)
                    node = endBranch(node);
                else if (!node->left || !node->right)
                    node = oneBranch(node);
                else
                    node = midBranch(node);
            }
            node = balanceErase(node);
            return (node);
        }

        void erase(Node* node, const key_type key)
        {
            node = newErase(node, key);
            _point = _point->parentMax();
            updateEnd();
        }

        void clear(Node* node)
        {
            if (node)
            {
                clear(node->left);
                clear(node->right);
                _alloc.destroy(&node->value);
                _allocNode.deallocate(node, 1);
            }
            _point = NULL;
            updateEnd();
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
        Node* rotateLeft(Node* node)
        {
            Node* new_parent = node->right;
            Node* mid_node = new_parent->left;

            new_parent->parent = node->parent;
            new_parent->left = node;
            node->parent = new_parent;
            node->right = mid_node;
            if (mid_node)
                mid_node->parent = node;
            return (new_parent);
        }

        Node* rotateRight(Node* node)
        {
            Node* new_parent = node->left;
            Node* mid_node = new_parent->right;

            new_parent->parent = node->parent;
            new_parent->right = node;
            node->parent = new_parent;
            node->left = mid_node;
            if (mid_node)
                mid_node->parent = node;
            return (new_parent);
        }

        int getBalance(Node* node)
        {
            if (!node)
                return 0;
            return (sizeHeight(node->left) - sizeHeight(node->right));
        }

        Node* balanceInsert(Node* node, const key_type key)
        {
            if (!node)
                return (node);
            int nb = getBalance(node);

            // Left left case
            if (node->left)
                if (nb > 1 && _comp(key, node->left->value.first))
                    return (rotateRight(node));
            // Right right case
            if (node->right)
                if (nb < -1 && _comp(node->right->value.first, key))
                    return (rotateLeft(node));
            // Left right case
            if (node->left)
                if (nb > 1 && _comp(node->left->value.first, key))
                {
                    node->left = rotateLeft(node->left);
                    return (rotateRight(node));
                }
            // Right left case
            if (node->right)
                if (nb < -1 && _comp(key, node->right->value.first))
                {
                    node->right = rotateRight(node->right);
                    return (rotateLeft(node));
                }
            return (node);
        }

        Node* balanceErase(Node* node)
        {
            if (!node)
                return (node);

            int nb = getBalance(node);
            // Left left case
            if (node->left)
                // if (nb < -1 && getBalance(node->left) <= 0)
                if (nb > 1 && getBalance(node->left) >= 0) // le mien
                    return (rotateRight(node));
            // Left right case
            if (node->left)
                // if (nb < -1 && getBalance(node->left) > 0)
                if (nb > 1 && getBalance(node->left) < 0) // le mien
                {
                    node->left = rotateLeft(node->left);
                    return (rotateRight(node));
                }
            if (node->right)
                // Right right case
                // if (nb > 1 && getBalance(node->right) >= 0)
                if (nb < -1 && getBalance(node->right) <= 0) // le mien
                    return (rotateLeft(node));
            // Right left case
            if (node->right)
                // if (nb > 1 && getBalance(node->right) < 0)
                if (nb < -1 && getBalance(node->right) > 0) // le mien
                {
                    node->right = rotateRight(node->right);
                    return (rotateLeft(node));
                }
            return (node);
        }
    };
} // namespace ft

#endif