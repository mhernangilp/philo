#####################
#      SETUP        #
#####################

NAME = philo
CC = gcc -pthread
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

#####################
#      COLORS       #
#####################

NOC = \033[0m
YELLOW = \033[1;33m
GREEN = \033[1;32m
RED = \033[1;31m

#####################
#      FILES        #
#####################

SRCS = src/main.c src/parse.c src/utils.c src/start.c src/initialize.c src/activities.c

#####################
#     LIBRARIES     #
#####################

INCLUDE = ./philo.h

#####################
#	RULES       #
#####################

%.o: %.c
	@${CC} ${CFLAGS} -pthread -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDE}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)Philo compiled ✓$(NOC)"

clean:
	@${RM} ${OBJS}
	@echo "$(RED)Philo objects deleted ✓$(NOC)"

fclean:
	@${RM} ${OBJS}
	@${RM} ${NAME}
	@echo "$(RED)Pipex deleted ✓$(NOC)"

re: fclean all

.PHONY: all clean fclean re
