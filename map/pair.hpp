#pragma once

#include <iostream>

namespace ft {

    template <class T1, class T2> struct pair {
        public:
            typedef T1  first_type;
            typedef T2  second_type;

            first_type  first;
            second_type second;

            pair() : first(), second() {}

            pair (const first_type& a, const second_type& b) : first(a), second(b) {}
            
            template<class U, class V>
            pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

            pair& operator= (const pair& pr) {
                first = pr.first;
                second = pr.second;
                return *this;
            }

            ~pair() {}

            template <class t1, class t2>
            friend bool operator== (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return lhs.first == rhs.first && lhs.second == rhs.second; }

            template <class t1, class t2>
            friend bool operator!= (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return !(lhs == rhs); }

            template <class t1, class t2>
            friend bool operator<  (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return lhs.first < rhs.first || ((lhs.first == rhs.first) && (lhs.second < rhs.second)); }

            template <class t1, class t2>
            friend bool operator<= (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return !(rhs < lhs); }

            template <class t1, class t2>
            friend bool operator>  (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return rhs < lhs; }

            template <class t1, class t2>
            friend bool operator>= (const pair<t1,t2>& lhs, const pair<t1,t2>& rhs)
            { return !(lhs < rhs); }
    };

    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
      return ( pair<T1,T2>(x,y) );
    }
}