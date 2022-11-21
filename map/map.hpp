#pragma once

#include <iostream>
#include "pair.hpp"
#include "AVLtree.hpp"
#include "../vector/vector.hpp"
#include "../tools/utilsMap.hpp"
#include "../tools/ReverseIterator.hpp"
#include "../tools/IteratorBid.hpp"

namespace ft
{

    template <
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                                                     key_type;
        typedef T                                                                       mapped_type;
        typedef ft::pair<const Key, T>                                                  value_type;
        typedef Compare                                                                 key_compare;
        typedef Allocator                                                               allocator_type;
        typedef std::size_t                                                             size_type;
        typedef std::ptrdiff_t                                                          difference_type;
        typedef AVLtree<key_type, mapped_type, value_type, allocator_type, key_compare> Tree;
        typedef typename Tree::TreeNode                                                 TreeNode;
        typedef value_type &                                                            reference;
        typedef const value_type &                                                      const_reference;
        typedef TreeNode *                                                              pointer;
        typedef const TreeNode *                                                        const_pointer;
        typedef IteratorBid<Key, value_type, TreeNode, Tree, Compare>                   iterator;
        typedef IteratorBid<Key, const value_type, const TreeNode, Tree, Compare>       const_iterator;
        typedef Reverse_Iterator<iterator>                                              reverse_iterator;
        typedef Reverse_Iterator<const_iterator>                                        const_reverse_iterator;

        Tree _tree;

        class value_compare
        {
            friend class map;
            protected:
                Compare comp;
                value_compare() {}
                value_compare(Compare c) : comp(c) {}

            public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator()(const value_type &x, const value_type &y) const
                {
                    return comp(x.first, y.first);
            }
        };

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp_key(comp), _alloc(alloc) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp_key(comp), _alloc(alloc)
        {
            for (; first != last; first++)
                insert(value_type(first->first, first->second));
        }
        map(const map &x)
        {
            if (*this != x)
                *this = x;
        }

        map &operator=(const map &x)
        {
            clear();
            if (!x.empty())
                insert(x.begin(), x.end());
            return *this;
        }
        ~map() { clear(); }

        //-g --------________ITERATORS:_________-------- //

        iterator begin()
        {
            pointer p = _tree.root;
            while (p && p->left != NULL)
                p = p->left;
            if (p != NULL)
                return iterator(_tree, p->_pair, p);
            return iterator(_tree, NULL, p);
        }
        const_iterator begin() const
        {
            const_pointer p = _tree.root;
            while (p && p->left != NULL)
                p = p->left;
            if (p != NULL)
                return const_iterator(_tree, p->_pair, p);
            return const_iterator(_tree, NULL, p);
        }

        iterator end()
        {
            pointer p = _tree.root;
            while (p && p->right != NULL)
                p = p->right;
            if (p)
                return iterator(_tree, p->_pair, p->right);
            return iterator(_tree, NULL, NULL);
        }
        const_iterator end() const
        {
            const_pointer p = _tree.root;
            while (p && p->right != NULL)
                p = p->right;
            if (p)
                return const_iterator(_tree, p->_pair, p->right);
            return const_iterator(_tree, NULL, NULL);
        }

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        //-b --------________CAPACITY:_________-------- //

        bool empty() const { return !_tree.size(); }

        size_type size() const { return _tree.size(); }

        size_type max_size() const { return _alloc.max_size(); }

        //-y --------________ELEMENT ACCESS:_________-------- //

