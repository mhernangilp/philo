NAME = philo

SRCS = src/main.c src/parse.c src/utils.c src/start.c src/initialize.c src/activities.c

INCLUDE = ./philo.h

CC = gcc -pthread
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

%.o: %.c
	${CC} ${CFLAGS} -pthread -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:
	${RM} ${OBJS}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
