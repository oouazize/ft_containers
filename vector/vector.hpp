#pragma once
#include <iostream>
#include <algorithm>
#include "../tools/utils.hpp"
#include "../tools/ReverseIterator.hpp"
#include "VectorIterator.hpp"

namespace ft {

    template < class T, class Alloc = std::allocator<T> > class vector
    {
        public:
            typedef Alloc                                           allocator_type;
            typedef typename allocator_type::value_type             value_type;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::difference_type        difference_type;
            typedef VectorIterator<value_type>                      iterator;
            typedef VectorIterator<const value_type>                const_iterator;
            typedef ft::Reverse_Iterator<iterator>                  reverse_iterator;
            typedef ft::Reverse_Iterator<const_iterator>            const_reverse_iterator;

            explicit vector (const allocator_type& alloc = allocator_type()) : _m_alloc(alloc), _m_begin(nullptr), _m_size(0), _m_capacity(0) {}

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _m_alloc(alloc), _m_begin(nullptr), _m_size(0), _m_capacity(0) {
                assign(n, val);
            }

            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : _m_alloc(alloc), _m_begin(nullptr), _m_size(0), _m_capacity(0) {
                assign(first, last);
            }

            vector (const vector& x) {
                if (_m_begin) {
                    _m_size = 0;
                    _m_capacity = 0;
                }
                *this = x;
            }

            vector& operator= (const vector& x) {
                if (this != &x)
                    assign(x.begin(), x.end());
                return *this;
            }

            ~vector() {
                clear();
                if (_m_capacity) _m_alloc.deallocate(_m_begin, _m_capacity);
                _m_capacity = 0;
            }


            //-v --------________ITERATORS:_________-------- //

            iterator begin() {return iterator(_m_begin);}
            const_iterator begin() const {return const_iterator(_m_begin);}

            iterator end() {return iterator(_m_begin + _m_size);}
            const_iterator end() const {return const_iterator(_m_begin + _m_size);}

            reverse_iterator rbegin() {return reverse_iterator(end());}
            const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

            reverse_iterator rend() {return reverse_iterator(begin());}
            const_reverse_iterator rend() const {return const_reverse_iterator(begin());}


            //-o --------________RELATIONAL OPERATORS:_________-------- //

            friend bool operator== (const vector& lhs, const vector& rhs) {
                if (lhs.size() != rhs.size()) return false;
                return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
            }

            friend bool operator!= (const vector& lhs, const vector& rhs) {
                return !(lhs == rhs);
            }

            friend bool operator<  (const vector& lhs, const vector& rhs) {
                return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
            }

            friend bool operator<= (const vector& lhs, const vector& rhs) {
                if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs) return true;
                return false;
            }

            friend bool operator>  (const vector& lhs, const vector& rhs) {
                return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
            }

            friend bool operator>= (const vector& lhs, const vector& rhs) {
                if (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || lhs == rhs) return true;
                return false;
            }


            //-r --------________CAPACITY:_________-------- //
            size_type size() const {return _m_size;}

            size_type max_size() const {
                if (PTRDIFF_MAX < _m_alloc.max_size())
                    return PTRDIFF_MAX;
                return _m_alloc.max_size();
            }

            void resize (size_type n, value_type val = value_type()) {
                if (n < size())
                    while (_m_size > n) pop_back();
                else {
                    reserve(n);
                    for (size_type i = n; n > _m_size; i--) push_back(val);
                }
            }

            size_type capacity() const {return _m_capacity;}

            bool empty() const {return begin() == end();}

            void reserve (size_type n) {
                if (n <= _m_capacity) return ;
                if (n > max_size()) _m_begin = _m_alloc.allocate(n);
                size_type old_size = size();
                bool check = empty();
                allocator_type tmp;
                pointer tmp_bg;
                if (!check) {
                    tmp_bg = tmp.allocate(_m_size);
                    for (size_type i = 0; i < _m_size; ++i)
                        tmp.construct(tmp_bg + i, _m_begin[i]);
                    clear();
                    _m_size = 0;
                }
                if (_m_capacity) _m_alloc.deallocate(_m_begin, _m_capacity);
                _m_capacity = 0;
                _m_begin = _m_alloc.allocate(n);
                _m_size = old_size;
                if (!check) {
                    for(size_type i = 0; i < old_size; i++)
                        _m_alloc.construct(_m_begin + i, tmp_bg[i]);
                    for (int i = _m_size - 1; i >= 0; i--)
                        tmp.destroy(tmp_bg + i);
                    tmp.deallocate(tmp_bg, _m_size);
                }
                _m_capacity = n;
            }


            //-b --------________ELEMENT ACCESS:_________-------- //

            reference operator[](size_type n) {
                if (n >= _m_size) throw std::out_of_range("vector");
                return _m_begin[n];
            }

            const_reference operator[] (size_type n) const {
                if (n >= _m_size) throw std::out_of_range("vector");
                return _m_begin[n];
            }

            reference at(size_type n) {
                if (n >= _m_size) throw std::out_of_range("vector");
                return _m_begin[n];
            }

            const_reference at (size_type n) const {
                if (n >= _m_size) throw std::out_of_range("vector");
                return _m_begin[n];
            }

            reference front() {return *begin();}
            const_reference front() const {return *begin();}

            reference back() {return *(end() - 1);}
            const_reference back() const {return *(end() - 1);}


            //-g --------________MODIFIERS:_________-------- //

