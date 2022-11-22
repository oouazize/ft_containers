/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:54:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/11/22 16:48:09 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "vector/vector.hpp"
#include "vector/VectorIterator.hpp"

typedef std::vector<std::string>    strvector;
typedef ft::vector<std::string>     mystrvector;
typedef std::vector<int>            intvector;
typedef ft::vector<int>             myintvector;
typedef std::vector<long>           longvector;
typedef ft::vector<long>            mylongvector;
typedef std::vector<char>           charvector;
typedef ft::vector<char>            mycharvector;
typedef std::vector<double>         doublevector;
typedef std::vector<float>          floatvector;
typedef ft::vector<float>           myfloatvector;
typedef ft::vector<double>          mydoublevector;
typedef ft::vector<double>          mydoublevector;

template<typename T>
void PRINT_LINE(std::ofstream& file, const char* str, T val)
{ file << str << val << std::endl; }

void PRINT_MSG(std::ofstream& file, const char* str)
{ file << str << std::endl; }

template <typename Vect>
void CHECK_AND_PRINT_ALL(std::ofstream& file, Vect& vec)
{
    file << "Capacity: " << vec.capacity() << std::endl;
    file << "SIZE: " << vec.size() << std::endl;
    file << "\nVector content:\n";
    for (typename Vect::iterator it = vec.begin(); it != vec.end(); ++it)
        file << *it << " ";
    file << std::endl << std::endl;
}

template <class Vect1, class Vect2>
void CHECK_ALL(std::ofstream& file, Vect1& vec, std::ofstream& my_file, Vect2& my_vec)
{
    CHECK_AND_PRINT_ALL(file, vec);
    CHECK_AND_PRINT_ALL(my_file, my_vec);
}

