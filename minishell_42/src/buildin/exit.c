/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:27:55 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 21:05:24 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	command_exit(void)
{
	write(1, "exit\n", 5);
	exit (0);
}

int	all_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_exit(t_cmd	*cmd)
{
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
	write(1, "exit: ", 6);
	write(1, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
	write(1, ": numeric argument required\n: ", 28);
}

void	print_exit2(t_cmd	*cmd)
{
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
	write(1, "exit: too many arguments\n",
		ft_strlen("exit: too many arguments\n"));
	update_errno(1, cmd->l_env);
}

void	command_exit_input(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	write(1, "exit\n", 5);
	if (i == 2 && all_num(cmd->cmd[1]))
	{
		exit(ft_atoi(cmd->cmd[1]));
	}
	else if (i >= 2 && !all_num(cmd->cmd[1]))
	{
		print_exit(cmd);
		exit (255);
	}
	else if (i > 2)
		print_exit2(cmd);
	else
		exit (0);
}
