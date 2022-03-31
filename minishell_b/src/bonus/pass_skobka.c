/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_skobka.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:48:35 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:54:27 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_left_skobka(char *str, int i)
{
	if (i > 0)
		(i)--;
	while (i > 0 && *(str + i) && (*(str + i) == ' ' || \
					*(str + i) == '\t' || *(str + i) == '('))
		(i)--;
	if (i == 0 || (i > 0 && ((*(str + i) == '|' && \
							*(str + i - 1) == '|' ) || \
							(*(str + i) == '&' && \
							*(str + i - 1) == '&' ))))
		return (1);
	return (0);
}

static int	check_wright_skobka(char *str, int *i)
{
	(*i)++;
	while (*(str + *i) && (*(str + *i) == ' ' || \
			*(str + *i) == '\t' || *(str + *i) == ')'))
		(*i)++;
	if (*(str + *i) == '\0' || \
		((*(str + *i) == '|' && \
		*(str + *i + 1) == '|' ) || \
		(*(str + *i) == '&' && \
		*(str + *i + 1) == '&' )))
		return (1);
	return (0);
}

int	normin(char *str, int *i, int k, int *flag)
{
	k = *i;
	if (check_wright_skobka(str, i))
	{
		*i = k + 1;
		(*flag)--;
		if (*flag == 0)
			return (1);
	}
	else
		*i = k + 1;
	return (0);
}

void	pass_skobka(char *str, int *i, int j, int flag)
{
	if (check_left_skobka(str, *i))
	{
		*i = j + 1;
		while (*(str + *i))
		{
			if (*(str + *i) == ')')
			{
				if (normin(str, i, 0, &flag))
					return ;
			}
			else if (*(str + *i) == '(')
			{
				if (check_left_skobka(str, *i - 1))
					flag++;
				(*i)++;
			}
			else
				(*i)++;
		}
		if (*(str + *i) == '\0')
			*i = j + 1;
	}
	else
		*i = j + 1;
}
