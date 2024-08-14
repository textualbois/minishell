/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:12:27 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 14:11:09 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	free_env_list(t_env *env_list)
{
	t_env	*current_env;
	t_env	*next_env;

	current_env = env_list;
	// perror("free_env_list\n");
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
	// perror("free_ast\n");
	if (root != NULL)
	{
		if (root->left != NULL) // problem with self
		{
			free_ast(root->left);
			root->left = NULL;
		}
		if (root->right != NULL) // problem with self
		{
			free_ast(root->right);
			root->right = NULL;
		}
		if (root->cmd != NULL) // problem with cmd
		{
			// perror("free_ast: root->cmd\n");
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



// void free_command(t_command *cmd)
// {
// 	if (cmd != NULL)
// 	{
// 		clear_arr(cmd->args);  // Free the argument list
// 		free(cmd->name);               // Free the command name
// 		free(cmd->input_file);         // Free the input file name, if any
// 		free(cmd->output_file);        // Free the output file name, if any
// 		free(cmd->heredoc_delimiter);  // Free the heredoc delimiter, if used
// 		free(cmd);                     // Finally free the command structure itself
// 	}
// }



// Main function to free the shell structure
void	free_shell(t_shell *shell, int input_status)
{
	// perror("free_shell\n");
	if (shell != NULL)
	{
		free(shell->terminal_prompt);
		free(shell->input);
		// free(shell->user);
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
		// free(shell);
	}
}
