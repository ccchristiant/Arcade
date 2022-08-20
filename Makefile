##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME        =    arcade

CXX        ?=    g++

SRC_DIR        =    src/

SRC        =    $(SRC_DIR)main.cpp		\
				$(SRC_DIR)Core.cpp		\

OBJ        =    $(SRC:.cpp=.o)

CPPFLAGS    =    -I./include

CXXFLAGS 	=	-std=c++20 -Wall -Wextra 

LDLIBS	=	-ldl

RM        =    rm -f

all:    $(NAME)

$(NAME):	games graphicals core

core:	$(OBJ)
	$(CXX) $(LDLIBS) $(CPPFLAGS) -o $(NAME) $(OBJ)

games:
	make -C lib/games

graphicals:
	make -C lib/graphicals

clean:
	make -C lib/games clean
	make -C lib/graphicals clean
	$(RM) $(OBJ) *.gc* *.so*

fclean:        clean
	make -C lib/games fclean
	make -C lib/graphicals fclean
	$(RM) $(NAME)

re:    fclean all

.PHONY:		all core games graphicals clean fclean re