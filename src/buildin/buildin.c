/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:32:08 by hzona             #+#    #+#             */
/*   Updated: 2021/11/16 11:30:42 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	command_env(t_list_2val	*l_env)
{
	t_list_2val	*temp;

	temp = l_env;
	while (temp)
	{
		if (temp->visible)
		{
			write (1, temp->flag, ft_strlen(temp->flag));
			write (1, "=", 1);
			write (1, temp->value, ft_strlen(temp->value));
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
	exit (0);
}

void	command_pwd(t_list_2val	*l_env)
{
	t_list_2val	*temp;

	temp = l_env;
	while (temp)
	{
		if (ft_strnstr(temp->flag, "invisPWD", 9))
		{
			write (1, temp->value, ft_strlen(temp->value));
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
	exit (0);
}

void	sort_env(t_list_2val *l_env)
{
	t_list_2val	*tmp;
	char		*temp;
	int			tmp2;

	tmp = l_env;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->flag, tmp->next->flag) > 0)
		{
			temp = tmp->flag;
			tmp->flag = tmp->next->flag;
			tmp->next->flag = temp;
			temp = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = temp;
			tmp2 = tmp->visible;
			tmp->visible = tmp->next->visible;
			tmp->next->visible = tmp2;
			tmp = l_env;
		}
		else
			tmp = tmp->next;
	}
}

void	print_export(t_list_2val *l_env)
{
	t_list_2val	*tmp;

	tmp = l_env;
	sort_env(l_env);
	while (l_env)
	{
		if (l_env->visible)
		{
			write(1, "declare -x ", 11);
			write(1, l_env->flag, ft_strlen(l_env->flag));
			if (l_env->value != NULL)
			{
				write(1, "=\"", 2);
				write(1, l_env->value, ft_strlen(l_env->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		l_env = l_env->next;
	}
	update_errno(0, tmp);
}

void	find_flag_value2(char *env, char **flag, char **value)
{
	int	i;

	i = 0;
	while (*(env + i) != '=' && *(env + i) != '\0')
		i++;
	*flag = ft_substr(env, 0, i);
	if (*(env + i) == '\0')
	{
		*value = NULL;
		return ;
	}
	if (!*flag)
		ft_error_malloc("Error malloc: pars_env.c - flag");
	*value = ft_substr(env, i + 1, ft_strlen(env));
	if (!*value)
		ft_error_malloc("Error malloc: pars_env.c - value");
}
