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
		if (current->type == T_SPECIAL && current->value == '(')
			depth++;
		else if (current->type == T_SPECIAL && current->value == ')')
			depth--;
		else if (current->type == T_OR || current->type == T_AND)
		{
			if (depth < head_node_depth || head_token == NULL)
			{
				head_node_depth = depth;
				head_token = current;
			}
		}
		current = current->next;
	}

	if (head_token != NULL) // if we found && or ||
	{
		t_tree *res = init_tree_node(head_token, parent);
		res->left = get_nodes_and_or(start, head_token, res);
		res->right = get_nodes_and_or(head_token->next, stop, res);
		return (res);
	}
	else if (start != stop)
		return (get_nodes_pipes(start, stop, parent));
	else
	return (NULL);
}

t_token	*get_nodes_pipes(t_token *start, t_token *stop, t_tree *parent)
{
	t_token	*current;
	t_token	*pipe_token;
	t_tree	*res;

	current = start;
	pipe_token = NULL;

	while (current != stop)
	{
		if (current->type == T_PIPE)
		{
			pipe_token = current;
			break;
		}
		current = current->next;
	}

	if (pipe_token != NULL)
	{
		res = init_tree_node(parent, pipe_token);
		res->left = init_cmd_node(start, pipe_token, res);  // Assuming init_cmd can take a list up to a point
		res->right = get_nodes_pipes(pipe_token->next, stop, res);
		return res;
	}
	else
		return (init_cmd_node(start, stop, parent));
}

t_tree	*init_cmd_node(t_token *start, t_token *stop, t_token *parent)
{
	t_tree	*res;
	t_token	*current;
	t_command *cmd;

	//if res not null
	cmd = ft_calloc(sizeof(t_command), 1);
	// if cmd not null
	start = get_input_file(cmd, start, stop);
	stop = get_heredoc(cmd, start, stop); 
	stop = get_output_file(cmd, start, stop);
	current = start;
	res = init_tree_node(current, parent);
	res->cmd = cmd;
	cmd->name = current->value;
	cmd->args = list_to_arr(current, stop);
	return (res);
}

t_tree	*init_tree_node(t_token *token, t_tree *parent)
{
	t_tree	*new_node;
	
	new_node = malloc(sizeof(t_tree));
	if (new_node == NULL)
		return NULL;
	new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;
	new_node->token = token;
	return (new_node);
}