        mapped_type &operator[](const key_type &k)
        {
            mapped_type val = mapped_type();
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find)
                return _find->_pair->second;
            _tree.root = _tree.Insert(_tree.root, _tree.createNode(k, val));
            _find = _tree.Search(_tree.root, k);
            return _find->_pair->second;
        }

        mapped_type &at(const key_type &k)
        {
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find)
                return _find->_pair->second;
            throw std::out_of_range("map::at:  key not found");
        }
        const mapped_type &at(const key_type &k) const
        {
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find)
                return _find->_pair->second;
            throw std::out_of_range("map::at:  key not found");
        }

        //-r --------________MODIFIERS:_________-------- //

        pair<iterator, bool> insert(const value_type &val)
        {
            size_type _size = size();
            bool _new = true;
            _tree.root = _tree.Insert(_tree.root, _tree.createNode(val.first, val.second));
            TreeNode *_r = _tree.Search(_tree.root, val.first);
            if (_size == size()) _new = false;
            return ft::pair<iterator, bool>(iterator(_tree, _r->_pair, _r), _new);
        }

        iterator insert (iterator position, const value_type& val) {
            (void)position;
            _tree.root = _tree.Insert(_tree.root, _tree.createNode(val.first, val.second));
            TreeNode* _r = _tree.Search(_tree.root, val.first);
            return iterator(_tree, _r->_pair, _r);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; first++)
                insert(*first);
        }

        void erase(iterator position)
        {
            _tree.root = _tree.deleteNode(_tree.root, position->first);
        }
        size_type erase(const key_type &k)
        {
            size_type s = _tree.size();
            _tree.root = _tree.deleteNode(_tree.root, k);
            if (_tree.size() == s) return 0;
            return 1;
        }
        void erase(iterator first, iterator last)
        {
            ft::vector<Key> val;
            for (; first != last; first++)
                val.push_back(first->first);
            for (size_t i = 0; i < val.size(); i++)
                erase(val[i]);
        }

        void swap(map &x) { _tree.swap(x._tree); }

        void clear() { _tree.clear(); }

        //-b --------________OBSERVERS:_________-------- //

        key_compare key_comp() const { return _comp_key; }
        value_compare value_comp() const { return value_compare(_comp_key); }

        //-y --------________OPERATIONS:_________-------- //
        iterator find(const key_type &k)
        {
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find) return iterator(_tree, _find->_pair, _find);
            return end();
        }
        const_iterator find(const key_type &k) const
        {
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find) return const_iterator(_tree, _find->_pair, _find);
            return end();
        }

        size_type count(const key_type &k) const
        {
            TreeNode *_find = _tree.Search(_tree.root, k);
            if (_find) return 1;
            return 0;
        }

        iterator upper_bound(const key_type &k)
        {
            TreeNode *Ub = _tree.UpperBound(_tree.root, k);
            if (Ub) return iterator(_tree, Ub->_pair, Ub);
            return end();
        }
        const_iterator upper_bound(const key_type &k) const
        {
            TreeNode *Ub = _tree.UpperBound(_tree.root, k);
            if (Ub) return const_iterator(_tree, Ub->_pair, Ub);
            return end();
        }

        iterator lower_bound(const key_type &k)
        {
            if (find(k) != end())
                return find(k);
            iterator it = begin();
            for (; it != end(); it++)
                if (it->first >= k)
                    break;
            return it;
        }
        const_iterator lower_bound(const key_type &k) const
        {
            if (find(k) != end())
                return find(k);
            const_iterator it = begin();
            for (; it != end(); it++)
                if (it->first >= k)
                    break;
            return it;
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            iterator lit = lower_bound(k);
            iterator uit = upper_bound(k);
            return ft::pair<iterator, iterator>(lit, uit);
        }
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            const_iterator lit = lower_bound(k);
            const_iterator uit = upper_bound(k);
            return ft::pair<const_iterator, const_iterator>(lit, uit);
        }

        allocator_type get_allocator() const { return _alloc; }

        template <class key, class t, class compare, class Alloc>
        friend bool operator==(const map<key, t, compare, Alloc> &lhs, const map<key, t, compare, Alloc> &rhs)
        {
            if (lhs.size() != rhs.size())
                return false;
            return equalNode(lhs.begin(), lhs.end(), rhs.begin());
        }
        template <class key, class t, class compare, class Alloc>
        friend bool operator!=(const map<key, t, compare, Alloc> &lhs, const map<key, t, compare, Alloc> &rhs)
        {
            return !(lhs == rhs);
        }
        template <class key, class t, class compare, class Alloc>
        friend bool operator<(const map<key, t, compare, Alloc> &lhs, const map<key, t, compare, Alloc> &rhs)
        {
            return comp(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
        template <class key, class t, class compare, class Alloc>
        friend bool operator<=(const map<key, t, compare, Alloc> &lhs, const map<key, t, compare, Alloc> &rhs)
        {
            return !(rhs < lhs);
        }
        template <class key, class t, class compare, class Alloc>
        friend bool operator>(const map<key, t, compare, Alloc> &lhs, const map<key, t, compare, Alloc> &rhs)
        {
            return rhs < lhs;
        }
        template <class key, class t, class compare, class Alloc>
        friend bool operator>=(const map<key, t, compare, Alloc> &lhs, const map<Key, t, Compare, Alloc> &rhs)
        {
            return !(lhs < rhs);
        }

        template <class K, class t, class cmp, class Alloc>
        void swap(map<K, t, cmp, Alloc> &x, map<K, t, cmp, Alloc> &y)
        {
            x.swap(y);
        }

    private:
        key_compare _comp_key;
        allocator_type _alloc;
    };
}