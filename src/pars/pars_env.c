/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:54:24 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:10:56 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_flag_value(char *env, char **flag, char **value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(env + i) != '=')
		i++;
	*flag = ft_substr(env, 0, i);
	if (!*flag)
		ft_error_malloc("Error malloc: pars_env.c - flag");
	*value = ft_substr(env, i + 1, ft_strlen(env));
	if (!*value)
		ft_error_malloc("Error malloc: pars_env.c - value");
	if (!ft_strcmp(*flag, "SHLVL"))
	{
		tmp = *value;
		*value = ft_itoa(ft_atoi(*value) + 1);
		if (!*value)
			*value = tmp;
		else
			free(tmp);
	}
}

void	add_baks(t_list_2val	**env)
{
	t_list_2val	*tmp;
	int			flag;

	tmp = ft_lstnew_2val(ft_strdup("?"), ft_strdup("0"));
	tmp->visible = 0;
	ft_lstadd_back_2val(env, tmp);
	tmp = *env;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->flag, "TERM"))
			flag = 1;
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		tmp = ft_lstnew_2val(ft_strdup("TERM"), ft_strdup("xterm-256color"));
		ft_lstadd_back_2val(env, tmp);
	}
}

int	check_add_env(t_list_2val **env, char **first_env)
{
	t_list_2val		*tmp;
	int				i;
	int				flag;
	static char		buf[1000];

	flag = 0;
	tmp = ft_lstnew_2val(ft_strdup("PWD"), ft_strdup(getcwd(buf, 1000)));
	ft_lstadd_back_2val(env, tmp);
	tmp = ft_lstnew_2val(ft_strdup("invisPWD"), ft_strdup(getcwd(buf, 1000)));
	tmp->visible = 0;
	ft_lstadd_back_2val(env, tmp);
	tmp = ft_lstnew_2val(ft_strdup("_"), ft_strdup("/usr/bin/env"));
	ft_lstadd_back_2val(env, tmp);
	i = -1;
	while (first_env[++i])
		if (ft_strnstr(first_env[i], "SHLVL", 5))
			flag = 1;
	if (flag != 1)
	{
		tmp = ft_lstnew_2val(ft_strdup("SHLVL"), ft_strdup("1"));
		ft_lstadd_back_2val(env, tmp);
		return (1);
	}
	return (0);
}

t_list_2val	*pars_env(char **env, int i)
{
	t_list_2val	*tmp;
	t_list_2val	*new_env;
	char		*flag;
	char		*value;
	int			shlvl;

	new_env = ((void *)0);
	shlvl = check_add_env(&new_env, env);
	while (env[++i])
	{
		find_flag_value(env[i], &flag, &value);
		if (!strcmp(flag, "PWD") || !strcmp(flag, "_") || shlvl == 1)
		{
			free (value);
			free (flag);
			continue ;
		}
		tmp = ft_lstnew_2val(flag, value);
		tmp->visible = 1;
		if (!tmp)
			ft_error_malloc("Error malloc: pars_env.c - tmp");
		ft_lstadd_back_2val(&new_env, tmp);
	}
	add_baks(&new_env);
	return (new_env);
}
