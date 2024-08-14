/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:12:27 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 21:32:53 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*current_env;
	t_env	*next_env;

	current_env = env_list;
	while (current_env)
	{
		next_env = current_env->next;
		free(current_env->key);
		free(current_env->value);
		free(current_env);
		current_env = next_env;
	}
}

// Helper function to free the command structures in the AST
void	free_ast(t_tree *root)
{
	if (root != NULL)
	{
		if (root->left != NULL)
		{
			free_ast(root->left);
			root->left = NULL;
		}
		if (root->right != NULL)
		{
			free_ast(root->right);
			root->right = NULL;
		}
		if (root->cmd != NULL)
		{
			clear_arr(root->cmd->args);
			root->cmd->args = NULL;
			if (root->cmd->name)
			{
				free(root->cmd->name);
				root->cmd->name = NULL;
			}
			if (root && root->cmd && root->cmd->input_file)
			{
				free(root->cmd->input_file);
				root->cmd->input_file = NULL;
			}
			if (root && root->cmd && root->cmd->output_file)
			{
				free(root->cmd->output_file);
				root->cmd->output_file = NULL;
			}
			if (root && root->cmd)
			{
				free(root->cmd);
				root->cmd = NULL;
			}
		}
		free(root);
		root = NULL;
	}
}

// Main function to free the shell structure
void	free_shell(t_shell *shell, int input_status)
{
	if (shell != NULL)
	{
		free(shell->terminal_prompt);
		free(shell->input);
		free_env_list(shell->env_list);
		if (shell->env != NULL)
			clear_arr(shell->env);
		free(shell->heredoc);
		free(shell->last_input);
		if (shell->cmd_paths != NULL)
			clear_arr(shell->cmd_paths);
		if (shell->path != NULL)
			clear_arr(shell->path);
		if (shell->pwd != NULL)
			free(shell->pwd);
		if (input_status != -2 && shell->ast != NULL)
		{
			free_ast(shell->ast);
			shell->ast = NULL;
		}
	}
}

/*
* @brief: free one node of the environment list.
*/
void	free_env_node(t_env *env_node)
{
	free(env_node->key);
	free(env_node->value);
	free(env_node);
}

/*
* @ brief: clears the shell's token list.
*/
void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	shell->head = NULL;
	shell->tail = NULL;
	shell->token_count = 0;
}
