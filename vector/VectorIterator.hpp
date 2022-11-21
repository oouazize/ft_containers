#pragma once
#include <iostream>
#include "../tools/utils.hpp"

namespace ft
{
    //-b -----------------iterator_traits------------------
    template<class Iterator>
    class iterator_traits
    {
        public:
            typedef typename Iterator::value_type        value_type;
            typedef typename Iterator::pointer           pointer;
            typedef typename Iterator::reference         reference;
            typedef typename Iterator::difference_type   difference_type;
            typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    class iterator_traits<T*>
    {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef std::ptrdiff_t difference_type;
            typedef std::random_access_iterator_tag iterator_category;
    };

    template<class T>
    class iterator_traits<const T*>
    {
        public:
            typedef T value_type;
            typedef const T* pointer;
            typedef const T& reference;
            typedef std::ptrdiff_t difference_type;
            typedef std::random_access_iterator_tag iterator_category;
    };
    
    //-r ---------------------iterator---------------------
        template <class T> class VectorIterator {
        public:
            typedef typename iterator_traits<T*>::value_type            value_type;
            typedef typename iterator_traits<T*>::pointer               pointer;
            typedef typename iterator_traits<T*>::reference             reference;
            typedef typename iterator_traits<T*>::difference_type       difference_type;
            typedef typename iterator_traits<T*>::iterator_category     iterator_category;

            VectorIterator() : m_ptr(nullptr) {}
            VectorIterator(pointer ptr) : m_ptr(ptr) {}
            VectorIterator(const VectorIterator &iter) {m_ptr = iter.m_ptr;}
            operator VectorIterator<const value_type>() {return VectorIterator<const value_type>(m_ptr);}
            VectorIterator& operator=(pointer other) {m_ptr = other; return *this;}
            reference operator*() {return *m_ptr; }
            pointer operator->() { return &this->operator*(); }
            difference_type operator+ (const VectorIterator& other) const {
                difference_type n = static_cast<difference_type>(m_ptr + other.m_ptr);
                return n;
            }
            difference_type operator- (const VectorIterator& other) const {
                difference_type n = static_cast<difference_type>(m_ptr - other.m_ptr);
                return n;
            }
            pointer base() const { return m_ptr; }
            template <class Iter1, class Iter2> friend bool operator<(const VectorIterator<Iter1>& a, const VectorIterator<Iter2>& b) { return a.base() < b.base(); }
            template <class Iter1, class Iter2> friend bool operator<=(const VectorIterator<Iter1>& a, const VectorIterator<Iter2>& b) { return a.base() <= b.base(); }
            template <class Iter1, class Iter2> friend bool operator>(const VectorIterator<Iter1>& a, const VectorIterator<Iter2>& b) { return a.base() > b.base(); }
            template <class Iter1, class Iter2> friend bool operator>=(const VectorIterator<Iter1>& a, const VectorIterator<Iter2>& b) { return a.base() >= b.base(); }
            VectorIterator operator+(difference_type n) { VectorIterator tmp = *this; tmp.m_ptr = m_ptr + n; return tmp; }
            VectorIterator operator-(difference_type n) { VectorIterator tmp = *this; tmp.m_ptr = m_ptr - n; return tmp; }
            VectorIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
            VectorIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
            VectorIterator& operator++() { m_ptr++; return *this; }
            VectorIterator operator++(int) {
                VectorIterator tmp = *this;
                ++m_ptr;
                return tmp;
            }
            VectorIterator& operator--() { m_ptr--; return *this; }
            VectorIterator operator--(int) {
                VectorIterator tmp = *this;
                --m_ptr;
                return tmp;
            }
            const reference operator[](difference_type n) const {return *(m_ptr + n);}
            bool operator==(const VectorIterator& b) { return m_ptr == b.m_ptr; };
            bool operator!=(const VectorIterator& b) { return !(m_ptr == b.m_ptr); };
            template <class iterator> friend VectorIterator<iterator> operator+ ( typename VectorIterator<iterator>::difference_type n, const VectorIterator<iterator>& rev_it) {
                return  (rev_it.m_ptr + n);
            }
        protected:
            pointer m_ptr;
    };
}