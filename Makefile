# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:20:11 by mrusu             #+#    #+#              #
#    Updated: 2024/07/11 15:24:34 by mrusu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# vars
USER = $(shell whoami)

# requisites helpers

INC_RDL_HEADER = -I /Users/$(USER)/.brew/opt/readline/include
INC_RDL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

#-L/usr/local/opt/readline/lib -lreadline

BREW_DIR = /Users/$(USER)/.brew/bin
READLINE_DIR = /Users/$(USER)/.brew/opt/readline/include/readline

READLINE_FLAG = -lreadline

brew_check:
	@if [ -d $(BREW_DIR) ]; then \
		echo "BREW is already installed in $(BERW_DIR)"; \
	else \
		\
			echo "Installing Homebrew..."; \
			curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
	fi
	@$(MAKE) readline_check

readline_check:
	@if [ -d $(READLINE_DIR) ]; then \
		echo "READLINE is already installed in $(READLINE_DIR)"; \
	else \
			echo "Installing Readline..."; \
			brew install readline; \
	fi
	@$(MAKE) all

# COMPILER
CC = cc

# FLAGS FOR COMPILATION
FLAGS = -Wall -Wextra -Werror -g #-Ofast -Wunreachable-code -fsanitize=address
LFLAGS = READLINE_FLAG

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
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/loop/loop.c \
	$(SRC_DIR)/exec/exec0.c \
	$(SRC_DIR)/parse/parse.c $(SRC_DIR)/parse/lexer.c \
	$(SRC_DIR)/prompts/terminal_prompt.c \
	$(SRC_DIR)/setup/env.c $(SRC_DIR)/setup/init_shell.c \
	$(SRC_DIR)/utils/utils0.c \
	$(SRC_DIR)/error/error.c

# OBJ FILES
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
	@mkdir -p obj/general_utils
	@$(CC) $(FLAGS) -I$(INC_DIR) $(OBJS) $(LIBFT_DIR)/libft.a $(PIPEX_DIR)/pipex.a -o $(NAME) $(INC_RDL_LIB)
	@touch obj/general_utils/user.txt && echo $$USER > obj/general_utils/user.txt

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