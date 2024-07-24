/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:18:55 by isemin            #+#    #+#             */
/*   Updated: 2024/07/24 15:11:21 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_ast(t_shell *shell)
{
	t_tree	*current;

	current = shell->ast;
	if (current == NULL)
	{
		printf("No AST to print\n");
		return (1);
	}
	printf("\
|--------------|\n\
|              |\n\
| Printing AST |\n\
|              |\n\
| WORD       0 |\n\
| SPECIAL    1 |\n\
| PIPE       2 |\n\
| OR         3 |\n\
| AND        4 |\n\
| QUOTE      5 |\n\
| DOLLAR     6 |\n\
|______________|\n");
	print_ast_recursive(current, 0);
	return (0);
}

void	print_ast_recursive(t_tree *node, int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
	printf("Token: %s, type: %d\n", node->token->value, node->token->type);
	if (node->left != NULL)
	{
		i = 0;
		while (i < depth)
		{
			printf("l%dl%d", depth, depth);
		//	printf("llll");
			i++;
		}
		//printf("Left:\n");
		printf(": \n");
		print_ast_recursive(node->left, depth + 1);
	}
	if (node->right != NULL)
	{
		i = 0;
		while (i < depth)
		{

			printf("r%dr%d", depth, depth);
		//	printf("rrrr");
			i++;
		}
		printf(": \n");
	//	printf("Right:\n");
		print_ast_recursive(node->right, depth + 1);
	}
}

int	depth_counter(int get_set, int direction, int val)
{
	static int	max_depth;
	static int	current_depth;
	static int	max_left;
	static int	max_right;
	static int	current_width;

	(void )val;
	if (get_set == SET)
	{
		if (direction == DOWN)
		{
			current_depth += 1;
			max_depth = my_max(max_depth, current_depth);
		}
		else if (direction == LEFT)
		{
			current_width -= 1;
			if (current_width < 0)
				max_left = my_max(max_left, -current_width);
		}
		else if (direction == RIGHT)
		{
			current_width += 1;
			if (current_width > 0)
				max_right = my_max(max_right, current_width);
		}
		else if (direction == UP)
		{
			current_depth -= 1;
			if (current_depth < 0)
			{
				printf("Error: depth counter went negative\n");
				return (1);
			}
		}
	}
	else
	{
		if (direction == DOWN)
			return (max_depth);
		else if (direction == CURRENT_DEPTH)
			return (current_depth);
		else if (direction == LEFT)
			return (max_left);
		else if (direction == RIGHT)
			return (max_right);
		else if (direction == CURRENT_WIDTH)
			return (current_width);
	}
	return (0);
}

