/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_access_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:10:25 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:10:58 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_our_cmd(char *cmd)
{
	int		i;
	char	*tmp_cmd;

	tmp_cmd = strdup(cmd);
	if (!tmp_cmd)
		ft_error_malloc("Error malloc: pars_list_access_cmd.c - tmp_cmd");
	i = -1;
	while (*(tmp_cmd + ++i))
		*(tmp_cmd + i) = ft_tolower(*(tmp_cmd + i));
	if (cmd && \
		(!ft_strcmp(tmp_cmd, "echo") || !ft_strcmp(tmp_cmd, "cd") || \
		!ft_strcmp(tmp_cmd, "pwd") || !ft_strcmp(tmp_cmd, "export") || \
		!ft_strcmp(tmp_cmd, "unset") || !ft_strcmp(tmp_cmd, "env") || \
		!ft_strcmp(tmp_cmd, "exit")))
	{
		free (tmp_cmd);
		i = -1;
		while (*(cmd + ++i))
			*(cmd + i) = ft_tolower(*(cmd + i));
		return (1);
	}
	free (tmp_cmd);
	return (0);
}

static char	*find_check_cmd(char **path, char *tmp_cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], tmp_cmd);
		if (!tmp)
			ft_error_malloc("Error malloc: pars_list_access_cmd.c - tmp");
		if (access(tmp, F_OK) == 0)
			return (tmp);
		else
			free(tmp);
	}
	return ((void *)0);
}

static char	**find_path(t_list_2val *l_env)
{
	char		**path;
	int			i;
	t_list_2val	*env_tmp;

	path = ((void *)0);
	i = -1;
	env_tmp = l_env;
	while (env_tmp)
	{
		if (!ft_strcmp("PATH", env_tmp->flag))
		{
			path = ft_split(env_tmp->value, ':');
			if (!path)
				ft_error_malloc("Error malloc: pars_list_access_cmd.c - path");
			break ;
		}
		env_tmp = env_tmp->next;
	}
	return (path);
}

char	*pars_list_access_cmd(char *cmd, t_list_2val *l_env, int *our_cmd)
{
	char		*cmd_tmp;
	char		*cmd_tmp_slash;
	char		**path;

	*our_cmd = check_our_cmd(cmd);
	if (*our_cmd == 0 && cmd && *cmd != '\0')
	{		
		path = find_path(l_env);
		if (!path)
			return (cmd);
		cmd_tmp_slash = ft_strjoin("/", cmd);
		if (!cmd_tmp_slash)
			ft_error_malloc("Error malloc: \
							pars_list_access_cmd.c - cmd_tmp_slash");
		cmd_tmp = find_check_cmd(path, cmd_tmp_slash);
		if (cmd_tmp)
		{
			free(cmd);
			cmd = cmd_tmp;
		}
		free(cmd_tmp_slash);
		ft_free_split(path);
	}
	return (cmd);
}
