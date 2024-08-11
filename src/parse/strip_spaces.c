#include "../../inc/minishell.h"

void strip_spaces(t_shell *shell)
{
	t_token *current;
	t_token *temp;
	
	
	// int type;
	// current = shell->head;
	// while (current != NULL)
	// {
	// 	type = current->type;
	// 		printf("before strip: Type = ");
	// 		if (type == T_WORD)
	// 			printf("WORD");
	// 		else if (type == T_PIPE)
	// 			printf("PIPE");
	// 		else if (type == T_OR)
	// 			printf("OR");
	// 		else if (type == T_AND)
	// 			printf("AND");
	// 		else if (type == T_SPECIAL)
	// 			printf("SPECIAL");
	// 		else if (type == T_DOLLAR)
	// 			printf("DOLLAR");
	// 		else if (type == T_EXCODE)
	// 			printf("$?");
	// 		else if (type == T_WILDCARD)
	// 			printf("WILDCARD");
	// 		else if (type == T_WORD_EXPAND)
	// 			printf("T_WORD_EXPAND");
	// 		else if (type == T_SQUOTE)
	// 			printf("T_SQUOTE");
	// 		else if (type == T_DQUOTE)
	// 			printf("T_DQUOTE");
	// 		else if (type == T_SPACE)
	// 			printf("T_SPACE");
	// 		else
	// 			printf("UNKNOWN");
	// 		printf(", Value = '%s'\n", current->value);
	// 		current=current->next;
	// }
		
	current = shell->head;
	while (current)
	{
		if (current->type == T_SPACE)
		{
			if (current->value[0] == '\0')
			{
				temp = current;
				if (current->next != NULL && current->prev != NULL)
				{
					current->prev->next = current->next;
					current->next->prev = current->prev;
				}
				if (temp->prev == NULL && temp->next != NULL)
				{
					shell->head = temp->next;
					current->next->prev = NULL;
				}
				if (temp->prev != NULL && temp->next == NULL)
				{
					shell->tail = current->prev;
					current->prev->next = NULL;
				}
				// else
				// {
				// 	shell->head = NULL;
				// 	shell->tail = NULL;
				// }
				current = current->next;
				free(temp->value);
				free(temp);
				
			}
			else
				current->type = T_WORD;
		}
		else
			current = current->next;
	}

	// current = shell->head;
	// while (current != NULL)
	// {
	// 	type = current->type;
	// 		printf("after strip: Type = ");
	// 		if (type == T_WORD)
	// 			printf("WORD");
	// 		else if (type == T_PIPE)
	// 			printf("PIPE");
	// 		else if (type == T_OR)
	// 			printf("OR");
	// 		else if (type == T_AND)
	// 			printf("AND");
	// 		else if (type == T_SPECIAL)
	// 			printf("SPECIAL");
	// 		else if (type == T_DOLLAR)
	// 			printf("DOLLAR");
	// 		else if (type == T_EXCODE)
	// 			printf("$?");
	// 		else if (type == T_WILDCARD)
	// 			printf("WILDCARD");
	// 		else if (type == T_WORD_EXPAND)
	// 			printf("T_WORD_EXPAND");
	// 		else if (type == T_SQUOTE)
	// 			printf("T_SQUOTE");
	// 		else if (type == T_DQUOTE)
	// 			printf("T_DQUOTE");
	// 		else if (type == T_SPACE)
	// 			printf("T_SPACE");
	// 		else
	// 			printf("UNKNOWN");
	// 		printf(", Value = '%s'\n", current->value);
	// 		current=current->next;
	// }
}
