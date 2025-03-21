CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
SRCS = src/main.c \
		src/utils/check_args.c \
		src/utils/cleanup.c \
		src/utils/init.c \
		src/utils/monitor.c \
		src/utils/philo_actions.c \
		src/utils/philo_utils.c \
		src/utils/print_utils.c \
		src/utils/time_utils.c \
		src/utils/utils.c

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