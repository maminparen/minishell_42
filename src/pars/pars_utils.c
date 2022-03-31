/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:15:11 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:19 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pass_quotes(char *str, int *i, char qqq)
{
	int	j;

	j = *i;
	(*i)++;
	while (*(str + *i) != qqq && *(str + *i) != '\0')
		(*i)++;
	if (*i == (int)ft_strlen(str))
		*i = j + 1;
	else
		(*i)++;
}
