#pragma once

#include "pair.hpp"
#include <algorithm>
#include "../tools/utilsMap.hpp"


    template<
        class Key,
        class Val,
        class value_type,
        class allocator_type,
        class Compare = std::less<Key>
    > class AVLtree {
        private:
            allocator_type alloc_pair;
        public:
            class TreeNode
            {
                public:
                    TreeNode*                   left;
                    value_type*                  _pair;
                    TreeNode*                   right;
                    int                         height;
                    TreeNode() : left(nullptr), _pair(), right(nullptr), height(1) {}
            };

            typedef typename allocator_type::template rebind<TreeNode>::other    tree_node_allocator;

            TreeNode*       root;
            size_t          _size;

            AVLtree() : root(NULL), _size(0) {}
            AVLtree(const AVLtree& other) : root(other.root), _size(other._size) {}
            AVLtree& operator=(const AVLtree& other) {root = other.getRoot(), _size = other.size(); return *this;}
            bool IsEmpty() const {
                if (root == NULL) return true;
                return false;
            }

            TreeNode* createNode(const Key& k, Val value) {            
                TreeNode* tmp = _alloc.allocate(1);
                _alloc.construct(tmp, TreeNode());
                tmp->left = NULL;
                tmp->_pair = alloc_pair.allocate(1);
                alloc_pair.construct(tmp->_pair, ft::make_pair(k, value));
                tmp->right = NULL;
                return tmp;
            }

            TreeNode* getRoot() const { return root; }
            size_t  size() const { return _size; }

            //-y -----_____Insert - Delete____-----
            //-y -----________________________-----

            TreeNode* Insert(TreeNode* ptr, TreeNode* new_node) {
                if (ptr == NULL) {
                    ptr = new_node;
                    _size++;
                    return ptr;
                }
            
                if (ft::compare<Key, Key, Compare>(new_node->_pair->first, ptr->_pair->first))
                    ptr->left = Insert(ptr->left, new_node);
                else if (ft::compare<Key, Key, Compare>(ptr->_pair->first, new_node->_pair->first))
                    ptr->right = Insert(ptr->right, new_node);
                else
                {
                    alloc_pair.destroy(new_node->_pair);
                    _alloc.destroy(new_node);
                    alloc_pair.deallocate(new_node->_pair, 1);
                    _alloc.deallocate(new_node, 1);
                    return ptr;
                }
            
                ptr->height = 1 + std::max(height(ptr->left), height(ptr->right));
                return balance(ptr);
            }

            TreeNode* deleteNode(TreeNode *node, Key _key) {
                // Find the node and delete it
                if (node == NULL) return node;
                if (ft::compare<Key, Key, Compare>(node->_pair->first, _key)) node->right = deleteNode(node->right, _key);
                else if (ft::compare<Key, Key, Compare>(_key, node->_pair->first)) node->left = deleteNode(node->left, _key);
                else {
                // case 1: leaf node && one child
                    if (node->left == NULL || node->right == NULL) {
                        TreeNode *tmp = node->left ? node->left : node->right;
                        if (tmp == NULL) {
                            tmp = node;
                            node = NULL;
                        }
                        else {
                            alloc_pair.destroy(node->_pair);
                            alloc_pair.construct(node->_pair, ft::make_pair(tmp->_pair->first, tmp->_pair->second));
                            if (tmp->left == NULL || tmp->right == NULL) {
                                node->left = NULL;
                                node->right = NULL;
                            }
                        }
                        alloc_pair.destroy(tmp->_pair);
                        _alloc.destroy(tmp);
                        alloc_pair.deallocate(tmp->_pair, 1);
                        _alloc.deallocate(tmp, 1);
                        _size--;
                    }
                    // case 2: two childrean
                    else {
                        TreeNode *tmp = minValueNode(node->right);
                        alloc_pair.destroy(node->_pair);
                        alloc_pair.construct(node->_pair, ft::make_pair(tmp->_pair->first, tmp->_pair->second));
                        node->right = deleteNode(node->right, tmp->_pair->first);
                    }
                }
                if (node == NULL)
                    return node;
                node->height = 1 + std::max(height(node->left),  height(node->right));
                return balance(node);
            }

            //-y -----_____Search - Height - Print____-----
            //-y -----________________________________-----

            TreeNode* Search(TreeNode* TmpRoot, Key _key) const {
                if (TmpRoot == NULL || TmpRoot->_pair->first == _key)
                    return TmpRoot;
                else if (ft::compare<Key, Key, Compare>(TmpRoot->_pair->first, _key))
                    return Search(TmpRoot->right, _key);
                return Search(TmpRoot->left, _key);
            }

            TreeNode* UpperBound(TreeNode* TmpRoot, Key _key) const {
                if (TmpRoot == NULL)
                    return TmpRoot;
                if (!ft::compare<Key, Key, Compare>(_key, TmpRoot->_pair->first) && TmpRoot->right) //greater then
                        return UpperBound(TmpRoot->right, _key);
                else if (ft::compare<Key, Key, Compare>(_key, TmpRoot->_pair->first) && TmpRoot->left) //smaller then
                        return UpperBound(TmpRoot->left, _key);
                while (!ft::compare<Key, Key, Compare>(_key, TmpRoot->_pair->first) && TmpRoot != root)
                    TmpRoot = getParent(root, TmpRoot->_pair->first);
                if (TmpRoot == root)
                    return NULL;
                return TmpRoot;
            }

            TreeNode* getParent(TreeNode* TmpRoot, Key _key) const {
                if (TmpRoot == NULL || TmpRoot->_pair->first == _key)
                    return NULL;
                else if (ft::compare<Key, Key, Compare>(_key, TmpRoot->_pair->first) && TmpRoot->left->_pair->first == _key)
                    return TmpRoot;
                else if (ft::compare<Key, Key, Compare>(TmpRoot->_pair->first, _key) && TmpRoot->right->_pair->first == _key)
                    return TmpRoot;
                else if (ft::compare<Key, Key, Compare>(TmpRoot->_pair->first, _key))
                    return getParent(TmpRoot->right, _key);
                return getParent(TmpRoot->left, _key);
            }

            int height(TreeNode* TmpRoot) const {
                if (TmpRoot == NULL)
                    return 0;
                return TmpRoot->height;
            }

            void printLevelOrderBFS(TreeNode* TmpRoot) const {
                int h = height(TmpRoot);
                for(int i = 0; i <= h; i++)
                    printGivenLevel(TmpRoot, i);
            }

            void printGivenLevel(TreeNode* tmp, int level) const {
                if (tmp == NULL) return;
                if (level == 0) std::cout << tmp->_pair->first << std::endl;
                else {
                    printGivenLevel(tmp->left, level - 1);
                    printGivenLevel(tmp->right, level - 1);
                }
            }

            size_t getSize(TreeNode* TmpRoot) const {
                size_t size = 0;
                int h = height(TmpRoot);
                for(int i = 0; i <= h; i++)
                    iterOfLevel(TmpRoot, i, &size);
                return size;
            }

            void iterOfLevel(TreeNode* tmp, int level, size_t* size) const {
                if (tmp == NULL) return;
                if (level == 0) *size += 1;
                else {
                    iterOfLevel(tmp->left, level - 1, size);
                    iterOfLevel(tmp->right, level - 1, size);
                }
            }

            TreeNode* minValueNode(TreeNode* node) const {
                TreeNode* tmp = node;
                while (tmp && tmp->left != NULL)
                    tmp = tmp->left;
                return tmp;
            }

            TreeNode* maxValueNode(TreeNode* node) const {
                TreeNode* tmp = node;
                while (tmp && tmp->right != NULL)
                    tmp = tmp->right;
                return tmp;
            }

            //-y -----_________----Balance----_________-----
            //-y -----_________---------------_________-----

            TreeNode* balance(TreeNode* node) {
                int bf = getBalanceFactor(node);
                if (bf > 1) {
                    if (getBalanceFactor(node->left) < 0)
                        node->left = left_rotation(node->left);
                    return right_rotation(node);
                }
                if (bf < -1) {
                    if (getBalanceFactor(node->right) > 0)
                        node->right = right_rotation(node->right);
                    return left_rotation(node);
                }
                return node;
            }

            TreeNode* right_rotation(TreeNode* tmp) {
                TreeNode* x = tmp->left;
                TreeNode* r = x->right;

                x->right = tmp;
                tmp->left = r;
                tmp->height = 1 + std::max(height(tmp->left), height(tmp->right));
                x->height = 1 + std::max(height(x->left), height(x->right));
                return x;
            }

            TreeNode* left_rotation(TreeNode* tmp) {
                TreeNode* x = tmp->right;
                TreeNode* r = x->left;

                x->left = tmp;
                tmp->right = r;
                tmp->height = 1 + std::max(height(tmp->left), height(tmp->right));
                x->height = 1 + std::max(height(x->left), height(x->right));
                return x;
            }

            int getBalanceFactor(TreeNode* node) {
                if (node == NULL) 
                    return -1;
                return (height(node->left) - height(node->right));
            }

            void swap(AVLtree& x) {
                std::swap(root, x.root);
                std::swap(_size, x._size);
            }

            void clear () {
                while (size() > 0)
                    root = deleteNode(root, root->_pair->first);
            }
            tree_node_allocator _alloc;
};

template <class InputIterator1, class InputIterator2>
    bool equalNode(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (first1->first != first2->first || first1->second != first2->second)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

template <class InputIterator1, class InputIterator2>
bool comp(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
    if (first2 == last2)
        return (first2 != last2);
    while (first1 != last1)
    {
        if (first1->first < first2->first)
            return true;
        else if (first1->first > first2->first)
            return false;
        else if (first1->second < first2->second)
            return true;
        else if (first1->second > first2->second)
            return false;
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

