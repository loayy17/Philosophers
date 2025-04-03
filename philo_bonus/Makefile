CC = cc
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
NAME = philo_bonus
SRC = 	src/main.c \
		src/utils/check_args.c \
		src/utils/utils.c \
		src/utils/init_data.c \
		src/utils/time_utils.c \
		src/utils/monitor.c \
		src/utils/philo_actions.c \
		src/utils/print_utils.c 

INCLUDE = -I./include
OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lpthread

all: ${NAME}

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re