/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:07:40 by hzona             #+#    #+#             */
/*   Updated: 2021/11/13 17:29:28 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

t_history	*ft_lstnew_2(char *str)
{
	t_history	*new;

	new = malloc(sizeof(t_line));
	if (new == (void *)0)
		return ((void *)0);
	new->prev = (void *)0;
	new->next = (void *)0;
	new->cmd = str;
	return (new);
}

int	ft_lstsize_2(t_history *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_front_2(t_history **lst, t_history *new)
{
	t_history		*tmp;

	tmp = *lst;
	new->next = tmp;
	if (tmp != 0)
		tmp->prev = new;
	*lst = new;
}
