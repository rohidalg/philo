
NAME = philo

MKD = mkdir -p
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRCs = philosophers.c

DIR_OBJs = OBJECTS

OBJs = $(addprefix $(DIR_OBJs)/,$(SRCs:%.c=%.o))

INCLUDES = -I.

all: dir_objs $(NAME)

$(NAME): $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(NAME)

$(DIR_OBJs)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

dir_objs:
	$(MKD) $(DIR_OBJs)

clean:
	$(RM) $(DIR_OBJs)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re dir_objs
