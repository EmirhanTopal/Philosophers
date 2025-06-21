NAME = philosophers

CC = clang
CFLAGS = -fsanitize=thread -g -Wall -Wextra -Werror -pthread

SRCS = main.c \
	   utilize.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
