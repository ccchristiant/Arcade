##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME	=	graphicals

CXX        ?=    g++

CPPFLAGS        =    -std=c++20 -Wall -Wextra -fPIC -I../../include

LDFLAGS	=	-shared

RM        =    rm -f

##FOO##

LIBFOO	=	arcade_sfml.so

FOO_SRC_DIR	=	foo/

FOO_SRC        =    $(FOO_SRC_DIR)foo.cpp		\

FOO_OBJ		=	$(FOO_SRC:.cpp=.o)

##BAR##

LIBBAR	=	arcade_ncurses.so

BAR_SRC_DIR	=	bar/

BAR_SRC        =    $(BAR_SRC_DIR)bar.cpp		\

BAR_OBJ		=	$(BAR_SRC:.cpp=.o)

##GRA##

LIBGRA	=	arcade_sdl2.so

GRA_SRC_DIR	=	gra/

GRA_SRC        =    $(GRA_SRC_DIR)gra.cpp		\

GRA_OBJ		=	$(GRA_SRC:.cpp=.o)

all:    $(NAME) $(LIBBAR)

$(NAME): $(FOO_OBJ) $(BAR_OBJ) $(GRA_OBJ)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(LIBFOO) $(FOO_OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(LIBBAR) $(BAR_OBJ) -lncurses
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(LIBGRA) $(GRA_OBJ) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

$(LIBBAR): $(BAR_OBJ)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(LIBBAR) $(BAR_OBJ) -lncurses

clean:
	$(RM) $(FOO_OBJ) $(BAR_OBJ) $(GRA_OBJ)

fclean:        clean
	$(RM) $(LIBFOO) $(LIBBAR) $(LIBGRA)

re:    fclean all

.PHONY:        all clean fclean re