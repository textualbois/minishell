/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/07/18 12:20:49 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token *get_input_file(t_command *cmd, t_token *start, t_token *stop)
{
	t_token	*current;
	char	*error_str;

	current = start;
	while (current != stop) // if the lexer handles input checking then this should nopt be a while loop, just an if
	{
		if (current->type == T_SPECIAL && current->value[0] == '<')
		{
			if (current->next->type == T_WORD)
			{
				cmd->input_file = current->next->value;
				return (current->next);
			}
			else // is the error handled here or later or in lexing!!!! need to check against bash. If bash "lets this pass" i.e. still executes later commands, then we should act accordingly
			{
				error_str = ft_strjoin("Error near ", current->next->value);
				perror(error_str);
				free(error_str);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (start);
}

t_token *get_heredoc(t_command *cmd, t_token *start, t_token *stop)
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
				return (stop);
		}
		current = current->next;
	}
	return (stop);
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
				cmd->append_output = (ft_strcmp(current->value, ">>"));
				return (current);
			}
			else
				return (stop);
		}
		current = current->next;
	}
	return (stop);
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
		if (current->type == T_WORD) //handle this or nah?
		{
			res[i] = current->value;
			i++;
		}
		current = current->next;
	}
	return (res);
}

void	print_ast(t_tree *node, int depth) //debug
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	if (node->cmd)
		printf("Command: %s\n", node->cmd->name);
	else if (node->token)
		printf("Operator: %s\n", node->token->value);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
