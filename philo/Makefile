CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
SRCS = src/main.c \
		src/philo_actions.c \
		src/cleanup.c \
		src/utils/init.c \
		src/utils/utils.c \
		src/utils/check_args.c 
OBJS_DIR = obj
INCLUDE = -I./include
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 