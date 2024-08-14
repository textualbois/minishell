/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 20:09:39 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*get_nodes_and_or(t_token *start, t_token *stop, t_tree *parent)
{
	int		depth;
	int		head_node_depth;
	t_token	*head_token;
	t_token	*current;

	depth = 0;
	head_node_depth = 0;
	head_token = NULL;
	current = start;
	while (current != stop)
	{
		head_token = get_pivot_token(current, &depth, \
									&head_node_depth, head_token);
		current = current->next;
	}
	if (head_token != NULL)
		return (add_tree_node_and_or(head_token, start, stop, parent));
	else if (start != stop)
		return (get_nodes_pipes(start, stop, parent));
	else
		return (NULL);
}

t_tree	*get_nodes_pipes(t_token *start, t_token *stop, t_tree *parent)
{
	t_token	*current;
	t_token	*pipe_token;

	current = start;
	pipe_token = NULL;
	while (current != stop)
	{
		if (current->type == T_PIPE)
		{
			pipe_token = current;
			break ;
		}
		current = current->next;
	}
	if (pipe_token != NULL)
		return (add_tree_node_pipe(pipe_token, start, stop, parent));
	else
		return (init_cmd_node(start, stop, parent));
}

t_tree	*init_cmd_node(t_token *start, t_token *stop, t_tree *parent)
{
	t_tree		*res;
	t_token		*current;
	t_command	*cmd;
	int			got_cmd_name;

	got_cmd_name = 0;
	cmd = ft_calloc(sizeof(t_command), 1);
	current = start;
	while (current != stop)
	{
		if (current->type == T_SPECIAL)
			current = process_redirections(cmd, current, stop);
		else if (got_cmd_name == 0)
		{
			cmd->name = ft_strdup(current->value);
			cmd->args = list_to_arr_no_limit(current);
			got_cmd_name = 1;
			res = init_tree_node(current, parent);
			res->cmd = cmd;
			cmd->next = NULL;
		}
		current = current->next;
	}
	return (res);
}

t_tree	*init_tree_node(t_token *token, t_tree *parent)
{
	t_tree	*new_node;

	new_node = ft_calloc(sizeof(t_tree), 1);
	if (!new_node)
	{
		perror("Error: Failed to allocate memory for tree node\n");
		return (NULL);
	}
	new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;
	new_node->token = token;
	return (new_node);
}
