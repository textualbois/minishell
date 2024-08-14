# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:20:11 by mrusu             #+#    #+#              #
#    Updated: 2024/08/14 21:06:49 by mrusu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# vars
USER = $(shell whoami)

# requisites helpers

#INC_RDL_HEADER_DEFAULT := -I /Users/$(USER)/.brew/opt/readline/include
#INC_RDL_LIB_DEFAULT := -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
#INC_RDL_HEADER := $(INC_RDL_HEADER_DEFAULT)
#INC_RDL_LIB := $(INC_RDL_LIB_DEFAULT)

#-L/usr/local/opt/readline/lib -lreadline

#BREW_DIR := $(if $(BREW_BIN),$(shell dirname $(BREW_BIN)),)
#BREW_DIR = /Users/$(USER)/.brew/bin
#BREW_DIR_ALT = /usr/local/bin/brew
#READLINE_DIR := /Users/$(USER)/.brew/opt/readline/include/readline

BREW_EXEC := $(shell which brew)
READLINE_DIR = $(shell brew --prefix readline)
INC_RDL_HEADER = -I $(READLINE_DIR)/include
INC_RDL_LIB = -L $(READLINE_DIR)/lib -lreadline

READLINE_FLAG:= -lreadline

brew_check:
	@echo "BREW_EXEC = $(BREW_EXEC)\n";
	@if [ -f $(BREW_EXEC) ]; then \
		echo "BREW is already here $(BREW_EXEC)"; \
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
	$(SRC_DIR)/loop/loop.c $(SRC_DIR)/loop/loop_further.c\
	$(SRC_DIR)/exec/pipex_api/here_doc.c $(SRC_DIR)/exec/pipex_api/manage_fd.c $(SRC_DIR)/exec/pipex_api/manage_fd_helpers.c \
	$(SRC_DIR)/exec/exec0.c $(SRC_DIR)/exec/exec_builtin.c $(SRC_DIR)/exec/pipex_wrapper.c $(SRC_DIR)/exec/stdio_save_restore.c\
	$(SRC_DIR)/parse/ast_helper.c $(SRC_DIR)/parse/ast_setup.c $(SRC_DIR)/parse/strip_spaces.c \
	$(SRC_DIR)/parse/ast_helper2.c $(SRC_DIR)/parse/parse.c $(SRC_DIR)/parse/lexer.c $(SRC_DIR)/parse/lexer_utils.c \
	$(SRC_DIR)/parse/utils.c $(SRC_DIR)/parse/token_extras.c\
	$(SRC_DIR)/expand/expand_dollar.c $(SRC_DIR)/expand/expand_wildcard.c $(SRC_DIR)/expand/expand_utils.c $(SRC_DIR)/expand/expand_utils2.c \
	$(SRC_DIR)/prompts/terminal_prompt.c \
	$(SRC_DIR)/setup/env.c $(SRC_DIR)/setup/init_shell.c \
	$(SRC_DIR)/utils/utils0.c $(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/builtins/cmds.c $(SRC_DIR)/builtins/env.c $(SRC_DIR)/builtins/export.c $(SRC_DIR)/builtins/change_dir.c \
	$(SRC_DIR)/signal/signals.c \


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
	@$(CC) $(FLAGS) $(INC_RDL_HEADER) -I$(INC_DIR) $(OBJS) $(LIBFT_DIR)/libft.a $(PIPEX_DIR)/pipex.a -o $(NAME) $(INC_RDL_LIB)
	@touch obj/general_utils/user.txt && echo $$USER > obj/general_utils/user.txt

# RULES FOR CREATING OBJECT FILES
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INC_RDL_HEADER) -I$(INC_DIR) -c $< -o $@

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