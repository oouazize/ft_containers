#pragma once
#include <iostream>
#include "../vector/vector.hpp"
#include <algorithm>
#include "../vector/VectorIterator.hpp"

namespace ft
{
    //-r --------------------enable_if---------------------
    template <bool Cond, class T = void>
    struct enable_if
    {
    };
    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    //-v -------------------is_integral--------------------
    template <typename>
    struct is_integral
    {
        static const bool value = false;
    };
    template <>
    struct is_integral<bool>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char16_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char32_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<wchar_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<signed char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<short int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned short int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long long int>
    {
        static const bool value = true;
    };

    //-b ----------------------equal-----------------------

    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
               typename enable_if<!std::is_integral<InputIterator1>::value, InputIterator1>::type * = 0,
               typename enable_if<!std::is_integral<InputIterator2>::value, InputIterator2>::type * = 0)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        for (; first1 != last1; first1++, first2++)
            if (!pred(*first1, *first2))
                return false;
        return true;
    }

    //-g -------------lexicographical_compare--------------

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 typename enable_if<!std::is_integral<InputIterator1>::value, InputIterator1>::type = 0,
                                 typename enable_if<!std::is_integral<InputIterator2>::value, InputIterator2>::type = 0)
    {
        for (; first1 != last1; first1++, first2++)
        {
            if (first2 == last2 || *first1 > *first2)
                return false;
            else if (*first1 < *first2)
                return true;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        for (; first1 != last1; first1++, first2++)
        {
            if ((!comp(*first1, *first2) && *first1 != *first2) || first2 == last2)
                return false;
            else if (comp(*first1, *first2))
                return true;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2>
    size_t lenghToIterate(InputIterator1 first, InputIterator2 last,
                          typename enable_if<!std::is_integral<InputIterator1>::value, InputIterator1>::type = 0,
                          typename enable_if<!std::is_integral<InputIterator2>::value, InputIterator2>::type = 0)
    {
        size_t count = 0;
        for (; last != first; first++)
            count++;
        return count;
    }
}