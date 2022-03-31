/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:52:44 by hzona             #+#    #+#             */
/*   Updated: 2021/11/15 18:59:37 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

int	used_flag(char *flag, t_list_2val *l_env)
{
	while (l_env)
	{
		if (!strcmp(l_env->flag, flag))
			return (1);
		l_env = l_env->next;
	}
	return (0);
}
