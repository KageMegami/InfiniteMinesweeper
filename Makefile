SRC	=	src/main.cpp	\
		src/Game/Game.cpp	\
		src/Game/Map.cpp	\
		src/Game/Chunk.cpp	\

OBJ =	$(SRC:.cpp=.o)

CC	=	g++

CFLAGS	=	-Wall -Wextra

NAME	=	infiniteMinesweeper

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

clean:	
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all