            void assign (size_type n, const value_type& val) {
                clear();
                if (n > _m_capacity) reserve(n);
                for (size_type i = 0; i < n; i++)
                    _m_alloc.construct(_m_begin + i, val);
                _m_size = n;
            }

            template <class InputIterator> void assign (InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
                vector tmp;
                for (; first != last; first++)
                    tmp.push_back(*first);
                size_type n = tmp.size();
                clear();
                if (n > _m_capacity) reserve(n);
                for (size_type i = 0; i < n; i++, _m_size++)
                    _m_alloc.construct(_m_begin + i, tmp[i]);
            }

            void push_back (const value_type& val) {
                if (size() == capacity()) {
					int next_capacity = (size() > 0) ? (int)(capacity() * 2) : 1;
					reserve(next_capacity);
				}
                else if(size() == 0) reserve(capacity());
                _m_alloc.construct(_m_begin + _m_size, val);
                _m_size++;
            }

            void pop_back ()
            {
                if (!empty()) {
                    _m_alloc.destroy(_m_begin + _m_size - 1);
                    _m_size -= 1;
                }
                else
                    _m_size = SIZE_T_MAX;
            }

            iterator insert (iterator position, const value_type& val) {
                size_type i = 0;
                size_type j = 0;
                vector tmp(*this);
                size_type pos = position - begin();
                if (_m_size + 1 > capacity())
                    (_m_capacity) ? reserve(capacity() * 2) : reserve(1);
                clear();
                while(i < pos)
                    _m_alloc.construct(_m_begin + i++, tmp[j++]);
                _m_alloc.construct(_m_begin + i++, val);
                _m_size = tmp.size() + 1;
                while (i < _m_size)
                    _m_alloc.construct(_m_begin + i++, tmp[j++]);
                return _m_begin + pos;
            }

            void insert (iterator position, size_type n, const value_type& val) {
                if (!size()) {
                    reserve(n);
                    for (; n != 0; n--) push_back(val);
                }
                else if (!n) return ;
                else {
                    size_type pos = position - begin();
                    size_type old_size = size();
                    if (_m_size + n > capacity()) {
                        (_m_size + n > _m_capacity * 2) ? reserve(_m_size + n) : reserve(_m_capacity * 2);
                        position = _m_begin + pos;
                    }
                    for(size_type i = 0; i < n; i++)
                        _m_alloc.construct(_m_begin + _m_size + i, val);
                    _m_size += n;
                    iterator last = _m_begin + old_size;
                    (pos != old_size) ? last-- : last;
                    iterator endl = _m_begin + _m_size - 1;
                    for (; last != position; last--, endl--)
                        *endl = *last;
                    *endl = *last;
                    position += n;
                    for(; last != position; last++) *last = val;
                }
            }

            template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
                vector tmp;
                for (; first != last; first++)
                    tmp.push_back(*first);
                size_type pos = position - begin();
                size_type n = tmp.size();
                if (n) {
                    //reserve
                    size_type old_size = size();
                    if (_m_size + n > capacity()) {
                        (_m_size + n > _m_capacity * 2) ? reserve(_m_size + n) : reserve(_m_capacity * 2);
                        position = _m_begin + pos;
                    }
                    _m_size += n;
                    iterator last = _m_begin + old_size;
                    if (pos != old_size) last--;
                    iterator endl = _m_begin + _m_size - 1;
                    for (; last != position; last--) {
                        if (endl >= iterator(_m_begin + old_size)) _m_alloc.construct(&(*endl), *last);
                        else *endl = *last;
                        endl--;
                    }
                    if (endl >= iterator(_m_begin + old_size)) _m_alloc.construct(&(*endl), *last);
                    else *endl = *last;
                    position += n;
                    for(size_type i = 0; last != position; last++) {
                        if(last >= iterator(_m_begin + _m_size - n) && !(pos == old_size && _m_begin + _m_size - 1 == &(*last)))
                            _m_alloc.construct(&(*last), tmp[i]);
                        else *last = tmp[i];
                        i++;
                    }
                }
            }

            iterator erase (iterator position) {
                size_type n = position - begin();
                vector vect2(begin(), position);
                vector vect3(position + 1, end());
                *this = vect2;
                insert(end(), vect3.begin(), vect3.end());
                iterator p = _m_begin + n;
                return p;
            }

            iterator erase (iterator first, iterator last) {
                iterator p = begin();
                if (first != last) {
                    size_type n = first - begin();
                    vector vect2(begin(), first);
                    vector vect3(last, end());
                    vect2.reserve(_m_capacity);
                    swap(vect2);
                    insert(end(), vect3.begin(), vect3.end());
                    p = _m_begin + n;
                }
                return p;
            }

            void clear() {
                for (int i = _m_size - 1; i >= 0; i--)
                    _m_alloc.destroy(_m_begin + i);
                _m_size = 0;
            }

            void swap (vector& x) {
                swapT(_m_begin, x._m_begin);
                swapT(_m_size, x._m_size);
                swapT(_m_capacity, x._m_capacity);
                swapT(_m_alloc, x._m_alloc);
            }

            template <typename X>
            void swapT(X& my_ptr, X& ptr) {
                X tmp = my_ptr;
                my_ptr = ptr;
                ptr = tmp;
            }

            template <class I, class alloc> friend void swap (vector<I,alloc>& x, vector<I,alloc>& y) { x.swap(y); }

            allocator_type get_allocator() const {return _m_alloc;}
        protected:
            allocator_type                        _m_alloc;
            pointer                               _m_begin;
            size_type                             _m_size;
            size_type                             _m_capacity;
    };
}