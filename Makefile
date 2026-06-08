CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC = src/main.c src/parse.c src/utils.c src/server.c \
      src/env.c src/client.c src/loop.c src/wisp.c src/base10_to_char.c

TEST = test/base10_to_char.c \
	test/wisp.c \
	test/client.c \
	test/parse.c\
	test/utils.c\
	test/server.c\
	test/env.c

OBJS_TEST = $(TEST:.c=.o)
OBJ = $(SRC:.c=.o)

NAME = chat_server
NAME_TEST = ut.out

all: $(NAME) $(NAME_TEST)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(NAME_TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) $(OBJS_TEST) -o $(NAME_TEST) -lcriterion

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
