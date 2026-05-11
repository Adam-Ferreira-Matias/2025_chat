CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC = src/main.c src/parse.c src/utils.c src/server.c
OBJ = $(SRC:.c=.o)
NAME = chat_server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
