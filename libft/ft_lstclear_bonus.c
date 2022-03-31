/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:51:09 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 20:51:17 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
