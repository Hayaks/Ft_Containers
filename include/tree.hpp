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
        allocator_type _alloc;
        key_compare    _comp;
        Node*          _point;
        Node*          _end;
        size_type      _size;

      public:
        Tree(const key_compare&    comp = key_compare(),
             const allocator_type& alloc = allocator_type())
            : _comp(comp), _alloc(alloc), _point(NULL), _size(0)
        {
            _end = _alloc.allocate(1);
            _end->parent = NULL;
            _end->left = NULL;
            _end->right = NULL;
            // Peut etre le contraire. Allouer a end et non point
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
            _alloc.deallocate(_end, 1);
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
                nb = sizeHeight(node, nb);
                nb_bis = sizeHeight(node, nb_bis);
            }
            return (nb = nb > nb_bis ? nb : nb_bis);
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

        // Modifiers
        void firstNode(const value_type& val)
        {
            _point = _alloc.allocate(1);
            _alloc.construct(&_point->value, val);
            _point->parent = NULL;
            _point->left = NULL;
            _point->right = NULL;
        }

        void insertNode(Node* parent, value_type val)
        {
            Node* node;

            node = _alloc.allocate(1);
            _alloc.construct(&node->value, val);
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
        }

        void insert(Node* node, const value_type& val)
        {
            if (_point == NULL)
            {
                firstNode(val);
                return;
            }
            else if (_point != NULL && !node)
            {
                insertNode(node->parent, val);
                return;
            }
            if (key_compare()(val->value.first, node->value.first))
                insert(node->left, val);
            else if (key_compare()(val->value.first, node->value.first))
                insert(node->right, val);
            else
                return;
            balanceInsert(node, val.first);
            updateEnd();
        }

        void erase(Node* node, const key_type key)
        {
            updateEnd();
        }

        void clear(Node* node)
        {
            if (node)
            {
                clear(node->left);
                clear(node->right);
                this->_allocValue.destroy(&node->value);
                this->_allocNode.deallocate(node, 1);
            }
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
            int nb = getBalance(node);

            // Left left case
            if (nb < -1 && _comp(key, node->left->value.first))
            {
                rotateRight(node);
                return;
            }
            // Right right case
            if (nb > 1 && _comp(node->left->value.first, key))
            {
                rotateLeft(node);
                return;
            }
            // Left right case
            if (nb < -1 && _comp(node->left->value.first, key))
            {
                rotateLeft(node->left);
                rotateRight(node);
                return;
            }
            // Right left case
            if (nb > 1 && _comp(key, node->left->value.first))
            {
                rotateRight(node->right);
                rotateLeft(node);
                return;
            }
            return;
        }

        void balanceDelete(Node* node)
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