CC = cc
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
NAME = philo_bonus
SRC = 	src/main.c \
		src/utils/cleanup.c \
		src/utils/init.c \
		src/utils/philo_actions.c \
		src/utils/start_processes.c \
		src/utils/utils.c \
		src/utils/validate_args.c 

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