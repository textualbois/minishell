/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:18:55 by isemin            #+#    #+#             */
/*   Updated: 2024/08/05 13:17:27 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	print_ast_recursive1(current, 0);
	// print_ast_recursive2(current);
	return (0);
}

void	print_ast_recursive1(t_tree *node, int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
	// if (node->token)
	// 	printf("Token: %s, type: %d\n", node->token->value, node->token->type);
	// else
	// 	printf("node has no token\n");
	if (node->left != NULL)
	{
		i = 0;
		while (i < depth)
		{
			//printf("l%dl%d", depth, depth);
			printf("    ");
			i++;
		}
		printf("%d Left:\n", depth);
		//printf(": \n");
		print_ast_recursive1(node->left, depth + 1);
	}
	if (node->right != NULL)
	{
		i = 0;
		while (i < depth)
		{

		//	printf("r%dr%d", depth, depth);
			printf("    ");
			i++;
		}
	//	printf(": \n");
		printf("%d Right:\n", depth);
		print_ast_recursive1(node->right, depth + 1);
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


int print_ast_recursive2main(t_tree *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%s)", tree->token->value);

    int left  = print_ast_recursive2main(tree->left,  1, offset,                depth + 1, s);
    int right = print_ast_recursive2main(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_ast_recursive2(t_tree *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    print_ast_recursive2main(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
