/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:54:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/11/19 14:16:48 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "map/AVLtree.hpp"
#include "map/map.hpp"
#include "map/pair.hpp"

typedef std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator>               iter_def;
typedef ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator>                  ft_iter_def;
typedef std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator>   const_iter_def;
typedef ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator>      ft_const_iter_def;

template<typename T>
void PRINT_LINE(std::ofstream& file, const char* str, T val)
{ file << str << val << std::endl; }

void PRINT_MSG(std::ofstream& file, const char* str)
{ file << str << std::endl; }

template <typename It>
void print_map(std::ofstream& file, It first, It last)
{
    for (; first != last; ++first)
        file << "Key: " << first->first << " Value: " << first->second << " ";
    file << std::endl;
}

template <class M>
void PRINT(std::ofstream& file, M& m)
{
    PRINT_LINE(file, "Size:", m.size());
    file << "\nMap content:\n";
    print_map(file, m.begin(), m.end());
    file << std::endl;
}

template <class M, class P>
void PRINT_ALL(std::ofstream& file, M& m, std::ofstream& file1, P& p)
{
    PRINT(file, m);
    PRINT(file1, p);
}

template <class M, class P>
void PRINT_PAIR_REF(std::ofstream& file, M& m, std::ofstream& file1, P& p)
{
    PRINT_LINE(file, "Key:", m.first);
    PRINT_LINE(file, "Value:", m.second);

    PRINT_LINE(file1, "Key:", p.first);
    PRINT_LINE(file1, "Value:", p.second);
}

template <class M, class P>
void PRINT_INS_PAIR(std::ofstream& file, M& m, std::ofstream& file1, P& p)
{
    PRINT_PAIR_REF(file, *m.first, file1, *p.first);
    PRINT_LINE(file, "Inserted:", m.second ? "true" : "false");
    PRINT_LINE(file1, "Inserted:", p.second ? "true" : "false");
}

template <typename T, typename P>
void init_array_int_str(T* arr, P* arr1, std::size_t size)
{
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "oWurB8fBAIBQq1ZnlFiR", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "d8NpBFRFI87WxlYiRzJB",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

    for (std::size_t i = 0; i < size; ++i) {
        int random = rand();
        arr[i] = T(random, x[i]);
        arr1[i] = P(random, x[i]);
    }
}

template <typename T, typename P>
void init_array_str_str(T* arr, P* arr1, std::size_t size)
{
    std::string x[32] = { "RxWAUMME3GtF9Zbv3a4M", "3z82NvciqTwWW2Lp7MET", "2beuhrfBZvjdkmfqV9yn",
                          "AuIhF3lUgwT0OMy8DuUx", "dVW2KAL06gB4s7rEf508", "jnsp7MGfl5wZNZVfQSvp",
                          "p26Kfhz0Iof6rJDy27vc", "bnWXfp2eexq7MPpcmRSI", "tMEU0L6RNvqDAaV6HN0e",
                          "POcbaPteUMFfltrwdu7r", "epDGhJZoKoL4i1HO67XS", "o83N1RTIeOafqBfqeAYh",
                          "aYRtwuDT8k7k7iIfTrtU", "fEPXIREoFGKXqnNKySG5", "QrqmIbVVIQzf8WKBxiga",
                          "k5NSg0Dq0b9ewfrhYdy7", "Tf9dsqBADfMeWVQGG3Zk", "dS2LouElpUXsXNCClr4B",
                          "tsvf3JaWNg5JlSDZs1Dm", "oWurB8fBAIBQq1ZnlFiR", "HdCk0Gm8Gn3eqcVYxcYD",
                          "Spt36tVcEkIFjwogWli0", "c25H1u6DF9RVdagn81DA", "AjWfT7TlXgzSKOywpoTH",
                          "eRJ98PUF2tSMX6zpDOi4", "6KhIc7LvaTTwklmmbjBO", "QN1iAuoSNQ5WvHeSeSSL",
                          "7g5wfNllowIaqMUVjywr", "b38gJrosdk9xEQ2K8Gbu", "KdVdRVLHJg9Bazc4cpM7",
                          "COJeGmQEzjXwqKCAnd6J", "2k6XCpXEkP7QoST6uYoy" };

    std::string y[32] = { "TZ3QuE3ZNUbFrEpQhgcY", "BX2lyPzOWRIznb34T5OT", "v7lPrSeDokdBIUXR9QGh",
                          "nAQxkuEYL5k1Er7FspKu", "r8T4oZaWBI1m7sPBEDz3", "pdxM9tJrYZskZla7L7yM",
                          "dIIx6eKTfygu24SNKa32", "tw04BOo705mdWxuDciNO", "q94icFprhKrrFXLvjEN3",
                          "uM25BWUl14NTlTwFsNIv", "2oTV9fXUESLQqzvsPFmd", "W6ASLRzrlOggx5b7CtYN",
                          "bz4BQ7rLU203RNwwmbMK", "jfWgRPiuy1P3NGDPWmbe", "eaaFugCSOOU5my4y4SkG",
                          "1IRLC9sfQI5AzDYeotLd", "gGd4FiUEJwgvhOCSHu9g", "9K0ZhqlbyDCJXYXHoEIN",
                          "VTmk8m7rbEGl8ntGpTCQ", "eRJ98PUF2tSMX6zpDOi4", "wFMJIDAbjYnJkxMxkAtL",
                          "JCOXV4iPcIt72DcNnbuY", "oWurB8fBAIBQq1ZnlFiR", "YVPp2jPqK3jmif7yY14r",
                          "JBMhRRtLY3QX3x1ZVDCs", "Uwo5PD2RLMx5ByW9Rscq", "O4Q6DPBJHOelMtBKc9GQ",
                          "Bq0H2eqnuCYqyj9F5Lkn", "P2fJf0TYN92iUXkwELjG", "f656ltXlumpc7YyPVjan",
                          "YQfr76LAA1xKokfq8HpL", "6utvLeZ9t0IM4OkdfAQ2" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = T(x[i], y[i]);
        arr1[i] = P(x[i], y[i]);
    }
}

