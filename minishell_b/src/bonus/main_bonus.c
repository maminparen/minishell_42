/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:11:27 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 17:50:18 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	make_cmd(char *line, t_list_2val *l_env)
{
	t_sh	*sh;	

	sh = pars(line, l_env);
	if (!sh->flag_error_syntax)
		make_execute(sh);
	free_sh(&sh);
}

int	find_baks(t_list_2val *l_env)
{
	while (l_env)
	{
		if (!ft_strcmp(l_env->flag, "?"))
		{
			if (ft_atoi(l_env->value))
				return (1);
			else
				return (0);
		}
		l_env = l_env->next;
	}
	return (0);
}

int	find_baks_exit(t_list_2val *l_env)
{
	while (l_env)
	{
		if (!ft_strcmp(l_env->flag, "?"))
		{
			if (ft_atoi(l_env->value))
				return (ft_atoi(l_env->value));
			else
				return (0);
		}
		l_env = l_env->next;
	}
	return (0);
}

void	make_main_skobka(t_sh_all *sh_all, \
						t_list_2val *l_env, int i, int status)
{
	int			ret;

	if (!((!find_baks(l_env) && sh_all->connect[i] == 1) || \
			(find_baks(l_env) && sh_all->connect[i] == 2)))
	{
		free(sh_all->sh_array[i]);
		return ;
	}
	ret = fork();
	if (ret < 0)
		ft_error_malloc("Error fork: main.bonus.c - ret");
	if (ret == 0)
	{
		make_main_split(sh_all->sh_array[i], sh_all->l_env);
		exit (find_baks_exit(l_env));
	}
	waitpid(ret, &status, 0);
	if (WIFEXITED(status))
		update_errno(WEXITSTATUS(status), l_env);
	else if (WIFSIGNALED(status))
		update_errno(WTERMSIG(status), l_env);
	else if (WIFSTOPPED(status))
		update_errno(WSTOPSIG(status), l_env);
	else
		update_errno(0, l_env);
}

void	make_main_split(char *line, t_list_2val *l_env)
{
	t_sh_all	*sh_all;
	int			i;	
	int			flag;

	sh_all = pars_sh_all(line, l_env);
	flag = 1;
	i = -1;
	while (sh_all->sh_array[++i])
	{	
		if (sh_all->skobka[i] == 0)
		{
			if (sh_all->num_sh == 1 || \
					((!find_baks(l_env) && sh_all->connect[i] == 1) || \
					(find_baks(l_env) && sh_all->connect[i] == 2)))
				make_cmd(sh_all->sh_array[i], sh_all->l_env);
			else
				free(sh_all->sh_array[i]);
		}
		else
			make_main_skobka (sh_all, l_env, i, 0);
	}
	free_sh_all(&sh_all);
}
