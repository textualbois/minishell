# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:20:11 by mrusu             #+#    #+#              #
#    Updated: 2024/07/09 17:45:50 by mrusu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# vars
USER = $(shell whoami)

# COMPILER
CC = cc

# FLAGS FOR COMPILATION
FLAGS = -Wall -Wextra -Werror -g #-Ofast -Wunreachable-code -fsanitize=address

# COLORS
GREEN = \033[0;32m
NC = \033[0m

# Minishell DIRECTORIES
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
LIBFT_DIR = libft
PIPEX_DIR = pipex

# Minishell EXECUTABLE NAME
NAME = minishell

# HEADER FILE
HEADER = $(INC_DIR)/minishell.h

# LIST OF SOURCE FILES
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/loop/loop.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ALL RULE
all: libft pipex $(NAME)
	@echo "$(GREEN)Minishell build successful$(NC)"

# RULE FOR LIBFT
libft:
	@$(MAKE) -C $(LIBFT_DIR)

# RULE FOR PIPEX
pipex:
	@$(MAKE) -C $(PIPEX_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(PIPEX_DIR)/pipex.a
	@$(CC) $(FLAGS) -I$(INC_DIR) $(OBJS) $(LIBFT_DIR)/libft.a $(PIPEX_DIR)/pipex.a -o $(NAME)
	@rm -r obj/general_utils
	@cd obj/general_utils && touch user.txt && echo $$USER > user.txt

# RULES FOR CREATING OBJECT FILES
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

# RULES TO CLEAN EVERYTHING
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PIPEX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Minishell cleaned$(NC)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PIPEX_DIR) fclean
	@rm -f $(NAME)
	@echo "$(GREEN)Minishell fcleaned$(NC)"

# RULES FOR RECOMPILATION
re: fclean all

.PHONY: all clean fclean re libft pipex