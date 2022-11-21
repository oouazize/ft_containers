/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:54:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/11/19 09:19:07 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "stack/stack.hpp"

template<typename T>
void PRINT_LINE(std::ofstream& file, const char* str, T val)
{ file << str << val << std::endl; }

void PRINT_MSG(std::ofstream& file, const char* str)
{ file << str << std::endl; }

template <typename C, typename D>
void add_values(C& s, D& d, typename C::value_type value, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i, ++value) {
        s.push(value);
        d.push(value);
    }
}

template <typename C, typename D>
void add_value(C& s, D& d, typename C::value_type value, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i) {
        s.push(value);
        d.push(value);
    }
}

int main()
{
    std::ofstream STDFILE("std::stack");
    std::ofstream FTFILE("ft::stack");
    if (!STDFILE.is_open() || !FTFILE.is_open())
        throw std::ofstream::failure("Could not open the file");
    
    //-b ------------------------------------operator==--------------------------------
    STDFILE << "-------------------- [" << " operator== " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " operator== " << "] --------------------\n" << std::endl;
    {
        {
            std::stack<long> v1;
            std::stack<long> v2;
            ft::stack<long> my_v1;
            ft::stack<long> my_v2;

            if (v1 == v2) PRINT_MSG(STDFILE, "Equal");
            if (my_v1 == my_v2) PRINT_MSG(FTFILE, "Equal");

            add_values(v1, my_v1, 0, 5);

            if (v1 == v2) PRINT_MSG(STDFILE, "Equal.");
            if (my_v1 == my_v2) PRINT_MSG(FTFILE, "Equal.");

            add_values(v2, my_v2, 0, 9);

            if (v1 == v2) PRINT_MSG(STDFILE, "Equal..");
            if (my_v1 == my_v2) PRINT_MSG(FTFILE, "Equal..");
        }
        {
            ft::stack<long> v1;
            ft::stack<long> v2;
            ft::stack<long> my_v1;
            ft::stack<long> my_v2;

            add_values(v1, my_v1, 1, 64);
            add_values(v2, my_v2, 1, 64);

            if (v1 == v2) PRINT_MSG(STDFILE, "Equal...");
            if (my_v1 == my_v2) PRINT_MSG(FTFILE, "Equal...");
        }
    }
    //-b ------------------------------------operator<=--------------------------------
    STDFILE << "-------------------- [" << " operator<= " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " operator<= " << "] --------------------\n" << std::endl;
    {
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq");

            add_value(v2, my_v2, 0, 64);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq.");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq.");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_value(v1, my_v1, 0, 64);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq..");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq..");

            add_value(v2, my_v2, 0, 65);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq...");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq...");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1024, 63);
            add_values(v2, my_v2, 1024, 64);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq....");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq....");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1024, 64);
            add_values(v2, my_v2, 1024, 63);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq.....");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq.....");

        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1, 64);
            add_values(v2, my_v2, 1, 64);

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq......");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq......");

            v1.top() = 1;
            my_v1.top() = 1;

            if (v1 <= v2) PRINT_MSG(STDFILE, "Greater Eq.......");
            if (my_v1 <= my_v2) PRINT_MSG(FTFILE, "Greater Eq.......");
        }
    }
    //-b ------------------------------------operator<--------------------------------
    STDFILE << "-------------------- [" << " operator< " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " operator< " << "] --------------------\n" << std::endl;
    {
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then");

            add_value(v2, my_v2, 0, 64);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then.");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then.");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_value(v1, my_v1, 0, 64);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then..");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then..");

            add_value(v2, my_v2, 0, 65);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then...");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then...");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1024, 63);
            add_values(v2, my_v2, 1024, 64);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then....");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then....");
        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1024, 64);
            add_values(v2, my_v2, 1024, 63);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then.....");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then.....");

        }
        {
            std::stack<int> v1;
            std::stack<int> v2;
            ft::stack<int> my_v1;
            ft::stack<int> my_v2;

            add_values(v1, my_v1, 1, 64);
            add_values(v2, my_v2, 1, 64);

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then......");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then......");

            v1.top() = 1;
            my_v1.top() = 1;

            if (v1 < v2) PRINT_MSG(STDFILE, "Greater then.......");
            if (my_v1 < my_v2) PRINT_MSG(FTFILE, "Greater then.......");
        }
    }
    //-b ------------------------------------empty method--------------------------------
    STDFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " empty method " << "] --------------------\n" << std::endl;
	{
		std::stack<int> v;
		ft::stack<int> my_v;
		int my_sum = 0;
		int sum = 0;

		add_values(v, my_v, 0, 10);

		while (!v.empty()) {
			sum += v.top();
			v.pop();
		}
		while (!my_v.empty()) {
			my_sum += my_v.top();
			my_v.pop();
		}
		PRINT_LINE(STDFILE, "Sum: ", sum);
		PRINT_LINE(FTFILE, "Sum: ", my_sum);
	}
    //-b ------------------------------------size method--------------------------------
    STDFILE << "-------------------- [" << " size method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " size method " << "] --------------------\n" << std::endl;
    {
		std::stack<int> v;
		ft::stack<int> my_v;
		PRINT_LINE(STDFILE, "Size: ", v.size());
		PRINT_LINE(FTFILE, "Size: ", my_v.size());

		add_values(v, my_v, 1, 5);
		PRINT_LINE(STDFILE, "Size: ", v.size());
		PRINT_LINE(FTFILE, "Size: ", my_v.size());

		v.pop();
		my_v.pop();
		PRINT_LINE(STDFILE, "Size: ", v.size());
		PRINT_LINE(FTFILE, "Size: ", my_v.size());
	}
    //-b ------------------------------------top method--------------------------------
    STDFILE << "-------------------- [" << " top method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " top method " << "] --------------------\n" << std::endl;
    {
		std::stack<int> v;
		ft::stack<int> my_v;

		add_values(v, my_v, 10, 2);

		v.top() -= 6;
		my_v.top() -= 6;

		PRINT_LINE(STDFILE, "top: ", v.top());
		PRINT_LINE(FTFILE, "top: ", my_v.top());

		std::vector<int> vec(10, 50);
		vec.push_back(300);
		std::stack<int, std::vector<int> > const c_v(vec);
		ft::stack<int, std::vector<int> > const c_myv(vec);

		PRINT_LINE(STDFILE, "top: ", c_v.top());
		PRINT_LINE(FTFILE, "top: ", c_myv.top());
	}
    //-b ------------------------------------push & pop method--------------------------------
    STDFILE << "-------------------- [" << " push & pop method " << "] --------------------\n" << std::endl;
    FTFILE << "-------------------- [" << " push & pop method " << "] --------------------\n" << std::endl;
	{
		int sum = 0;
		int my_sum = 0;
		std::stack<int> v;
		ft::stack<int> my_v;

		add_values(v, my_v, 1, 5);

		while (!v.empty()) {
			sum += v.top();
			v.pop();
		}
		while (!my_v.empty()) {
			my_sum += my_v.top();
			my_v.pop();
		}
		PRINT_LINE(STDFILE, "Sum: ", sum);
		PRINT_LINE(FTFILE, "Sum: ", my_sum);
	}
    STDFILE.close();
    FTFILE.close();
    if (system("diff ft::stack std::stack") == 0) std::cout << "\033[1;32mOK" << std::endl;
    else std::cout << "\033[1;31mKO" << std::endl;
}