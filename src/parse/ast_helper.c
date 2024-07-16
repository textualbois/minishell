/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/07/16 16:52:03 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*get_nodes_and_or(t_shell *shell, char *input, t_token *parent)
{
	int	i = 0;
	int	head_node_location;
	int	head_node_depth = 1;
	int	depth = 0;
	int	we_are_inside_quotes = 0;
	t_token		*res = NULL;

	while (input[i])
	{
		if (input[i] == '(') // todo check that this is the correct way to check for brackets
			depth++;
		if (input[i] == ')')
			depth--;
		if (ft_strncmp(input + i, "||", 2) || ft_strncmp(input + i, "&&", 2)) // todo check that this is the correct way to check for or and and
		{
			if (depth < head_node_depth)
			{
				head_node_depth = depth;
				head_node_location = i;
			}
		}
		i++;
	}
	if (head_node_location != 0)
	{
		res = init_token(parent, ft_substr(input, head_node_location, 2), 2);
		res->left = get_nodes_and_or(shell, ft_substr(input, 0, head_node_location), res);
		res->right = get_nodes_and_or(shell, ft_substr(input, head_node_location + 2, ft_strlen(input) - head_node_location - 2), res);
		return (res);
	}
	else // and_or_not_found
	{
		return (get_nodes_pipes(shell, input, parent));
	}
}

t_token	*get_nodes_pipes(t_token *shell, char *input, t_token *parent)
{
	int		i = 0;
	int		pipe_node_location;
	t_token	*res;

	while (input[i])
	{
		if (input[i] == '|')
		{
			pipe_node_location = i;
			res = init_token(parent, ft_substr(input, pipe_node_location, 1), 1);
			res->left = init_cmd(ft_substr(input, 0, pipe_node_location), res);
			res->right = get_nodes_pipes(shell, ft_substr(input, pipe_node_location + 1, ft_strlen(input) - pipe_node_location - 1), res);
		}
		i++;
	}
	if (pipe_node_location != 0)
	{
		res = init_cmd(input, parent);
	}
}

init_token();