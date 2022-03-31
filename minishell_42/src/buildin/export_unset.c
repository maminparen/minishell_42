/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:52:02 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 20:01:01 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	delete_env(char *flag, t_list_2val *l_env,
	t_list_2val *tmp, t_list_2val *prev)
{
	while (l_env)
	{
		tmp = l_env->next;
		if (!strcmp(flag, l_env->flag))
		{
			free(l_env->flag);
			free(l_env->value);
			if (tmp)
			{
				l_env->flag = tmp->flag;
				l_env->value = tmp->value;
				l_env->next = tmp->next;
				free (tmp);
			}
			else
			{
				prev->next = NULL;
				free(l_env);
			}
		}
		prev = l_env;
		l_env = l_env->next;
	}
}

void	print_export2(t_cmd *cmd, int i, t_list_2val *l_env)
{
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
	write(1, "export: ", 8);
	write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	write(1, ": not a valid identifier\n: ", 25);
	update_errno(1, l_env);
}

void	command_export(t_cmd *cmd, t_list_2val *l_env, char *flag, char *value)
{
	int			i;
	t_list_2val	*tmp;

	i = 0;
	if (cmd->cmd[1] == NULL)
		return (print_export(l_env));
	while (cmd->cmd[++i])
	{
		if (!ft_isalpha(cmd->cmd[i][0]) && !(cmd->cmd[i][0] == '_'))
			print_export2(cmd, i, l_env);
		else
		{
			find_flag_value2(cmd->cmd[i], &flag, &value);
			if (used_flag(flag, l_env) && value != NULL)
				delete_env(flag, l_env, NULL, NULL);
			if (!used_flag(flag, l_env))
			{
				tmp = ft_lstnew_2val(flag, value);
				if (!tmp)
					ft_error_malloc("Error malloc: pars_env.c - tmp");
				ft_lstadd_back_2val(&l_env, tmp);
				update_errno(0, l_env);
			}
		}
	}
}

void	command_unset(t_cmd *cmd, t_list_2val *l_env)
{
	int			i;
	t_list_2val	*tmp;
	int			error;

	tmp = l_env;
	if (cmd->cmd[1] == NULL)
		return ;
	i = 1;
	error = 0;
	while (cmd->cmd[i])
	{
		if (ft_isdigit(cmd->cmd[i][0]))
		{
			write(1, "\033[1;32mmini_shell: \033[0m", 24);
			write(1, "unset: ", 7);
			write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			write(1, ": not a valid identifier\n: ", 25);
			error = 1;
		}
		else
			delete_env(cmd->cmd[i], l_env, NULL, NULL);
		i++;
	}
	update_errno(error, tmp);
}
