/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:43:16 by hzona             #+#    #+#             */
/*   Updated: 2021/11/16 16:01:01 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

char	*while_pwd(t_list_2val *l_env, char *tmp, char *freec)
{
	while (l_env)
	{
		if (!ft_strcmp(l_env->flag, "invisPWD"))
		{
			if (tmp[1] == '/')
				tmp = ft_strdup(tmp + 1);
			else
				tmp = ft_strjoin("/", tmp);
			freec = tmp;
			tmp = ft_strjoin(l_env->value, tmp);
			free_line(&freec);
			return (tmp);
		}
		l_env = l_env->next;
	}
	return (NULL);
}

char	*while_path(t_list_2val *l_env, char *line,	char *tmp, int count)
{
	int		i;
	char	*freec;

	while (l_env)
	{
		if (!ft_strcmp(l_env->flag, "invisPWD"))
		{
			line = ft_strdup(l_env->value);
			i = ft_strlen(line);
			while (--i >= 0 && count > 0)
			{
				if ((line[i] == '/' && 1 < count --)
					|| (line[i] == '/' && 0 < count && tmp[0] != '\0'))
					line[i] = '\0';
				else if (line[i] == '/' && 0 <= count--)
					line[i + 1] = '\0';
			}
			freec = line;
			tmp = ft_strjoin(line, tmp);
			free_line(&freec);
			return (tmp);
		}
		l_env = l_env->next;
	}
	return (NULL);
}

char	*absolute_path(t_list_2val *l_env, char *tmp, char *ret, char *freec)
{
	int		count;
	char	*line;

	line = NULL;
	if (tmp[0] == '/')
		return (ft_strdup(tmp));
	if (tmp[0] != '.' || (tmp[0] == '.' && tmp[1] != '.')
		|| (tmp[0] == '.' && tmp[1] == '.' && tmp[2] != '/'))
		ret = while_pwd(l_env, tmp, freec);
	if (ret)
		return (ret);
	if (tmp[0] == '.' && tmp[1] == '.' && tmp[2] == '/')
	{
		count = 0;
		while (tmp[0] == '.' && tmp[1] == '.' && tmp[2] == '/' && ++count)
			tmp = tmp + 3;
		while (l_env)
		{
			ret = while_path(l_env, line, tmp, count);
			if (ret)
				return (ret);
		}
	}
	return (NULL);
}
