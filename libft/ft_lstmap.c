/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:28:34 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:46:06 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*head_new;
	t_list	*temp_new;
	void	*new_content;

	if (lst == NULL)
		return (NULL);
	new_content = f(lst->content);
	head_new = ft_lstnew(new_content);
	if (head_new == NULL)
		del(new_content);
	temp_new = head_new;
	while (head_new != NULL && lst->next != NULL)
	{
		lst = lst->next;
		new_content = f(lst->content);
		temp_new->next = ft_lstnew(new_content);
		if (temp_new->next == NULL)
		{
			del(new_content);
			ft_lstclear(&head_new, del);
		}
		else
			temp_new = temp_new->next;
	}
	return (head_new);
}
