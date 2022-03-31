/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_2val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:58:10 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:36 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list_2val	*ft_lstnew_2val(char *flag, char *value)
{
	t_list_2val	*tmp;

	tmp = (t_list_2val *)malloc(sizeof(t_list_2val));
	if (tmp == ((void *)0))
		return ((void *)0);
	tmp->flag = flag;
	tmp->value = value;
	tmp->next = ((void *)0);
	tmp->visible = 1;
	return (tmp);
}

void	ft_lstadd_back_2val(t_list_2val **lst, t_list_2val *new)
{
	t_list_2val	*tmp;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp ->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

void	ft_lstprint_2val(t_list_2val *lst)
{
	while (lst)
	{
		printf("%s=%s\n", lst->flag, lst->value);
		lst = lst->next;
	}
}
