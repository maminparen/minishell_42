/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:42:00 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 15:11:39 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	move_home_cd(t_list_2val *l_env)
{
	t_list_2val	*temp;
	char		*tmp2;

	temp = l_env;
	while (temp)
	{
		if (ft_strnstr(temp->flag, "invisPWD", 9))
			tmp2 = temp->value;
		temp = temp->next;
	}
	temp = l_env;
	while (temp)
	{
		if (ft_strnstr(temp->flag, "OLDPWD", 6))
		{
			free_line(&temp->value);
			temp->value = tmp2;
		}
		if (ft_strnstr(temp->flag, "invisPWD", 9))
			temp->value = ft_strdup(getenv("HOME"));
		temp = temp->next;
	}	
}

void	move_up_cd(t_list_2val *temp, t_list_2val *temp2, char *tmp, int i)
{
	update_errno(0, temp);
	while (temp)
	{
		if (ft_strnstr(temp->flag, "invisPWD", 9))
			tmp = ft_strdup(temp->value);
		temp = temp->next;
	}
	while (temp2)
	{
		if (ft_strnstr(temp2->flag, "OLDPWD", 6))
		{
			free_line(&temp2->value);
			temp2->value = tmp;
		}
		if (ft_strnstr(temp2->flag, "invisPWD", 9))
		{
			i = ft_strlen(temp2->value) - 1;
			while (temp2->value[i] && temp2->value[i] != '/')
				i--;
			if ((i != 0 && temp2->value[i] == '/') || 0 == i++)
				temp2->value[i] = '\0';
		}
		temp2 = temp2->next;
	}	
}

void	open_dir(t_list_2val *temp, t_list_2val *temp2, char *tmp)
{
	char	*pwd;

	while (temp)
	{
		if (ft_strnstr(temp->flag, "invisPWD", 9))
			pwd = ft_strdup(temp->value);
		temp = temp->next;
	}
	while (temp2)
	{
		if (ft_strnstr(temp2->flag, "OLDPWD", 6))
		{
			free_line(&temp2->value);
			temp2->value = pwd;
		}
		if (ft_strnstr(temp2->flag, "invisPWD", 9))
		{
			free(temp2->value);
			temp2->value = tmp;
		}
		temp2 = temp2->next;
	}	
}

void	move_to_dir(t_list_2val *l_env, char *tmp)
{
	DIR		*dir;
	char	*real;
	char	buffff[1000];

	real = absolute_path(l_env, tmp, NULL, NULL);
	if ((real[0] == '/' && real[1] == '/') || real[ft_strlen(real) - 1] == '/')
		real = new_real(real);
	dir = opendir(real);
	if (dir == 0 && getcwd(buffff, 1000))
	{
		write(1, "\033[1;32mmini_shell: \033[0mcd: ", 28);
		write(1, tmp, ft_strlen(tmp));
		write(1, ": No such file or directory\n", 28);
		update_errno(1, l_env);
		free_line(&real);
	}
	else if (dir == 0 && !getcwd(buffff, 1000))
		write(1, "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 108);
	else
	{
		open_dir(l_env, l_env, real);
		update_errno(0, l_env);
		closedir(dir);
	}
}

void	command_cd(t_cmd *cmd, t_list_2val *l_env)
{
	t_list_2val	*tmp;

	if (cmd->cmd[1] == NULL || !ft_strcmp(cmd->cmd[1], "~"))
		move_home_cd(l_env);
	else if (!ft_strcmp(cmd->cmd[1], "..\0"))
		move_up_cd(l_env, l_env, NULL, 0);
	else if (ft_strcmp(cmd->cmd[1], "."))
		move_to_dir(l_env, cmd->cmd[1]);
	tmp = l_env;
	while (l_env)
	{
		if (!ft_strcmp("invisPWD", l_env->flag) && !chdir(l_env->value))
			break ;
		l_env = l_env->next;
	}
	while (tmp)
	{
		if (!ft_strcmp(tmp->flag, "PWD") && l_env)
		{
			free_line(&tmp->value);
			tmp->value = ft_strdup(l_env->value);
		}
		tmp = tmp->next;
	}
}
