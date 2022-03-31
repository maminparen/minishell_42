/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_all_split_norma.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:21:23 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:54:29 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	norminett_flag_2(int flag, int	*skobka, char *str, char *str2)
{
	if (flag == 2)
	{
		*skobka = 1;
		*str = ' ';
		*str2 = ' ';
	}
	else
		*skobka = 0;
}

void	norminette_j(char **str, int i, int *j)
{
	*j = 0;
	while (str[i][*j] && (str[i][*j] == ' ' || str[i][*j] == '\t'))
		(*j)++;
}
