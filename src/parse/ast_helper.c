/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 20:05:09 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_words(t_token *start)
{
	t_token	*current;
	int		count;

	current = start;
	count = 0;
	while (current != NULL && \
			(current->type == T_WORD || current->type == T_SPECIAL))
	{
		if (current->type == T_WORD)
			count++;
		else if (current->value[0] == '>' || current->value[0] == '<')
			current = current->next;
		current = current->next;
	}
	return (count);
}

t_token	*get_input_file(t_command *cmd, t_token *start, t_token *stop)
{
	t_token	*current;
	char	*error_str;

	current = start;
	while (current != stop)
	{
		if (current->type == T_SPECIAL && current->value[0] == '<')
		{
			if (current->next->type == T_WORD)
			{
				cmd->input_file = current->next->value;
				return (current->next);
			}
			else
			{
				error_str = ft_strjoin("Error near ", current->next->value);
				perror(error_str);
				free(error_str);
				return (current);
			}
		}
		current = current->next;
	}
	return (current->next);
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
				return (current->next);
			}
			else
				return (current->next);
		}
		current = current->next;
	}
	return (current->next);
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
				return (current->next);
			}
			else
				return (current->next);
		}
		current = current->next;
	}
	return (current->next);
}

char	**list_to_arr_no_limit(t_token *start)
{
	t_token	*current;
	char	**res;
	int		count;

	count = count_words(start);
	res = ft_calloc(sizeof(char *), count + 1);
	count = 0;
	current = start;
	while (current != NULL && \
			(current->type == T_WORD || current->type == T_SPECIAL))
	{
		if (current->type == T_WORD)
		{
			res[count] = ft_strdup(current->value);
			count++;
		}
		else if (current->value[0] == '>' || current->value[0] == '<')
			current = current->next;
		current = current->next;
	}
	return (res);
}
