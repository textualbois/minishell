#include "../../inc/minishell.h"

void	handle_exit_code(t_shell *shell, t_token *token)
{
	free(token->value);
	token->value = ft_itoa(shell->exit_code);
	token->type = T_WORD;
}

void	handle_single_quote(t_token *token)
{
	free(token->value);
	token->value = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
	token->type = T_WORD;
}

t_token	*fallback_on_prev_token(t_token *current)
{
	char	*new_value;
	t_token *prev;

	prev = current->prev;
	if (prev != NULL && (prev->type == T_SPACE || prev->type == T_WORD))
	{
		new_value = ft_strjoin(prev->value, current->value);
		free(prev->value);
		prev->value = new_value;
		prev->next = current->next;
		if (current->next != NULL)
			current->next->prev = prev;
		free(current->value);
		free(current);
		return (prev);
	}
	return (current);
}
