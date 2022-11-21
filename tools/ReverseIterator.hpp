#pragma once

#include "../tools/IteratorBid.hpp"
#include "../vector/VectorIterator.hpp"
namespace ft {
    template <class Iterator> class Reverse_Iterator {
        protected:
            Iterator current;
        public:
            typedef Iterator                                                iterator_type;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;

            Reverse_Iterator() : current() {}
            explicit Reverse_Iterator(iterator_type it) : current(it) {}
            template <class Iter> Reverse_Iterator(const Reverse_Iterator<Iter>& rev_it) : current(rev_it.base()) {}
            template <class Iter> const Reverse_Iterator& operator=(const Reverse_Iterator<Iter>& rev_it) { current = rev_it.base(); return *this; }
            iterator_type base() const {return current;}
            reference operator*() const { iterator_type tmp = current; return *--tmp;}
            pointer   operator->() const {return &this->operator*();}
            template <class Iter1, class Iter2> friend bool operator<(const Reverse_Iterator<Iter1>& a, const Reverse_Iterator<Iter2>& b) { return a.base() > b.base(); }
            template <class Iter1, class Iter2> friend bool operator<=(const Reverse_Iterator<Iter1>& a, const Reverse_Iterator<Iter2>& b) { return a.base() >= b.base(); }
            template <class Iter1, class Iter2> friend bool operator>(const Reverse_Iterator<Iter1>& a, const Reverse_Iterator<Iter2>& b) { return a.base() < b.base(); }
            template <class Iter1, class Iter2> friend bool operator>=(const Reverse_Iterator<Iter1>& a, const Reverse_Iterator<Iter2>& b) { return a.base() <= b.base(); }
            Reverse_Iterator& operator++() {--current; return *this;}
            Reverse_Iterator  operator++(int) {
                Reverse_Iterator tmp(*this);
                --current;
                return tmp;
            }
            Reverse_Iterator& operator--() {++current; return *this;}
            Reverse_Iterator  operator--(int) {
                Reverse_Iterator tmp(*this);
                ++current;
                return tmp;
            }
            Reverse_Iterator  operator+ (difference_type n) {return Reverse_Iterator(current - n);}
            Reverse_Iterator& operator+=(difference_type n) {current -= n; return *this;}
            Reverse_Iterator  operator- (difference_type n) {return Reverse_Iterator(current + n);}
            Reverse_Iterator& operator-=(difference_type n) {current += n; return *this;}
            reference         operator[](difference_type n) const {return current[-n - 1];}
            template <class Iter> bool operator==(const Iter& b) { return current == b.base(); };
            template <class Iter> bool operator!=(const Iter& b) { return !(current == b.base()); };
            friend difference_type operator- ( const Reverse_Iterator<Iterator>& lhs,  const Reverse_Iterator<Iterator>& rhs) {
                difference_type n = static_cast<difference_type>(rhs.base() - lhs.base());
                return n;
            }
            template <class iter> friend Reverse_Iterator<iter> operator+ ( typename Reverse_Iterator<iter>::difference_type n, const Reverse_Iterator<iter>& rev_it) {
                return  (Reverse_Iterator<iter>(rev_it.base() - n));
            }
    };
}