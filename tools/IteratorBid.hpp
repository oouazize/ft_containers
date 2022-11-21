#pragma once

#include <iostream>
#include "utilsMap.hpp"


namespace ft
{
    //-b -----------------iter_traits------------------
    template<class Iterator>
    class iter_traits
    {
        public:
            typedef typename Iterator::value_type        value_type;
            typedef typename Iterator::pointer           pointer;
            typedef typename Iterator::reference         reference;
            typedef typename Iterator::difference_type   difference_type;
            typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    class iter_traits<T*>
    {
        public:
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef std::ptrdiff_t                  difference_type;
            typedef std::bidirectional_iterator_tag iterator_category;
    };

    template<class T>
    class iter_traits<const T*>
    {
        public:
            typedef T                               value_type;
            typedef const T*                        pointer;
            typedef const T&                        reference;
            typedef std::ptrdiff_t                  difference_type;
            typedef std::bidirectional_iterator_tag iterator_category;
    };
    
    //-r ---------------------IteratorBid---------------------
    template <class Key, class P, class T, class Tree, class Compare> class IteratorBid {
        public:
            typedef typename iter_traits<P*>::value_type            value_type;
            typedef typename iter_traits<P*>::pointer               pointer;
            typedef typename iter_traits<P*>::reference             reference;
            typedef typename iter_traits<P*>::difference_type       difference_type;
            typedef typename iter_traits<P*>::iterator_category     iterator_category;

            IteratorBid() : _tree(), _pair(), ptr_node(nullptr) {}
            IteratorBid(Tree r, pointer pr, T* ptr) : _tree(r), _pair(pr), ptr_node(ptr) {}
            IteratorBid(const IteratorBid &iter) : _tree(iter.getTree()), _pair(iter.getPair()), ptr_node(iter.base()) {}
            operator IteratorBid<Key, const value_type, const T, Tree, Compare>()
            { return IteratorBid<Key, const value_type, const T, Tree, Compare>(_tree, _pair, ptr_node); }
            IteratorBid& operator=(const IteratorBid &iter) {
                _tree = iter.getTree();
                _pair = iter.getPair();
                ptr_node = iter.base();
                return *this;
            }
            reference operator*() const { return *_pair; }
            pointer operator->() const { return &this->operator*(); }
            Tree getTree() const { return _tree; }
            pointer getPair() const { return _pair; }
            T* base() const { return ptr_node; }
            IteratorBid& operator++() {
                if (ptr_node != NULL && ptr_node->right == NULL) {
                    T* p = _tree.getParent(_tree.root, _pair->first);
                    while (p != NULL && ft::compare<Key, Key, Compare>(p->_pair->first, _pair->first))
                        p = _tree.getParent(_tree.root, p->_pair->first);
                    ptr_node = p;
                    if (ptr_node == NULL) _pair = NULL;
                    else _pair = p->_pair;
                    return *this;
                }
                T* p = ptr_node->right;
                while (p->left != NULL)
                    p = p->left;
                ptr_node = p;
                if (ptr_node == NULL) _pair = NULL;
                else _pair = p->_pair;
                return *this;
            }
            IteratorBid operator++(int) {
                IteratorBid tmp = *this;
                ++(*this);
                return tmp;
            }
            IteratorBid& operator--() {
                if (ptr_node && ptr_node->left == NULL) {
                    T* p = _tree.getParent(_tree.root, _pair->first);
                    while (p != NULL && ft::compare<Key, Key, Compare>(_pair->first, p->_pair->first))
                        p = _tree.getParent(_tree.root, p->_pair->first);
                    ptr_node = p;
                    if (ptr_node == NULL) _pair = NULL;
                    else _pair = p->_pair;
                    _pair = p->_pair;
                    return *this;
                }
                T* p;
                if (!ptr_node)
                    p = _tree.maxValueNode(_tree.root);
                else {
                    p = ptr_node->left;
                    while (p->right != NULL)
                        p = p->right;
                }
                ptr_node = p;
                if (ptr_node == NULL) _pair = NULL;
                else _pair = p->_pair;
                return *this;
            }
            IteratorBid operator--(int) {
                IteratorBid tmp = *this;
                --(*this);
                return tmp;
            }
            template <class Iter> bool operator==(const Iter& b) { return base() == b.base(); };
            template <class Iter> bool operator!=(const Iter& b) { return !(base() == b.base()); };
        private:
            Tree    _tree;
            pointer _pair;
            T*      ptr_node;
    };
}