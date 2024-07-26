/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/07/26 17:32:16 by mrusu            ###   ########.fr       */
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

	printf("Entering get_nodes_and_or\n"); //debug
	while (current != stop)
	{
		printf("Current token: %s, type: %d\n", current->value, current->type); //debug
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

	if (head_token != NULL) // if we found && or ||
	{
		t_tree *res = init_tree_node(head_token, parent);
		res->left = get_nodes_and_or(start, head_token, res);
		res->right = get_nodes_and_or(head_token->next, stop, res);
		return (res);
	}
	else if (start != stop)
	{
		printf("No operator found, calling get_nodes_pipes\n"); //debug
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

	printf("Entering get_nodes_pipes\n"); //debug
	while (current != stop)
	{
		if (current->type == T_PIPE)
		{
			printf("Found pipe token\n"); //debug
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
		return (res);
	}
	else
	{
		printf("No pipe found, creating command node\n");
		return (init_cmd_node(start, stop, parent));
	}
}

t_tree	*init_cmd_node(t_token *start, t_token *stop, t_tree *parent)
{
	t_tree	*res;
	t_token	*current;
	t_command *cmd;

	//if res not null

	printf("Entering init_cmd_node\n"); //debug
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

	printf("Command node created successfully\n");
	printf("Command: %s\n", cmd->name);
	printf("Arguments: ");
	for (int j = 0; cmd->args[j]; j++)
	{
		printf("%s ", cmd->args[j]);
	}
	printf("\n");
	return (res);
}

t_tree	*init_tree_node(t_token *token, t_tree *parent)
{
	t_tree	*new_node;

	printf("Entering init_tree_node\n");
	new_node = ft_calloc(1, sizeof(t_tree));
	if (!new_node)
	{
		printf("Error: Failed to allocate memory for tree node\n");
		return NULL;
	}
	new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;
	new_node->token = token;
	printf("Tree node created successfully\n");
	return (new_node);
}

