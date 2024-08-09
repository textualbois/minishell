/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:03 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 15:15:14 by mrusu            ###   ########.fr       */
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
	t_token			*prev;
	DIR				*dir;

	current = shell->head;
	prev = NULL;
	while (current)
	{
		if (current->type == T_WILDCARD)
		{
			dir = opendir(".");
			if (dir)
			{
				expand_wildcard_token(shell, current, &prev, dir);
			}
			else
			{
				printf("Error: opendir failed\n");
				return ;
			}
		}
		prev = current;
		current = current->next;
	}
}

/*
* @ brief: @ brief: expand a token by matching it with files in the current
*	current directory if a match is found it adds the matched
*	files to the token list.
*/
void	expand_wildcard_token(t_shell *shell, t_token *token,
			t_token **prev, DIR *dir)
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
				add_token(shell, T_WORD, ft_strdup(entry->d_name));
				found_match = true;
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	handle_wildcard_match(shell, token, prev, found_match);
}

/*
* @ brief: if a match is found it removes the wildcard token from the
*	list otherwise it treats the wildcard token as a normal word
*/
void	handle_wildcard_match(t_shell *shell, t_token *token,
	t_token **prev, bool found_match)
{
	if (found_match)
	{
		if (*prev)
			(*prev)->next = token->next;
		else
			shell->head = token->next;
		free(token->value);
		free(token);
	}
	else
	{
		token->type = T_WORD;
	}
}

/*
* @ brief: Matches the given pattern with the string,
*	returning true if they match, false otherwise.
*/
bool	match(const char *pattern, const char *string)
{
	bool		result;
	const char	*laststar_pat;
	const char	*laststar_str;

	laststar_pat = NULL;
	laststar_str = string;
	result = match_re(pattern, string, &laststar_pat, &laststar_str);
	return (result);
}

/*
* @ brief: Matches the given pattern with the string,
*	returning true if they match, false otherwise.
*/
bool	match_re(const char *pattern, const char *string,
			const char **laststar_pat, const char **laststar_str)
{
	while (*string)
	{
		if (*pattern == '?' || *pattern == *string)
		{
			string++;
			pattern++;
		}
		else if (*pattern == '*')
		{
			*laststar_pat = pattern++;
			*laststar_str = string;
		}
		else if (*laststar_pat)
		{
			pattern = *laststar_pat + 1;
			string = ++(*laststar_str);
		}
		else
			return (false);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}
