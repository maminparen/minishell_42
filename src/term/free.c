/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:03:51 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 14:59:11 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

void	free_all(t_line **data)
{
	if ((*data)->tmp)
		free((*data)->tmp);
	(*data)->tmp = NULL;
	free_line(&(*data)->line);
	free_line(&(*data)->name);
}

void	free_line(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
}

void	free_history(t_history *history)
{
	t_history	*tmp;

	while (history)
	{
		tmp = history;
		history = history->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free_line(&tmp->cmd);
		free(tmp);
		tmp = NULL;
	}
}

char	*new_real(char *real)
{
	char	*tmp;

	tmp = real;
	if (real[1] == '/')
	{
		real = ft_strdup(real + 1);
		free(tmp);
	}
	while (real[ft_strlen(real) - 1] == '/')
		real[ft_strlen(real) - 1] = '\0';
	tmp = NULL;
	return (real);
}
