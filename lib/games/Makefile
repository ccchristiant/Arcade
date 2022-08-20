##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME	=	games

CC        =    g++

CPPFLAGS        =    -std=c++20 -Wall -Wextra -fPIC -I../../include

LDFLAGS	=	-shared

RM        =    rm -f

##NIBBLER##

LIBNIBBLER	=	arcade_nibbler.so

NIBBLER_SRC_DIR	=	nibbler/

NIBBLER_SRC        =    $(NIBBLER_SRC_DIR)Nibbler.cpp		\

NIBBLER_OBJ		=	$(NIBBLER_SRC:.cpp=.o)

##PACMAN##

LIBPACMAN	=	arcade_pacman.so

PACMAN_SRC_DIR	=	pacman/

PACMAN_SRC        =    $(PACMAN_SRC_DIR)pacman.cpp		\

PACMAN_OBJ		=	$(PACMAN_SRC:.cpp=.o)

all:    $(NAME)

$(NAME): $(NIBBLER_OBJ) $(PACMAN_OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(LIBNIBBLER) $(NIBBLER_OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(LIBPACMAN) $(PACMAN_OBJ)

clean:
	$(RM) $(NIBBLER_OBJ) $(PACMAN_OBJ)

fclean:        clean
	$(RM) $(LIBNIBBLER) $(LIBPACMAN)

re:    fclean all

.PHONY:        all clean fclean re