#define SETUP_MAP()                                                                                                                            \
    std::pair<int, std::string> intstr_arr[64];                                                                                                \
    ft::pair<int, std::string> intstr_arr1[64];                                                                                                \
    init_array_int_str<std::pair<int, std::string>, ft::pair<int, std::string> >(intstr_arr, intstr_arr1, 64);                                 \
    std::pair<std::string, std::string> strstr_arr[32];                                                                                        \
    ft::pair<std::string, std::string> strstr_arr1[32];                                                                                        \
    init_array_str_str<std::pair<std::string, std::string>, ft::pair<std::string, std::string> >(strstr_arr, strstr_arr1, 32);                 \
    std::size_t intstr_size = 64;                                                                                                              \
    std::size_t strstr_size = 32;                                                                                                              \
    (void)intstr_arr;                                                                                                                          \
    (void)strstr_arr;                                                                                                                          \
    (void)intstr_size;                                                                                                                         \
    (void)strstr_size;

typedef std::map<int, std::string, std::less<int>, std::allocator<std::pair<const int, std::string> > >
    intmap;
typedef ft::map<int, std::string, std::less<int>, std::allocator<ft::pair<const int, std::string> > >
    intmap1;
typedef std::map<std::string, std::string, std::less<std::string>, std::allocator<std::pair<const std::string, std::string> > >
    strmap;
typedef ft::map<std::string, std::string, std::less<std::string>, std::allocator<ft::pair<const std::string, std::string> > >
    strmap1;

