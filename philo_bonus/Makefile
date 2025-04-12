CC = cc
CFLAGS = -Wall -Wextra -Werror ${INCLUDE}
NAME = philo_bonus
SRC = 	src/main.c \
		src/cleanup.c \
		src/monitor.c \
		src/philo_routine.c \
		src/utils/init.c \
		src/utils/utils.c \
		src/utils/validate_args.c 

INCLUDE = -I./include
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lpthread

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re