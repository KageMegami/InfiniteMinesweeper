SRC	=	src/Main.cpp

OBJ =	$(SRC:.cpp=.o)

CC	=	g++

CFLAGS	=	-Wall -Wextra

NAME	=	infiniteMinesweeper

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

clean:	rm $(NAME)

fclean: clean
		rm *.o

re:	fclean
	all