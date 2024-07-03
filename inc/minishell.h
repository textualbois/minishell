/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/03 15:14:18 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"

// Colors
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

// Typdef

// Forward declaration of structs

// code for x
// typedef enum e_x
// {
// 	TEST
// }	t_x;

// **********************====STRUCT====*********************
// Strucutre for token
typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

typedef struct s_command
{
	char	**args;
	char	*name;
	char	*input_file;
	char	*output_file;
	char	*heredoc_delimiter;
	int		append_output;
}	t_command;

// Strucutre for data
typedef struct s_data
{
	char	**av;
	char	**env;
	char	**path;
	char	*pwd;
	int		pipes;
	int		*pid;
	int		token_count;
	t_token	*tokens;
}	t_data;

// **********************====FUNCTION DECLARATION====*********************
// main.c

// 

#endif