std::size_t s_size = 32;
std::size_t b_size = 64;
std::string s_string[32] = {
    "SVraqw904AjAsTAO", "py9WdoOqrFi7i3KU", "eKFVu6jBjWW0NaVU", "mTjur54V6Ztm10QR",
    "w8OFhblTVwwHBlqO", "31dvbLyYOBtBbbTc", "bvcncvncghhjhgjt", "3JxQQFeGMtj5CE6X",
    "BRFgn12vhwdSz549", "2vY7z3TaJW9pf2Ih", "bE1RYclshCm46YFs", "kXeoi5YPqSgDTs79",
    "TFsQP1dz8VVKzUj0", "b3wYQSWfA9sYuRj3", "xJ47jLbpy5YPqScr", "P2Wq43Gf8VhHsyu5",
    "yToPebHovnq9BQog", "3qvUVm2g1DFDlqh4", "RR9P41VD4sVjdnWl", "YdIZM4b1oGQPjpBe",
    "l1ZVKw7brHSimJgq", "cf4vqRzpfXWtl10G", "lYqaV0s8DowMZwzV", "8P1cwJNLoJvLjYqO",
    "XNbAX23CEijO5cRT", "tHAwCOVQbuoLaEP2", "l6uN8fiLl3WoG6j6", "t6l0lph9ALQdr4HX",
    "D94s8YF02LhrwOdl", "dLCiOdE8yuntu6cj", "aQFHgAuagn4dFLO1", "eGv7LW75qlV5Fkik"
};
std::string b_string[64] = {
    "uvg6Kcgdu1n3ajsv", "Acjgojb9JOgZwyMn", "ATZKCzOqgkhwuGlf", "MOhaJ6yjOf6nLPRA",
    "B2Tr42v6aww2nK7J", "e6GsiLuoDpVhJKZ1", "z0jXAV9keaLOY0Xf", "p2ZAosHJdmZh1C7N",
    "Pu3EuZY0TCOjdK0t", "z7jCHoHCSM8GygKB", "KoK83JrZxZkul7ty", "g8gfrZ5XwfzsvHvv",
    "7PGmkOSRnEt9mFIP", "d7mBIpPEsCpF9kdw", "XQo0LW5TdZnpUNOb", "U0m1RFFhAS6hmHHw",
    "PKfxJxIOnEQB90xn", "cZ5xyQMJhrKBK9A7", "cFBiwYw7JqEGy5Kt", "0KWfXxeFO6tByqcE",
    "3Fvq9NrhPXHIlIVx", "MSRDjRvHAGhiMtDe", "2joMh71jQkzg5L4V", "Mq4RRavSAO0ibp8Q",
    "SVraqw904AjAsTAO", "py9WdoOqrFi7i3KU", "eKFVu6jBjWW0NaVU", "mTjur54V6Ztm10QR",
    "w8OFhblTVwwHBlqO", "31dvbLyYOBtBbbTc", "bvcncvncghhjhgjt", "3JxQQFeGMtj5CE6X",
    "BRFgn12vhwdSz549", "2vY7z3TaJW9pf2Ih", "bE1RYclshCm46YFs", "kXeoi5YPqSgDTs79",
    "TFsQP1dz8VVKzUj0", "b3wYQSWfA9sYuRj3", "xJ47jLbpy5YPqScr", "P2Wq43Gf8VhHsyu5",
    "yToPebHovnq9BQog", "3qvUVm2g1DFDlqh4", "RR9P41VD4sVjdnWl", "YdIZM4b1oGQPjpBe",
    "l1ZVKw7brHSimJgq", "cf4vqRzpfXWtl10G", "lYqaV0s8DowMZwzV", "8P1cwJNLoJvLjYqO",
    "XNbAX23CEijO5cRT", "tHAwCOVQbuoLaEP2", "l6uN8fiLl3WoG6j6", "t6l0lph9ALQdr4HX",
    "D94s8YF02LhrwOdl", "dLCiOdE8yuntu6cj", "OaxUSm3N9Y8Ea7sS", "BgDAwXz7xJo5Rwqd",
    "xdk1dEoJ6zuVhkvo", "olIwtUEJgs1l9bCn", "dTS0x2uXtcgOJHb8", "DYvhLppGNZKboTrd",
    "DjNMtt9kzqvWHI6j", "1ZeTFlPniKnzhzgu", "76X6hqMf5IXxKPEs", "gzaapi9EZjiaLeK6"
};
double s_double[32] = {
    42.42f, 10.1f, 44.3f, 12.42f, 44.1f, 40.3f,
    32.42f, 48.1f, 45.3f, 22.42f, 40.1f, 46.3f,
    72.42f, 11.1f, 49.3f, 49.42f, 31.1f, 14.3f,
    50.42f, 71.1f, 73.3f, 55.42f, 82.1f, 83.3f,
    51.42f, 91.1f, 39.3f, 54.42f, 77.1f, 20.3f,
    53.42f, 80.1f
};
double b_double[64] = {
    42.42f, 10.1f, 44.3f, 12.42f, 44.1f, 40.3f,
    32.42f, 48.1f, 45.3f, 22.42f, 40.1f, 46.3f,
    72.42f, 11.1f, 49.3f, 49.42f, 31.1f, 14.3f,
    50.42f, 71.1f, 73.3f, 55.42f, 82.1f, 83.3f,
    51.42f, 91.1f, 39.3f, 54.42f, 77.1f, 20.3f,
    53.42f, 80.1f, 99.9f, 88.42f, 85.1f, 92.9f,
    52.42f, 83.1f, 91.9f, 57.42f, 82.1f, 90.9f,
    19.42f, 81.1f, 95.9f, 18.42f, 22.1f, 63.9f,
    16.42f, 21.1f, 67.9f, 15.42f, 23.1f, 65.9f,
    14.42f, 25.1f, 66.9f, 13.42f, 27.1f, 61.9f,
    11.42f, 28.1f, 60.9f, 10.42f
};
int s_int[32] = {
    42, 10, 47, 12, 44, 33, 32, 48,
    45, 68, 40, 46, 72, 62, 24, 49,
    31, 64, 50, 71, 73, 55, 82, 86,
    51, 91, 39, 54, 77, 20, 53, 80
};
int b_int[64] = {
    42, 10, 47, 12, 44, 33, 32, 48, 45, 68, 40, 46,
    72, 62, 24, 49, 31, 64, 50, 71, 73, 55, 82, 86,
    51, 91, 39, 54, 77, 20, 53, 80, 99, 88, 85, 92,
    52, 83, 97, 57, 87, 90, 19, 81, 95, 18, 22, 63,
    16, 21, 67, 15, 23, 65, 14, 25, 66, 13, 27, 61,
    11, 28, 60, 10
};

