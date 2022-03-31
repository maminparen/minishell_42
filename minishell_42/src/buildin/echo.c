/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:32:35 by hzona             #+#    #+#             */
/*   Updated: 2021/11/15 22:25:59 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	init_echo(int *i, int *start, int *n)
{
	*i = 1;
	*start = 0;
	*n = 0;
}

void	while_cmd(t_cmd	*cmd, int *i, int *j, int *start)
{
	while (cmd->cmd[*i][2 + *j])
	{
		if (cmd->cmd[*i][2 + *j] != '\0' && cmd->cmd[*i][2 + *j] != 'n')
			*start = 1;
		*j = *j + 1;
	}
}

void	write_start(t_cmd *cmd, int i)
{
	write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	write (1, " ", 1);
}

void	command_echo(t_cmd	*cmd)
{
	int	i;
	int	start;
	int	j;
	int	n;

	init_echo(&i, &start, &n);
	while (cmd->cmd[i])
	{
		j = 0;
		if (start == 0 && cmd->cmd[i][0] == '-' && cmd->cmd[i][1] == 'n' )
		{
			while_cmd(cmd, &i, &j, &start);
			if (start == 0)
				n = 1;
		}
		else
			start = 1;
		if (start == 1)
			write_start(cmd, i);
		i++;
	}
	if (n == 0)
		write (1, "\n", 1);
	exit (0);
}
