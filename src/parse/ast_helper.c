/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 15:05:04 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*get_input_file(t_command *cmd, t_token *start, t_token *stop)
{
	t_token	*current;
	char	*error_str;

	current = start;
	while (current != stop) // if the lexer handles input checking then this should nopt be a while loop, just an if
	{
		if (current->type == T_SPECIAL && current->value[0] == '<')
		{
			// printf("found input file redirect sign\n");
			if (current->next->type == T_WORD)
			{
				cmd->input_file = current->next->value;
				return (current->next->next);
			}
			else // is the error handled here or later or in lexing!!!! need to check against bash. If bash "lets this pass" i.e. still executes later commands, then we should act accordingly
			{
				error_str = ft_strjoin("Error near ", current->next->value);
				perror(error_str);
				free(error_str);
				return (current);
			}
		}
		current = current->next;
	}
	return (start);
}

t_token	*get_heredoc(t_command *cmd, t_token *start, t_token *stop)
{
	t_token	*current;

	current = start;
	while (current != stop)
	{
		if (current->type == T_SPECIAL && ft_strcmp(current->value, "<<") == 0)
		{
			if (current->next->type == T_WORD)
			{
				cmd->heredoc_delimiter = current->next->value;
				return (current);
			}
			else // i dont think we should have a "<<" folowed by not a word
				return (current);
		}
		current = current->next;
	}
	return (current);
}

t_token	*get_output_file(t_command *cmd, t_token *start, t_token *stop)
{
	t_token	*current;

	current = start;
	while (current != stop)
	{
		if (current->type == T_SPECIAL && current->value[0] == '>')
		{
			if (current->next->type == T_WORD)
			{
				cmd->output_file = current->next->value;
				cmd->append_output = (ft_strcmp(current->value, ">>") == 0);
				return (current);
			}
			else
				return (current);
		}
		current = current->next;
	}
	return (current);
}

char	**list_to_arr_no_limit(t_token *start)
{
	t_token	*current;
	char	**res;
	int		count;

	printf("getting arg arr\n");
	current = start;
	count = 0;
	while (current != NULL && (current->type == T_WORD || current->type == T_SPECIAL)) // can we have non T_WORD types here? i.e will T_bracket pass
	{
		if (current->type == T_WORD)
			count++;
		current = current->next;
	}
	printf("no limit_arr count is %i\n", count);
	res = ft_calloc(sizeof(char *), count + 1);
	count = 0;
	current = start;
	while (current != NULL && (current->type == T_WORD || current->type == T_SPECIAL)) // can we have non T_WORD types here? i.e will T_bracket pass
	{
		if (current->type == T_WORD)
		{
			res[count] = current->value;
			count++;
		}
		current = current->next;
	}
	printf("made no_limit arr\n");
	return (res);
}

char	**list_to_arr(t_token *start, t_token *stop)
{
	t_token	*current;
	char	**res;
	int		i;

	current = start;
	i = 0;
	while (current != stop)
	{
		if (current->type == T_WORD)
			i++;
		current = current->next;
	}
	res = ft_calloc(sizeof(char *), i + 1);
	current = start;
	i = 0;
	while (current != stop)
	{
		if (current->type == T_WORD)
		{
			res[i] = current->value;
			i++;
		}
		current = current->next;
	}
	return (res);
}
