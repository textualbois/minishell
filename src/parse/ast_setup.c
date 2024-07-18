/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:58:09 by isemin            #+#    #+#             */
/*   Updated: 2024/07/18 17:18:40 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*get_nodes_and_or(t_token *start, t_token *stop, t_tree *parent)
{
    printf("Entering get_nodes_and_or\n");
    if (!start || !stop)
    {
        printf("Error: Invalid start or stop token\n");
        return NULL;
    }
    printf("Start token: %s, Stop token: %s\n", start->value, stop->value);

	int		depth;
	int		head_node_depth;
	t_token	*head_token;
	t_token	*current;

	depth = 0;
	head_node_depth = 0;
	head_token = NULL;
	current = start;

	if (start == stop)
    {
        printf("Single-word command detected\n");
        return init_cmd_node(start, stop, parent);
    }

	while (current && current <= stop)
	{
		if (!current->value)
		{
			printf("Error: Invalid token value\n");
			return NULL;
		}
		printf("Current token: %s, type: %d\n", current->value, current->type);
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
		printf("Creating node for operator: %s\n", head_token->value);
		t_tree *res = init_tree_node(head_token, parent);
		if (!res)
		{
			printf("Error: Failed to create tree node\n");
			return NULL;
		}
		res->left = get_nodes_and_or(start, head_token, res);
		res->right = get_nodes_and_or(head_token->next, stop, res);
		return (res);
	}
	else if (start != stop)
	{
		printf("No operator found, calling get_nodes_pipes\n");
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
	
	printf("Entering get_nodes_pipes\n");
    if (!start || !stop)
    {
        printf("Error: Invalid start or stop token\n");
        return NULL;
    }
    printf("Start token: %s, Stop token: %s\n", start->value, stop->value);

	while (current && current <= stop)
	{
		if (current->type == T_PIPE)
		{
			printf("Found pipe token\n");
			pipe_token = current;
			break;
		}
		current = current->next;
	}
	if (pipe_token != NULL)
	{
		printf("Creating node for pipe\n");
		res = init_tree_node(pipe_token, parent);
		if (!res)
		{
			printf("Error: Failed to create tree node\n");
			return NULL;
		}
		res->left = init_cmd_node(start, pipe_token, res);  // Assuming init_cmd can take a list up to a point
		res->right = get_nodes_pipes(pipe_token->next, stop, res);
		return (res);
	}
	else
	{
		printf("No pipe found, creating command node\n");
		return (init_cmd_node(start, stop, parent));
	}
}

t_tree *init_cmd_node(t_token *start, t_token *stop, t_tree *parent)
{
    printf("Entering init_cmd_node\n");
    if (!start || !stop)
    {
        printf("Error: Invalid start or stop token\n");
        return NULL;
    }
    printf("Start token: %s, Stop token: %s\n", start->value, stop->value);

    t_tree *res;
    t_command *cmd;

    cmd = ft_calloc(1, sizeof(t_command));
    if (!cmd)
    {
        printf("Error: Failed to allocate memory for command\n");
        return NULL;
    }

    // Count the number of tokens
    int token_count = 0;
    t_token *current = start;
    while (current && current <= stop)
    {
        token_count++;
        if (current == stop) break;
        current = current->next;
    }

    // Allocate memory for args
    cmd->args = ft_calloc(token_count + 1, sizeof(char *));
    if (!cmd->args)
    {
        printf("Error: Failed to allocate memory for command arguments\n");
        free(cmd);
        return NULL;
    }

    // Fill args array
    int i = 0;
    current = start;
    while (current && current <= stop)
    {
        cmd->args[i] = ft_strdup(current->value);
        if (!cmd->args[i])
        {
            printf("Error: Failed to duplicate token value\n");
            // TODO: Free previously allocated memory
            free(cmd->args);
            free(cmd);
            return NULL;
        }
        i++;
        if (current == stop) break;
        current = current->next;
    }

    cmd->name = cmd->args[0];  // The first argument is the command name

    res = init_tree_node(start, parent);
    if (!res)
    {
        printf("Error: Failed to create tree node\n");
        // TODO: Free allocated memory
        return NULL;
    }

    res->cmd = cmd;

    printf("Command node created successfully\n");
    printf("Command: %s\n", cmd->name);
    printf("Arguments: ");
    for (int j = 0; cmd->args[j]; j++)
    {
        printf("%s ", cmd->args[j]);
    }
    printf("\n");

    return res;
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