int main()
{
    std::ofstream STDFILE("std::vector");
    std::ofstream FTFILE("ft::vector");
    if (!STDFILE.is_open() || !FTFILE.is_open())
        throw std::ofstream::failure("Could not open the file");
    
    //-b ------------------------------------assign method--------------------------------
    STDFILE << "-------------------- [" << " assign method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " assign method " << "] --------------------\n" << std::endl;
    {
        strvector v;
        mystrvector my_v;

        v.assign(b_string, b_string + b_size);
        my_v.assign(b_string, b_string + b_size);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(65, "HelloWorld");
        my_v.assign(65, "HelloWorld");

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(s_string, s_string + s_size);
        my_v.assign(s_string, s_string + s_size);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }

    {
        // This test checks if vector works with iterators tagged as std::input_iterator_tag
        charvector v;
        mycharvector my_v;

        std::istringstream str("1 2 3 4 5 6 7");
        std::istringstream str1("1 2 3 4 5 6 7");
        std::istreambuf_iterator<char> it(str), end;
        std::istreambuf_iterator<char> it1(str1), end1;

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(it, end);
        my_v.assign(it1, end1);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }

    {
        charvector v;
        mycharvector my_v;

        v.assign(0, 'c');
        my_v.assign(0, 'c');

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(64, 'A');
        my_v.assign(64, 'A');

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(32, '5');
        my_v.assign(32, '5');

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(49, '8');
        my_v.assign(49, '8');

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.assign(77, '2');
        my_v.assign(77, '2');

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }

    //-b ------------------------------------assignment--------------------------------
    STDFILE << "-------------------- [" << " assignment " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " assignment " << "] --------------------\n" << std::endl;
    {
        strvector v1 = strvector(b_string, b_string + b_size);
        strvector v2;
        mystrvector my_v1 = mystrvector(b_string, b_string + b_size);
        mystrvector my_v2;

        v1 = v2;
        my_v1 = my_v2;

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);

        v2 = strvector(b_string, b_string + b_size);
        my_v2 = mystrvector(b_string, b_string + b_size);

        CHECK_ALL(STDFILE, v2, FTFILE, my_v2);

        v1 = v2;
        my_v1 = my_v2;

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);

        v2 = strvector(s_string, s_string + s_size);
        my_v2 = mystrvector(s_string, s_string + s_size);

        CHECK_ALL(STDFILE, v2, FTFILE, my_v2);

        v1 = v2;
        my_v1 = my_v2;

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);
    }
    //-b ------------------------------------at--------------------------------
    STDFILE << "-------------------- [" << " at " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " at " << "] --------------------\n" << std::endl;
    {
        const charvector v(64, 'a');
        const charvector my_v(64, 'a');

        try {
            intvector::const_reference c = v.at(38);

            STDFILE << "At: " << c << std::endl;
        } catch (std::out_of_range& e) {
            STDFILE << "Out of range exception"<< std::endl;
        }
        try {
            myintvector::const_reference c = my_v.at(38);

            FTFILE << "At: "<<  c << std::endl;
        } catch (std::out_of_range& e) {
            FTFILE << "Out of range exception"<< std::endl;
        }
    }

    {
        const intvector v(99, 64);
        const myintvector my_v(99, 64);

        try {
            intvector::const_reference c = v.at(99);

            STDFILE << "At: " << c << std::endl;
        } catch (std::out_of_range& e) {
            STDFILE << "Out of range exception"<< std::endl;
        }
        try {
            myintvector::const_reference c = my_v.at(99);

            FTFILE << "At: "<<  c << std::endl;
        } catch (std::out_of_range& e) {
            FTFILE << "Out of range exception"<< std::endl;
        }
    }
    //-b ------------------------------------back--------------------------------
    STDFILE << "-------------------- [" << " back " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " back " << "] --------------------\n" << std::endl;
    {
        const longvector v(1, 9);
        const mylongvector my_v(1, 9);

        STDFILE << "Back:" << v.back() << std::endl;
        FTFILE << "Back:" << my_v.back() << std::endl;

        longvector::const_reference b = v.back();
        mylongvector::const_reference my_b = my_v.back();
        if (&b != &v[0])
            STDFILE << "Wrong reference" << std::endl;
        if (&my_b != &my_v[0])
            FTFILE << "Wrong reference" << std::endl;
    }
    {
        longvector v(123, 543);
        mylongvector my_v(123, 543);
        v.push_back(10);
        my_v.push_back(10);

        STDFILE << "Back:" << v.back() << std::endl;
        FTFILE << "Back:" << my_v.back() << std::endl;

        longvector::const_reference b = v.back();
        mylongvector::const_reference my_b = my_v.back();
        if (&b != &v[122])
            STDFILE << "Wrong reference" << std::endl;
        if (&my_b != &my_v[122])
            FTFILE << "Wrong reference" << std::endl;
    }
    //-b ------------------------------------clear--------------------------------
    STDFILE << "-------------------- [" << " clear " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " clear " << "] --------------------\n" << std::endl;
    {
        intvector v;
        intvector v1(64, 420);
        myintvector my_v;
        myintvector my_v1(64, 420);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.clear();
        my_v.clear();

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);

        v1.clear();
        my_v1.clear();

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);

        v1.clear();
        my_v1.clear();

        CHECK_ALL(STDFILE, v1, FTFILE, my_v1);
    }
    //-b ------------------------------------relational operators--------------------------------
    STDFILE << "-------------------- [" << " relational operators " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " relational operators " << "] --------------------\n" << std::endl;
    {
        bool cond = true;
        {
            longvector v1;
            longvector v2;
            mylongvector my_v1;
            mylongvector my_v2;
            cond = (cond && (v1 != v2) == (my_v1 != my_v2));
            cond = (cond && (v1 > v2) == (my_v1 > my_v2));
            cond = (cond && (v1 >= v2) == (my_v1 >= my_v2));
            cond = (cond && (v1 < v2) == (my_v1 < my_v2));
            cond = (cond && (v1 <= v2) == (my_v1 <= my_v2));
            cond = (cond && (v1 == v2) == (my_v1 == my_v2));
        }
        {
            intvector v1(5, 64);
            intvector v2;
            myintvector my_v1(5, 64);
            myintvector my_v2;
            cond = (cond && (v1 != v2) == (my_v1 != my_v2));
            cond = (cond && (v1 > v2) == (my_v1 > my_v2));
            cond = (cond && (v1 >= v2) == (my_v1 >= my_v2));
            cond = (cond && (v1 < v2) == (my_v1 < my_v2));
            cond = (cond && (v1 <= v2) == (my_v1 <= my_v2));
            cond = (cond && (v1 == v2) == (my_v1 == my_v2));
        }
        {   
            intvector v1;
            intvector v2(5, 32);
            myintvector my_v1;
            myintvector my_v2(5, 32);
            cond = (cond && (v1 != v2) == (my_v1 != my_v2));
            cond = (cond && (v1 > v2) == (my_v1 > my_v2));
            cond = (cond && (v1 >= v2) == (my_v1 >= my_v2));
            cond = (cond && (v1 < v2) == (my_v1 < my_v2));
            cond = (cond && (v1 <= v2) == (my_v1 <= my_v2));
            cond = (cond && (v1 == v2) == (my_v1 == my_v2));
        }
        {
            intvector v1(5, 64);
            intvector v2(5, 48);
            myintvector my_v1(5, 64);
            myintvector my_v2(5, 48);
            cond = (cond && (v1 != v2) == (my_v1 != my_v2));
            cond = (cond && (v1 > v2) == (my_v1 > my_v2));
            cond = (cond && (v1 >= v2) == (my_v1 >= my_v2));
            cond = (cond && (v1 < v2) == (my_v1 < my_v2));
            cond = (cond && (v1 <= v2) == (my_v1 <= my_v2));
            cond = (cond && (v1 == v2) == (my_v1 == my_v2));
        }
        {
            intvector v1(10, 13);
            intvector v2(5, 48);
            myintvector my_v1(10, 13);
            myintvector my_v2(5, 48);
            cond = (cond && (v1 != v2) == (my_v1 != my_v2));
            cond = (cond && (v1 > v2) == (my_v1 > my_v2));
            cond = (cond && (v1 >= v2) == (my_v1 >= my_v2));
            cond = (cond && (v1 < v2) == (my_v1 < my_v2));
            cond = (cond && (v1 <= v2) == (my_v1 <= my_v2));
            cond = (cond && (v1 == v2) == (my_v1 == my_v2));
        }
        STDFILE << cond << std::endl;
        FTFILE << cond << std::endl;
    }
    //-b ------------------------------------empty method--------------------------------
    STDFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
    {
        {
            intvector v(0, 123);
            myintvector my_v(0, 123);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            if (v.empty()) PRINT_MSG(STDFILE, "Empty");
            if (my_v.empty()) PRINT_MSG(FTFILE, "Empty");
        }
        {
            intvector v;
            myintvector my_v;

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            if (v.empty()) PRINT_MSG(STDFILE, "Empty");
            if (my_v.empty()) PRINT_MSG(FTFILE, "Empty");
        }
        {
            intvector v(42, 64);
            myintvector my_v(42, 64);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            if (v.empty()) PRINT_MSG(STDFILE, "Empty");
            if (my_v.empty()) PRINT_MSG(FTFILE, "Empty");
        }
    }
    //-b ------------------------------------max_size method--------------------------------
    STDFILE << "-------------------- [" << " max_size method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " max_size method " << "] --------------------\n" << std::endl;
    {
        PRINT_LINE(STDFILE, "Char max size: ", charvector().max_size());
        PRINT_LINE(STDFILE, "Int max size: ", intvector().max_size());
        PRINT_LINE(STDFILE, "Long max size: ", longvector().max_size());
        PRINT_LINE(STDFILE, "Float max size: ", floatvector().max_size());

        PRINT_LINE(FTFILE, "Char max size: ", mycharvector().max_size());
        PRINT_LINE(FTFILE, "Int max size: ", myintvector().max_size());
        PRINT_LINE(FTFILE, "Long max size: ", mylongvector().max_size());
        PRINT_LINE(FTFILE, "Float max size: ", myfloatvector().max_size());
    }
    //-b ------------------------------------resize method--------------------------------
    STDFILE << "-------------------- [" << " resize method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " resize method " << "] --------------------\n" << std::endl;
    {
        strvector v;
        mystrvector my_v;

        v.resize(14, "HelloWorld");
        my_v.resize(14, "HelloWorld");

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.resize(6, "ABC");
        my_v.resize(6, "ABC");

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.resize(14, b_string[18]);
        my_v.resize(14, b_string[18]);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.resize(15, b_string[57]);
        my_v.resize(15, b_string[57]);
    }
    //-b ------------------------------------reserve method--------------------------------
    STDFILE << "-------------------- [" << " reserve method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " reserve method " << "] --------------------\n" << std::endl;
    {
        intvector v(b_int, b_int + b_size);
        myintvector my_v(b_int, b_int + b_size);

        v.reserve(0);
        my_v.reserve(0);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.reserve(32);
        my_v.reserve(32);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.reserve(48);
        my_v.reserve(48);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.reserve(1);
        my_v.reserve(1);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }
    //-b ------------------------------------push_back method--------------------------------
    STDFILE << "-------------------- [" << " push_back method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " push_back method " << "] --------------------\n" << std::endl;
    {
        doublevector v;
        mydoublevector my_v;

        for (int i = 0; i < 26; ++i) {
            v.push_back(45.0123);
            my_v.push_back(45.0123);
            CHECK_ALL(STDFILE, v, FTFILE, my_v);
        }

        v.push_back(6);
        my_v.push_back(6);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.push_back(-4356.8933);
        my_v.push_back(-4356.8933);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }
    //-b ------------------------------------pop_back method--------------------------------
    STDFILE << "-------------------- [" << " pop_back method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " pop_back method " << "] --------------------\n" << std::endl;
    {
        {
            doublevector v(s_double, s_double + s_size);
            mydoublevector my_v(s_double, s_double + s_size);

            v.pop_back();
            my_v.pop_back();

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            for (int i = 0; i < 10; ++i) {
                v.pop_back();
                my_v.pop_back();
            }

            CHECK_ALL(STDFILE, v, FTFILE, my_v);
        }
        {
            intvector v;
            myintvector my_v;

            v.pop_back();
            my_v.pop_back();

            PRINT_LINE(STDFILE, "Size: ", v.size());
            PRINT_LINE(FTFILE, "Size: ", my_v.size());
        }
    }
    //-b ------------------------------------insert method--------------------------------
    STDFILE << "-------------------- [" << " insert method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " insert method " << "] --------------------\n" << std::endl;
    {
        {
            intvector v;
            myintvector my_v;

            v.insert(v.end(), s_int, s_int + s_size - 10);
            my_v.insert(my_v.end(), s_int, s_int + s_size - 10);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            v.insert(v.begin() + 5, 9, -1);
            my_v.insert(my_v.begin() + 5, 9, -1);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            intvector::iterator it = v.insert(v.begin(), 64);
            myintvector::iterator my_it = my_v.insert(my_v.begin(), 64);

            PRINT_LINE(STDFILE, "It:", *it);
            PRINT_LINE(FTFILE, "It:", *it);
            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            for (int i = 0; i < 23; ++i) {
                it = v.insert(v.begin() + i + 2, i);
                my_it = my_v.insert(my_v.begin() + i + 2, i);
                PRINT_LINE(STDFILE, "It:", *it);
                PRINT_LINE(FTFILE, "It:", *my_it);
                CHECK_ALL(STDFILE, v, FTFILE, my_v);
            }

            v.insert(v.end(), 12, 42);
            my_v.insert(my_v.end(), 12, 42);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            v.insert(v.begin() + 12, b_int, b_int + b_size);
            my_v.insert(my_v.begin() + 12, b_int, b_int + b_size);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);

            v.insert(v.begin(), 69);
            my_v.insert(my_v.begin(), 69);

            CHECK_ALL(STDFILE, v, FTFILE, my_v);
        }
    }
    //-b ------------------------------------erase method--------------------------------
    STDFILE << "-------------------- [" << " erase method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " erase method " << "] --------------------\n" << std::endl;
    {
        strvector v(b_string, b_string + b_size);
        mystrvector my_v(b_string, b_string + b_size);

        v.erase(v.begin(), v.begin());
        my_v.erase(my_v.begin(), my_v.begin());

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.erase(v.end(), v.end());
        my_v.erase(my_v.end(), my_v.end());

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.erase(v.begin());
        my_v.erase(my_v.begin());

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.erase(v.end() - 1);
        my_v.erase(my_v.end() - 1);

        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        strvector::iterator it = v.erase(v.begin() + 3, v.begin() + 16);
        mystrvector::iterator my_it = my_v.erase(my_v.begin() + 3, my_v.begin() + 16);

        PRINT_LINE(STDFILE, "It:", *it);
        PRINT_LINE(FTFILE, "It:", *my_it);
        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        it = v.erase(v.begin() + 9);
        my_it = my_v.erase(my_v.begin() + 9);

        PRINT_LINE(STDFILE, "It:", *it);
        PRINT_LINE(FTFILE, "It:", *my_it);
        CHECK_ALL(STDFILE, v, FTFILE, my_v);

        v.erase(v.begin(), v.end());
        my_v.erase(my_v.begin(), my_v.end());

        CHECK_ALL(STDFILE, v, FTFILE, my_v);
    }
    //-b ------------------------------------iterator comparisons--------------------------------
    STDFILE << "-------------------- [" << " iterator comparisons " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " iterator comparisons " << "] --------------------\n" << std::endl;
    {
        // std::vector
        intvector v(b_int, b_int + b_size);
        intvector::iterator it = v.begin();
        intvector::iterator it2 = v.begin();
        intvector::const_iterator cit = v.begin();
        intvector::const_iterator cit2 = v.begin();

        // ft::vector
        myintvector my_v(b_int, b_int + b_size);
        myintvector::iterator my_it = my_v.begin();
        myintvector::iterator my_it2 = my_v.begin();
        myintvector::const_iterator my_cit = my_v.begin();
        myintvector::const_iterator my_cit2 = my_v.begin();

        // std::vector
        if (it == v.begin()) PRINT_MSG(STDFILE, "Equal iterators");
        if (cit == it) PRINT_MSG(STDFILE, "Equal const iterators.");
        if (cit == v.begin()) PRINT_MSG(STDFILE, "Equal const iterators");
        ++it;
        cit += 6;
        if (it != v.end()) PRINT_MSG(STDFILE, "Not Equal iterators");
        if (cit != it) PRINT_MSG(STDFILE, "Not Equal const iterators.");
        if (cit < it + 1) PRINT_MSG(STDFILE, "Less than...");
        if (cit <= cit) PRINT_MSG(STDFILE, "Less than or equal");
        if (it2 >= cit2) PRINT_MSG(STDFILE, "Greater than or equal");
        if (cit != v.end()) PRINT_MSG(STDFILE, "Not Equal const iterators");
        if (cit != it) PRINT_MSG(STDFILE, "Not Equal const iterators.");

        // ft::vector
        if (my_it == my_v.begin()) PRINT_MSG(FTFILE, "Equal iterators");
        if (my_cit == my_it) PRINT_MSG(FTFILE, "Equal const iterators.");
        if (my_cit == my_v.begin()) PRINT_MSG(FTFILE, "Equal const iterators");
        ++my_it;
        my_cit += 6;
        if (my_it != my_v.end()) PRINT_MSG(FTFILE, "Not Equal iterators");
        if (my_cit != my_it) PRINT_MSG(FTFILE, "Not Equal const iterators.");
        if (my_cit < my_it + 1) PRINT_MSG(FTFILE, "Less than...");
        if (my_cit <= my_cit) PRINT_MSG(FTFILE, "Less than or equal");
        if (my_it2 >= my_cit2) PRINT_MSG(FTFILE, "Greater than or equal");
        if (my_cit != my_v.end()) PRINT_MSG(FTFILE, "Not Equal const iterators");
        if (my_cit != my_it) PRINT_MSG(FTFILE, "Not Equal const iterators.");
    }
    //-b ------------------------------------swap method--------------------------------
    STDFILE << "-------------------- [" << " swap method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " swap method " << "] --------------------\n" << std::endl;
    {
        {
            intvector v1(s_int, s_int + s_size);
            intvector v2(b_int, b_int + b_size);
            myintvector my_v1(s_int, s_int + s_size);
            myintvector my_v2(b_int, b_int + b_size);

            v1.swap(v2);
            my_v1.swap(my_v2);

            CHECK_ALL(STDFILE, v1, FTFILE, my_v1);
            CHECK_ALL(STDFILE, v2, FTFILE, my_v2);
        }
        {
            intvector v1;
            intvector v2;
            myintvector my_v1;
            myintvector my_v2;

            intvector::iterator it = v2.begin();
            myintvector::iterator my_it = my_v2.begin();

            v1.swap(v2);
            intvector::iterator it1 = v1.begin();
            if (it1 == it) PRINT_MSG(STDFILE, "Swap Correct");

            my_v1.swap(my_v2);
            myintvector::iterator my_it1 = my_v1.begin();
            if (my_it1 == my_it) PRINT_MSG(FTFILE, "Swap Correct");
        }
    }
    //-b ------------------------------------get_allocator method--------------------------------
    STDFILE << "-------------------- [" << " get_allocator method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " get_allocator method " << "] --------------------\n" << std::endl;
    {
        intvector v;
        myintvector my_v;

        intvector::pointer begin = v.get_allocator().allocate(10);
        myintvector::pointer _begin = my_v.get_allocator().allocate(10);
        v.get_allocator().deallocate(begin, 10);
        my_v.get_allocator().deallocate(_begin, 10);
    }
    STDFILE.close();
    FTFILE.close();
    if (system("diff ft::vector std::vector") == 0) std::cout << "\033[1;32mOK" << std::endl;
    else std::cout << "\033[1;31mKO" << std::endl;
}