int main()
{
    SETUP_MAP();

    std::ofstream STDFILE("std::map");
    std::ofstream FTFILE("ft::map");
    if (!STDFILE.is_open() || !FTFILE.is_open())
        throw std::ofstream::failure("Could not open the file");
    
    //-b ------------------------------------assignement--------------------------------
    STDFILE << "-------------------- [" << " assignement " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " assignement " << "] --------------------\n" << std::endl;
    {
        intmap m1;
        intmap m2;
        intmap1 my_m1;
        intmap1 my_m2;

        m1 = m2;
        my_m1 = my_m2;

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);

        m2 = intmap(intstr_arr, intstr_arr + intstr_size);
        my_m2 = intmap1(intstr_arr1, intstr_arr1 + intstr_size);

        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m1 = m2;
        my_m1 = my_m2;

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);

        m1 = intmap(intstr_arr, intstr_arr + 10);
        my_m1 = intmap1(intstr_arr1, intstr_arr1 + 10);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);

        m2 = m1;
        my_m2 = my_m1;

        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);
    }
    //-b ------------------------------------at method--------------------------------
    STDFILE << "-------------------- [" << " at method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " at method " << "] --------------------\n" << std::endl;
    {
        {
            intmap m;
            intmap1 m1;

            try {
                std::string& x = m.at(6);

                PRINT_LINE(STDFILE, "At:", x);
            } catch (std::out_of_range& e) {
                PRINT_LINE(STDFILE, "Out of range exception ", 6);
            }

            try {
                std::string& x = m1.at(6);

                PRINT_LINE(FTFILE, "At:", x);
            } catch (std::out_of_range& e) {
                PRINT_LINE(FTFILE, "Out of range exception ", 6);
            }
        }

        {
            intmap m(intstr_arr, intstr_arr + intstr_size);
            intmap1 m1(intstr_arr1, intstr_arr1 + intstr_size);

            m.insert(std::make_pair(64, "64"));
            m1.insert(ft::make_pair(64, "64"));

            try {
                std::string& x = m.at(64);

                PRINT_LINE(STDFILE, "At:", x);
            } catch (std::out_of_range& e) {
                PRINT_LINE(STDFILE, "Wrong out of range exception ", 64);
            }

            try {
                std::string& x = m1.at(64);

                PRINT_LINE(FTFILE, "At:", x);
            } catch (std::out_of_range& e) {
                PRINT_LINE(FTFILE, "Wrong out of range exception ", 64);
            }
        }
    }
    //-b ------------------------------------clear method--------------------------------
    STDFILE << "-------------------- [" << " clear method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " clear method " << "] --------------------\n" << std::endl;
    {
        strmap m;
        strmap1 m1;

        PRINT_ALL(STDFILE, m, FTFILE, m1);

        m.clear();
        m1.clear();

        PRINT_ALL(STDFILE, m, FTFILE, m1);

        m.insert(strstr_arr, strstr_arr + 16);
        m1.insert(strstr_arr1, strstr_arr1 + 16);

        PRINT_ALL(STDFILE, m, FTFILE, m1);

        m.clear();
        m1.clear();

        PRINT_ALL(STDFILE, m, FTFILE, m1);
    }
    //-b ------------------------------------empty method--------------------------------
    STDFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
    {
        strmap m;
        strmap1 m1;

        PRINT_LINE(STDFILE, "Empty:", m.empty());
        PRINT_LINE(FTFILE, "Empty:", m1.empty());

        m.insert(std::make_pair("Hello", "World"));
        m1.insert(ft::make_pair("Hello", "World"));

        PRINT_LINE(STDFILE, "Empty:", m.empty());
        PRINT_LINE(FTFILE, "Empty:", m1.empty());

        m.erase(m.begin());
        m1.erase(m1.begin());

        PRINT_LINE(STDFILE, "Empty:", m.empty());
        PRINT_LINE(FTFILE, "Empty:", m1.empty());

        intmap v(intstr_arr, intstr_arr + intstr_size);
        intmap1 v1(intstr_arr1, intstr_arr1 + intstr_size);

        PRINT_LINE(STDFILE, "Empty:", v.empty());
        PRINT_LINE(FTFILE, "Empty:", v1.empty());
    }
    //-b ------------------------------------insert method--------------------------------
    STDFILE << "-------------------- [" << " insert method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " insert method " << "] --------------------\n" << std::endl;
    {
        {
            typedef std::pair<intmap::iterator, bool> ins_pair;
            typedef ft::pair<intmap1::iterator, bool> ins_pair1;

            intmap m;
            intmap1 m1;

            ins_pair p = m.insert(std::make_pair(64, "64str"));
            ins_pair1 p1 = m1.insert(ft::make_pair(64, "64str"));

            PRINT_INS_PAIR(STDFILE, p, FTFILE, p1);

            p = m.insert(std::make_pair(64, "Double"));
            p1 = m1.insert(ft::make_pair(64, "Double"));

            PRINT_INS_PAIR(STDFILE, p, FTFILE, p1);

            p = m.insert(std::make_pair(0, "0str"));
            p1 = m1.insert(ft::make_pair(0, "0str"));

            PRINT_INS_PAIR(STDFILE, p, FTFILE, p1);

            p = m.insert(std::make_pair(-23, "-23str"));
            p1 = m1.insert(ft::make_pair(-23, "-23str"));

            PRINT_INS_PAIR(STDFILE, p, FTFILE, p1);

            p = m.insert(std::make_pair(64, "dfgs"));
            p1 = m1.insert(ft::make_pair(64, "dfgs"));

            PRINT_INS_PAIR(STDFILE, p, FTFILE, p1);
        }
        {
            intmap m;
            intmap1 m1;

            intmap::iterator it = m.insert(m.end(), std::make_pair(64, "OussamaOz"));
            intmap1::iterator it1 = m1.insert(m1.end(), ft::make_pair(64, "OussamaOz"));

            PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

            it = m.insert(m.end(), std::make_pair(64, "Test"));
            it1 = m1.insert(m1.end(), ft::make_pair(64, "Test"));

            PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

            it = m.insert(m.end(), std::make_pair(100, "100DH"));
            it1 = m1.insert(m1.end(), ft::make_pair(100, "100DH"));

            PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

            it = m.end();
            it1 = m1.end();
            --it;
            --it1;

            it = m.insert(it, std::make_pair(100, "8*4852"));
            it1 = m1.insert(it1, ft::make_pair(100, "4852"));

            PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

            it = m.insert(it, std::make_pair(69, "42"));
            it1 = m1.insert(it1, ft::make_pair(69, "42"));

            PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);
        }
        {
            intmap m;
            intmap1 m1;

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(intstr_arr + 16, intstr_arr + 16);
            m1.insert(intstr_arr1 + 16, intstr_arr1 + 16);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(intstr_arr + 1, intstr_arr + 7);
            m1.insert(intstr_arr1 + 1, intstr_arr1 + 7);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(intstr_arr, intstr_arr + 1);
            m1.insert(intstr_arr1, intstr_arr1 + 1);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(intstr_arr, intstr_arr + 17);
            m1.insert(intstr_arr1, intstr_arr1 + 17);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(intstr_arr, intstr_arr + intstr_size);
            m1.insert(intstr_arr1, intstr_arr1 + intstr_size);

            PRINT_ALL(STDFILE, m, FTFILE, m1);
        }
    }
    //-b ------------------------------------erase method--------------------------------
    STDFILE << "-------------------- [" << " erase method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " erase method " << "] --------------------\n" << std::endl;
    {
        {
            intmap m(intstr_arr, intstr_arr + 25);
            intmap1 m1(intstr_arr1, intstr_arr1 + 25);

            intmap::iterator it = m.begin();
            intmap1::iterator it1 = m1.begin();

            m.erase(it);
            m1.erase(it1);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            it = m.begin();
            it1 = m1.begin();

            std::advance(it, 21);
            std::advance(it1, 21);

            m.erase(it);
            m1.erase(it1);

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            it = m.end();
            it1 = m1.end();

            std::advance(it, -10);
            std::advance(it1, -10);

            m.erase(it);
            m1.erase(it1);

            PRINT_ALL(STDFILE, m, FTFILE, m1);
        }
        {
            strmap m;
            strmap1 m1;

            m.erase(m.begin(), m.end());
            m1.erase(m1.begin(), m1.end());

            PRINT_ALL(STDFILE, m, FTFILE, m1);

            m.insert(strstr_arr, strstr_arr + strstr_size);
            m1.insert(strstr_arr1, strstr_arr1 + strstr_size);

            m.erase(m.begin(), m.end());
            m1.erase(m1.begin(), m1.end());

            PRINT_ALL(STDFILE, m, FTFILE, m1);
        }
    }
    //-b ------------------------------------swap method--------------------------------
    STDFILE << "-------------------- [" << " swap method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " swap method " << "] --------------------\n" << std::endl;
    {
        intmap m1(intstr_arr, intstr_arr + 32);
        intmap m2;
        intmap1 my_m1(intstr_arr1, intstr_arr1 + 32);
        intmap1 my_m2;

        swap(m1, m2);
        swap(my_m1, my_m2);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m1.clear();
        m1.swap(m2);
        my_m1.clear();
        my_m1.swap(my_m2);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m1.clear();
        m2.swap(m1);
        my_m1.clear();
        my_m2.swap(my_m1);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m1.insert(std::make_pair(42, "N42"));
        my_m1.insert(ft::make_pair(42, "N42"));
        swap(m1, m2);
        swap(my_m1, my_m2);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m2.insert(intstr_arr, intstr_arr + intstr_size);
        my_m2.insert(intstr_arr1, intstr_arr1 + intstr_size);
        m1.swap(m2);
        my_m1.swap(my_m2);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);

        m1.clear();
        m1.swap(m2);
        m1.clear();
        m1.swap(m2);
        my_m1.clear();
        my_m1.swap(my_m2);
        my_m1.clear();
        my_m1.swap(my_m2);

        PRINT_ALL(STDFILE, m1, FTFILE, my_m1);
        PRINT_ALL(STDFILE, m2, FTFILE, my_m2);
    }
    //-b ------------------------------------key_comp method--------------------------------
    STDFILE << "-------------------- [" << " key_comp method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " key_comp method " << "] --------------------\n" << std::endl;
    {
        intmap m(intstr_arr, intstr_arr + intstr_size);
        intmap1 m1(intstr_arr1, intstr_arr1 + intstr_size);

        intmap::iterator it = m.begin();
        intmap1::iterator it1 = m1.begin();

        intmap::const_iterator cit = m.begin();
        intmap1::const_iterator cit1 = m1.begin();

        intmap::key_compare comp = m.key_comp();
        intmap1::key_compare comp1 = m1.key_comp();

        if (comp(it->first, cit->first) == comp1(it1->first, cit1->first)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, 14);
        std::advance(cit, 5);
        std::advance(it1, 14);
        std::advance(cit1, 5);

        if (comp(it->first, cit->first) == comp1(it1->first, cit1->first)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, 7);
        std::advance(cit, 3);
        std::advance(it1, 7);
        std::advance(cit1, 3);

        if (comp(it->first, cit->first) == comp1(it1->first, cit1->first)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, -3);
        std::advance(cit, 12);
        std::advance(it1, -3);
        std::advance(cit1, 12);

        if (comp(it->first, cit->first) == comp1(it1->first, cit1->first)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, -1);
        std::advance(cit, 1);
        std::advance(it1, -1);
        std::advance(cit1, 1);

        if (comp(it->first, cit->first) == comp1(it1->first, cit1->first)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }
    }
    //-b ------------------------------------value_comp method--------------------------------
    STDFILE << "-------------------- [" << " value_comp method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " value_comp method " << "] --------------------\n" << std::endl;
    {
        intmap m(intstr_arr, intstr_arr + intstr_size);
        intmap1 m1(intstr_arr1, intstr_arr1 + intstr_size);

        intmap::iterator it = m.begin();
        intmap::iterator it2 = m.begin();
        intmap::value_compare comp = m.value_comp();
        intmap1::iterator my_it = m1.begin();
        intmap1::iterator my_it2 = m1.begin();
        intmap1::value_compare comp1 = m1.value_comp();

        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }
        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, 14);
        std::advance(it2, 5);
        std::advance(my_it, 14);
        std::advance(my_it2, 5);

        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, 7);
        std::advance(it2, 3);

        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, -3);
        std::advance(it2, 12);
        std::advance(my_it, -3);
        std::advance(my_it2, 12);

        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }

        std::advance(it, -1);
        std::advance(it2, 1);
        std::advance(my_it, -1);
        std::advance(my_it2, 1);

        if (comp(*it, *it2) == comp1(*my_it, *my_it2)) {
            PRINT_MSG(STDFILE, "OK");
            PRINT_MSG(FTFILE, "OK");
        }
    }
    //-b ------------------------------------find method--------------------------------
    STDFILE << "-------------------- [" << " find method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " find method " << "] --------------------\n" << std::endl;
    {
        strmap m(strstr_arr, strstr_arr + strstr_size);
        strmap1 m1(strstr_arr1, strstr_arr1 + strstr_size);

        strmap::iterator it = m.find("ABCD");
        strmap1::iterator it1 = m1.find("ABCD");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

        m.insert(std::make_pair("12345", "etsriueruy394w"));
        m.insert(std::make_pair("abcd", "sfdge4ta4tqtawefa"));
        m.insert(std::make_pair("123", "adfgagrawetawtawef"));
        m.insert(std::make_pair("1234", "asdfgaetfawfasdf"));
        m.insert(std::make_pair("ab", "adfawtawefgzsdfg"));
        m.insert(std::make_pair("yz", "gftrjr5y4agwe3ta"));
        m.insert(std::make_pair("64", "mhj,i;y9o67eysetrgerg"));
        m1.insert(ft::make_pair("12345", "etsriueruy394w"));
        m1.insert(ft::make_pair("abcd", "sfdge4ta4tqtawefa"));
        m1.insert(ft::make_pair("123", "adfgagrawetawtawef"));
        m1.insert(ft::make_pair("1234", "asdfgaetfawfasdf"));
        m1.insert(ft::make_pair("ab", "adfawtawefgzsdfg"));
        m1.insert(ft::make_pair("yz", "gftrjr5y4agwe3ta"));
        m1.insert(ft::make_pair("64", "mhj,i;y9o67eysetrgerg"));

        it = m.find("12345");
        it1 = m1.find("12345");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

        it = m.find("1234");
        it1 = m1.find("1234");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

        it = m.find("123");
        it1 = m1.find("123");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

        it = m.find("123");
        it1 = m1.find("123");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);

        it = m.find("z");
        it1 = m1.find("z");

        if (it != m.end() && it1 != m1.end()) PRINT_PAIR_REF(STDFILE, *it, FTFILE, *it1);
    }
    //-b ------------------------------------count method--------------------------------
    STDFILE << "-------------------- [" << " count method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " count method " << "] --------------------\n" << std::endl;
    {
        intmap m(intstr_arr, intstr_arr + intstr_size);
        intmap1 m1(intstr_arr1, intstr_arr1 + intstr_size);

        intmap::size_type c = m.count(64);
        intmap1::size_type c1 = m1.count(64);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(145);
        c1 = m1.count(145);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(11);
        c1 = m1.count(11);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        m.insert(std::make_pair(34, "seiurhg8347wo83twerw"));
        m.insert(std::make_pair(2, "dsghesrzarherheat43"));
        m.insert(std::make_pair(9, "awgfawe4t3A4YSDFGAS"));
        m.insert(std::make_pair(3, "dzfg45yrthsdfgshju"));
        m.insert(std::make_pair(22, "j564wedfshgj6ee5yegrs"));
        m.insert(std::make_pair(10, "cfngcvcx56;oiliuee"));
        m1.insert(ft::make_pair(34, "seiurhg8347wo83twerw"));
        m1.insert(ft::make_pair(2, "dsghesrzarherheat43"));
        m1.insert(ft::make_pair(9, "awgfawe4t3A4YSDFGAS"));
        m1.insert(ft::make_pair(3, "dzfg45yrthsdfgshju"));
        m1.insert(ft::make_pair(22, "j564wedfshgj6ee5yegrs"));
        m1.insert(ft::make_pair(10, "cfngcvcx56;oiliuee"));

        c = m.count(34);
        c1 = m1.count(34);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(2);
        c1 = m1.count(2);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(9);
        c1 = m1.count(9);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        m.erase(9);
        m1.erase(9);

        c = m.count(9);
        c1 = m1.count(9);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(10);
        c1 = m1.count(10);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);

        c = m.count(22);
        c1 = m1.count(22);

        PRINT_LINE(STDFILE, "Count:", c);
        PRINT_LINE(FTFILE, "Count:", c1);
    }
    //-b ------------------------------------lower_bound method--------------------------------
    STDFILE << "-------------------- [" << " lower_bound method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " lower_bound method " << "] --------------------\n" << std::endl;
    {
        bool cond = true;
        intmap m;
        intmap1 m1;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150};
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            m1.insert(ft::make_pair(arr[i], "value"));
        }
        intmap const c_m(m.begin(), m.end());
        intmap1 const c_m1(m1.begin(), m1.end());
        cond = (cond && (m.lower_bound(15)->first == m1.lower_bound(15)->first));
        cond = (cond && (m.lower_bound(65)->first == m1.lower_bound(65)->first));
        cond = (cond && (m.lower_bound(63)->first == m1.lower_bound(63)->first));
        cond = (cond && (m.lower_bound(120)->first == m1.lower_bound(120)->first));
        cond = (cond && (m.lower_bound(70)->first == m1.lower_bound(70)->first));

        cond = (cond && (c_m.lower_bound(15)->first == c_m1.lower_bound(15)->first));
        cond = (cond && (c_m.lower_bound(65)->first == c_m1.lower_bound(65)->first));
        cond = (cond && (c_m.lower_bound(63)->first == c_m1.lower_bound(63)->first));
        cond = (cond && (c_m.lower_bound(120)->first == c_m1.lower_bound(120)->first));
        cond = (cond && (c_m.lower_bound(70)->first == c_m1.lower_bound(70)->first));
        PRINT_MSG(STDFILE, "OK");
        if (cond) PRINT_MSG(FTFILE, "OK");
        else PRINT_MSG(FTFILE, "KO");
    }
    //-b ------------------------------------upper_bound method--------------------------------
    STDFILE << "-------------------- [" << " upper_bound method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " upper_bound method " << "] --------------------\n" << std::endl;
    {
        bool cond = true;
        intmap m;
        intmap1 m1;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150};
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            m1.insert(ft::make_pair(arr[i], "value"));
        }
        intmap const c_m(m.begin(), m.end());
        intmap1 const c_m1(m1.begin(), m1.end());
        cond = (cond && (m.upper_bound(15)->first == m1.upper_bound(15)->first));
        cond = (cond && (m.upper_bound(65)->first == m1.upper_bound(65)->first));
        cond = (cond && (m.upper_bound(63)->first == m1.upper_bound(63)->first));
        cond = (cond && (m.upper_bound(120)->first == m1.upper_bound(120)->first));
        cond = (cond && (m.upper_bound(70)->first == m1.upper_bound(70)->first));
        cond = (cond && (m.upper_bound(150)->first == m1.upper_bound(150)->first));

        cond = (cond && (c_m.upper_bound(15)->first == c_m1.upper_bound(15)->first));
        cond = (cond && (c_m.upper_bound(65)->first == c_m1.upper_bound(65)->first));
        cond = (cond && (c_m.upper_bound(63)->first == c_m1.upper_bound(63)->first));
        cond = (cond && (c_m.upper_bound(120)->first == c_m1.upper_bound(120)->first));
        cond = (cond && (c_m.upper_bound(70)->first == c_m1.upper_bound(70)->first));
        cond = (cond && (c_m.upper_bound(150)->first == c_m1.upper_bound(150)->first));
        PRINT_MSG(STDFILE, "OK");
        if (cond) PRINT_MSG(FTFILE, "OK");
        else PRINT_MSG(FTFILE, "KO");
    }
    //-b ------------------------------------equal_range method--------------------------------
    STDFILE << "-------------------- [" << " equal_range method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " equal_range method " << "] --------------------\n" << std::endl;
    {
        bool cond = true;
        iter_def            res;
        ft_iter_def         res1;
        const_iter_def      c_res;
        ft_const_iter_def   c_res1;
        intmap m;
        intmap1 m1;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            m1.insert(ft::make_pair(arr[i], "value"));
        }
        intmap const c_m(m.begin(), m.end());
        intmap1 const c_m1(m1.begin(), m1.end());

        res = m.equal_range(15);
        res1 = m1.equal_range(15);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));
        res = m.equal_range(65);
        res1 = m1.equal_range(65);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));
        res = m.equal_range(63);
        res1 = m1.equal_range(63);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));
        res = m.equal_range(120);
        res1 = m1.equal_range(120);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));
        res = m.equal_range(70);
        res1 = m1.equal_range(70);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));
        res = m.equal_range(150);
        res1 = m1.equal_range(150);
        cond = (cond && (res1.first->first == res.first->first) && (res1.second->first == res.second->first));

        c_res = c_m.equal_range(15);
        c_res1 = c_m1.equal_range(15);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        c_res = c_m.equal_range(65);
        c_res1 = c_m1.equal_range(65);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        c_res = c_m.equal_range(63);
        c_res1 = c_m1.equal_range(63);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        c_res = c_m.equal_range(120);
        c_res1 = c_m1.equal_range(120);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        c_res = c_m.equal_range(70);
        c_res1 = c_m1.equal_range(70);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        c_res = c_m.equal_range(150);
        c_res1 = c_m1.equal_range(150);
        cond = (cond && (c_res1.first->first == c_res.first->first) && (c_res1.second->first == c_res.second->first));
        PRINT_MSG(STDFILE, "OK");
        if (cond) PRINT_MSG(FTFILE, "OK");
        else PRINT_MSG(FTFILE, "KO");
    }
    STDFILE.close();
    FTFILE.close();
    if (system("diff ft::map std::map") == 0) std::cout << "\033[1;32mOK" << std::endl;
    else std::cout << "\033[1;31mKO" << std::endl;
}