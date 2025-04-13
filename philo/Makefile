CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
SRCS = main.c \
		src/check_args.c \
		src/cleanup.c \
		src/init.c \
		src/monitor.c \
		src/philo_actions.c \
		src/utils/philo_utils.c \
		src/utils/print_utils.c \
		src/utils/time_utils.c \
		src/utils/checker_utils.c

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