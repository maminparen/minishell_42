/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_sh_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:16:38 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 17:43:56 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

static t_sh_all	*init_sh_all(char *line, t_list_2val *l_env)
{	
	t_sh_all	*sh_all;

	sh_all = malloc(sizeof(t_sh_all));
	if (!sh_all)
		ft_error_malloc("Error malloc: pars.c - sh");
	sh_all->l_env = l_env;
	sh_all->line = line;
	sh_all->num_sh = 0;
	sh_all->sh_array = ((void *)0);
	sh_all->connect = ((void *)0);
	sh_all->skobka = ((void *)0);
	return (sh_all);
}

t_sh_all	*pars_sh_all(char *line, t_list_2val *l_env)
{
	t_sh_all	*sh_all;

	sh_all = init_sh_all(line, l_env);
	sh_all->sh_array = sh_all_split(line, sh_all, -1, 0);
	while (sh_all->sh_array[sh_all->num_sh])
		sh_all->num_sh += 1;
	return (sh_all);
}
