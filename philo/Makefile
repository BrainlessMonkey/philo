NAME = philo
CC = gcc
HEADER = ./includes/
CFLAGS = -g -pthread -Wall -Werror -Wextra -I $(HEADER)
RM = rm -rf
SRC = ./srcs/alive.c ./srcs/main.c ./srcs/philosophers.c ./srcs/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o ${NAME}
%o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	${RM} ${OBJ}
fclean : clean
	${RM} ${NAME}
re : fclean all

.PHONY: all clean fclean re
