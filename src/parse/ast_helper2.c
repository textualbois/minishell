/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:57:50 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 14:44:57 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*add_tree_node_and_or(t_token *head_token, \
					t_token *start, t_token *stop, t_tree *parent)
{
	t_tree	*res;

	res = init_tree_node(head_token, parent);
	res->left = get_nodes_and_or(start, head_token, res);
	res->right = get_nodes_and_or(head_token->next, stop, res);
	return (res);
}

t_tree	*add_tree_node_pipe(t_token *pipe_token, \
				t_token *start, t_token *stop, t_tree *parent)
{
	t_tree	*res;

	res = init_tree_node(pipe_token, parent);
	res->left = init_cmd_node(start, pipe_token, res);
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

t_token	*get_pivot_token(t_token *current, int *depth, \
						int *head_node_depth, t_token *head_token)
{
	if (current->type == T_SPECIAL && current->value[0] == '(')
		*depth = *depth +1;
	else if (current->type == T_SPECIAL && current->value[0] == ')')
		*depth = *depth -1;
	else if (current->type == T_OR || current->type == T_AND)
	{
		if (*depth < *head_node_depth || head_token == NULL)
		{
			*head_node_depth = *depth;
			return (current);
		}
	}
	return (head_token);
}

t_token	*process_redirections(t_command *cmd, t_token *current, t_token *stop)
{
	if (current->value[1] == '<')
		current = get_heredoc(cmd, current, stop);
	else if (current->value[0] == '>')
		current = get_output_file(cmd, current, stop);
	else if (current->value[0] == '<')
		current = get_input_file(cmd, current, stop);
	return (current);
}
