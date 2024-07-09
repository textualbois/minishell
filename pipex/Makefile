NAME = pipex.a

SRCS = executioner.c utils.c utils2.c pipex.c\
		get_path.c manage_fd.c manage_fd_helpers.c \
		here_doc.c gnl.c error.c command_parser.c

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@echo "\033[0;32mpipex compiled successful\033[0m"

$(NAME): ${OBJ_DIR} $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)%.o: %.c | obj
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

