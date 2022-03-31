/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:10:30 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/07 16:36:28 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*next;

	if (!lst)
		return ((void *)0);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return ((void *)0);
	next = new;
	tmp = lst->next;
	while (tmp)
	{
		next->next = ft_lstnew((*f)(tmp->content));
		if (!tmp)
		{
			ft_lstclear(&new, del);
			return ((void *)0);
		}
		next = next->next;
		tmp = tmp->next;
	}
	return (new);
}
