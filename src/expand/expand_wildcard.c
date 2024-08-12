/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:03 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/12 10:48:37 by isemin           ###   ########.fr       */
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
	DIR				*dir;

	current = shell->head;
	while (current) // loops through all tokens
	{
		if (current->type == T_WILDCARD)
		{
			current = wildcard_join(current);
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
		current = current->next;
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
	while (entry != NULL) // loops through all files in the directory
	{
		if (entry->d_name[0] != '.')
		{
			if (match(token->value, entry->d_name))
			{
				// should be insert token instead of add token
				insert_token(shell, token , T_WORD, entry->d_name);
				// add_token(shell, T_WORD, ft_strdup(entry->d_name));
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
	if (*pattern == '\0') // if pattern is empty
		return (*string == '\0'); // if string is also empty return true
	else if (*pattern == '*') // if we have a wildcard *
	{

		while (*string != '\0') // while string not over
		{
			if (match(pattern + 1, string)) // assume * matches none. i.e. see if it pattern matches the rest of the string
				return (true);
			string++; // assume * matches one more char.
		} //
		return (match(pattern + 1, string));
	}
	else if (*pattern == *string) // if literal matches
		return (match(pattern + 1, string + 1)); // check next character
	return (false);
}
