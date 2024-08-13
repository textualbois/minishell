/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:03 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/13 16:16:22 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ Brief: initialize the dir pointer and check if curennt token is a
*	wildcard it loops through the directory and when it finds a match it
*	it calls expand_wildcard_token to handle the match.
*/
void	expand_wildcard_tokens(t_shell *shell)
{
	t_token			*current;
	t_token			*next;
	DIR				*dir;

	current = shell->head;
	while (current)
	{
		next = current->next;
		if (current->type == T_WILDCARD)
		{
			current = wildcard_join(current);
			next = current->next;
			dir = opendir(".");
			if (dir)
			{
				expand_wildcard_token(shell, current, dir);
			}
			else
			{
				printf("Error: opendir failed\n");
				return ;
			}
		}
		current = next;
	}
}

/*
* @ brief: @ brief: expand a token by matching it with files in the current
*	current directory if a match is found it adds the matched
*	files to the token list.
*/
void	expand_wildcard_token(t_shell *shell, t_token *token,
								DIR *dir)
{
	struct dirent	*entry;
	bool			found_match;

	found_match = false;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (match(token->value, entry->d_name))
			{
				insert_token(shell, token, T_WORD, entry->d_name);
				found_match = true;
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	handle_wildcard_match(shell, token, token->prev, found_match);
}

/*
* @ brief: if a match is found it removes the wildcard token from the
*	list otherwise it treats the wildcard token as a normal word
*/
void	handle_wildcard_match(t_shell *shell, t_token *token,
								t_token *prev, bool found_match)
{
	if (found_match)
	{
		if (prev)
		{
			prev->next = token->next;
			if (token->next)
				token->next->prev = prev;
		}
		else
		{
			shell->head = token->next;
			if (token->next)
				token->next->prev = prev;
		}
		free(token->value);
		free(token);
	}
	else
	{
		token->type = T_WORD;
	}
}

bool	match(char *pattern, char *string)
{
	if (*pattern == '\0')
		return (*string == '\0');
	else if (*pattern == '*')
	{
		while (*string != '\0')
		{
			if (match(pattern + 1, string))
				return (true);
			string++;
		}
		return (match(pattern + 1, string));
	}
	else if (*pattern == *string)
		return (match(pattern + 1, string + 1));
	return (false);
}
