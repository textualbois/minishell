/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:18:15 by isemin            #+#    #+#             */
/*   Updated: 2024/01/11 17:08:38 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static ssize_t	append_to_stash(char **stash, int fd)
{
	ssize_t	r_status;
	char	*buf;
	size_t	stash_len;

	stash_len = 0;
	if (stash[fd] != NULL)
		stash_len = ft_strlen(stash[fd]);
	buf = ft_calloc(stash_len + BUFFER_SIZE + 1, 1);
	if (buf == NULL)
		return (-1);
	if (stash[fd] != NULL)
		ft_strlcpy(buf, stash[fd], stash_len + 1);
	if (stash[fd] != NULL)
		free(stash[fd]);
	stash[fd] = buf;
	r_status = read(fd, (stash[fd] + stash_len), BUFFER_SIZE);
	if (r_status == -1 || (r_status == 0 && stash[fd][0] == '\0'))
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (r_status);
	}
	return (r_status);
}

static char	*pinch_line(char **stash, int fd, char *nl_pos)
{
	size_t	res_len;
	char	*buf;

	res_len = ft_strlen(stash[fd]);
	if (nl_pos != NULL)
		res_len = (nl_pos - stash[fd] + 1);
	buf = ft_calloc(res_len + 1, 1);
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, stash[fd], res_len + 1);
	if (nl_pos != NULL)
		ft_strlcpy(stash[fd], nl_pos + 1, ft_strlen(nl_pos) + 1);
	else
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (buf);
}

char	*get_next_line(int fd, int clear_stash)
{
	static char	*stash[1024];
	char		*nl_pos;
	char		*res;
	ssize_t		r_status;

	if (clear_stash)
		return (clear_arr(stash));
	if (fd < 0 || fd > 1023)
		return (NULL);
	r_status = 1;
	nl_pos = NULL;
	if (stash[fd] != NULL)
		nl_pos = ft_strchr(stash[fd], '\n');
	while (nl_pos == NULL && r_status > 0)
	{
		r_status = append_to_stash(stash, fd);
		if (stash[fd] != NULL)
			nl_pos = ft_strchr(stash[fd], '\n');
		if (r_status == -1 || (r_status == 0 && stash[fd] == NULL))
			return (NULL);
	}
	res = pinch_line(stash, fd, nl_pos);
	return (res);
}
