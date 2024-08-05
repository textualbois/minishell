/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:25:03 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 13:17:51 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ Brief: go through the token list, if the token is a wildcard,
*	open the current directory and go through each entry, if the entry
*	matches the wildcard pattern, add a WORD token with the entry name.
*	close the directory and free the wildcard token. move to the next token.
*/
void	expand_wildcard_tokens(t_shell *shell)
{
	t_token			*current;
	DIR				*dir;
	struct dirent	*entry;

	current = shell->head;
	while (current)
	{
		if (current->type == T_WILDCARD)
		{
			dir = opendir(".");
			if (dir)
			{
				while (entry != NULL)
				{
					if (match(current->value, entry->d_name))
						add_token(shell, T_WORD, ft_strdup(entry->d_name));
					entry = readdir(dir);
				}
				closedir(dir);
			}
			free(current->value);
			current->value = NULL;
		}
		current = current->next;
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
		{			*laststar_pat = pattern++;
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
