/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/08/08 09:55:53 by mrusu            ###   ########.fr       */
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
		if (current->type == T_SPECIAL && current->value[0] == '(')
			depth++;
		else if (current->type == T_SPECIAL && current->value[0] == ')')
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
	if (head_token != NULL)
	{
		t_tree *res = init_tree_node(head_token, parent);
		res->left = get_nodes_and_or(start, head_token, res);
		res->right = get_nodes_and_or(head_token->next, stop, res);
		return (res);
	}
	else if (start != stop)
	{
		return (get_nodes_pipes(start, stop, parent));
	}
	else
		return (NULL);
}

t_tree	*get_nodes_pipes(t_token *start, t_token *stop, t_tree *parent)
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
		res = init_tree_node(pipe_token, parent);
		res->left = init_cmd_node(start, pipe_token, res);  // Assuming init_cmd can take a list up to a point
		if (res->left == NULL)
		{
			perror("Error: Failed to create left node of pipe\n");
			return (NULL);
		}
		res->right = get_nodes_pipes(pipe_token->next, stop, res);
		if (res->right->token && res->right->token->type == T_PIPE)
			res->left->cmd->next = res->right->left->cmd;
		else
			res->left->cmd->next = res->right->cmd;
		return (res);
	}
	else
	{
		return (init_cmd_node(start, stop, parent));
	}
}

t_tree	*init_cmd_node(t_token *start, t_token *stop, t_tree *parent)
{
	t_tree		*res;
	t_token		*current;
	t_command	*cmd;
	int			got_cmd_name;

	got_cmd_name = 0;
	cmd = ft_calloc(sizeof(t_command), 1); //1
	current = start; //5
	while (current != stop)
	{
		if (current->type == T_SPECIAL)
		{
			if (current->value[1] == '<')
				get_heredoc(cmd, current, stop); //3
			else if (current->value[0] == '>')
				get_output_file(cmd, current, stop); //4
			else
				get_input_file(cmd, current, stop); //2
			current = current->next;
		}
		else if(got_cmd_name == 0)
		{
			cmd->name = current->value; //11
			cmd->args = list_to_arr_no_limit(current); //6
			got_cmd_name = 1;
			res = init_tree_node(current, parent);	//8
			res->cmd = cmd;	//9
		}
		current = current->next;
	}
	return (res);
}

t_tree	*init_tree_node(t_token *token, t_tree *parent)
{
	t_tree	*new_node;

	new_node = ft_calloc(1, sizeof(t_tree));
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
