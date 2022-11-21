NAME1    =	vector.out
NAME2    =	Map.out
NAME3    =	Stack.out

SC_VEC    =	test_vector.cpp
SC_MAP    =	test_map.cpp
SC_STACK  =	test_stack.cpp

GCC		=	c++ -Wall -Wextra -Werror -std=c++98

RM		=	rm -f

RF		=	rm -rf std::* ft::*

vector: $(NAME1)
$(NAME1):   $(SC_VEC)
	@$(GCC) $(SC_VEC) -o $(NAME1)
	@echo "\033[1;35m▐▌ DONE ▐▌"

map: $(NAME2)
$(NAME2):   $(SC_MAP)
	@$(GCC) $(SC_MAP) -o $(NAME2)
	@echo "\033[1;35m▐▌ DONE ▐▌"

stack: $(NAME3)
$(NAME3):   $(SC_STACK)
	@$(GCC) $(SC_STACK) -o $(NAME3)
	@echo "\033[1;35m▐▌ DONE ▐▌"

clean:
	@$(RM)

fclean: clean
	@$(RM) $(NAME1) $(NAME2) $(NAME3)

re:    fclean vector map stack

rm:
	@$(RF)

.PHONY: fclean clean re rm