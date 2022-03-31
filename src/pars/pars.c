/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:19:16 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:21 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_sh	*init_sh(char *line, t_list_2val *l_env)
{	
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	if (!sh)
		ft_error_malloc("Error malloc: pars.c - sh");
	sh->line = line;
	sh->l_cmd = ((void *)0);
	sh->error_syntax = ((void *)0);
	sh->l_env = l_env;
	sh->num_cmd = 0;
	sh->flag_error_syntax = 0;
	return (sh);
}

t_sh	*pars(char *line, t_list_2val	*l_env)
{
	t_sh	*sh;
	t_cmd	*tmp;

	sh = init_sh(line, l_env);
	sh->flag_error_syntax = pars_check_line(sh->line, &sh->error_syntax);
	if (sh->flag_error_syntax)
	{
		printf("%s\n", sh->error_syntax);
		update_errno(258, sh->l_env);
	}
	else
	{
		sh->l_cmd = pars_list_cmd(sh->line, sh->l_env);
		tmp = sh->l_cmd;
		while (tmp)
		{
			sh->num_cmd += 1;
			tmp = tmp->next;
		}
	}
	return (sh);
}
