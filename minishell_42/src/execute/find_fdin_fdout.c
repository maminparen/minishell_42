/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fdin_fdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:57:22 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 22:03:12 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_fdout(t_execute *execute, char *flag, char *value)
{
	if (*flag == '>' && *(flag + 1) == '>')
	{
		if (execute->fdout > 1)
			close (execute->fdout);
		execute->fdout = open(value, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	else if (*flag == '>')
	{
		if (execute->fdout > 1)
			close (execute->fdout);
		execute->fdout = open(value, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	if (execute->fdout < 0)
	{
		update_errno(errno, execute->l_env);
		execute->error_fd = ft_strdup(strerror(errno));
		errno = 0;
	}
}

static void	find_fdin(t_execute *execute, char *value)
{
	if (execute->fdin > 0)
		close (execute->fdin);
	execute->fdin = open(value, O_RDONLY);
	if (execute->fdin < 0)
	{
		update_errno(errno, execute->l_env);
		execute->error_fd = ft_strdup(strerror(errno));
		errno = 0;
	}
}

static void	find_fdin_fdout(t_list_2val *fd, t_execute *execute, int i)
{
	char		*flag;

	while (fd && !execute->error_fd)
	{		
		flag = fd->flag;
		if (*flag == '<' && *(flag + 1) == '<')
		{	
			if (execute->fdin > 0)
				close (execute->fdin);
			create_fd_from_stdin(execute, i, fd->value, 0);
			execute->fdin = execute->fd[i * 2];
		}
		else if (*flag == '<')
			find_fdin(execute, fd->value);
		else if (*flag == '>')
			find_fdout(execute, flag, fd->value);
		fd = fd->next;
	}
}

void	find_fdin_fdout_upgrade(t_execute *execute, t_cmd *cmd, int i)
{
	find_fdin_fdout(cmd->fd_list, execute, i);
	if (!execute->error_fd)
	{
		if (execute->fdin > 0)
			;
		else if (i == 0)
			execute->fdin = 0;
		else
			execute->fdin = execute->fd[i * 2];
		if (execute->fdout > 1)
			;
		else if (!cmd->next)
			execute->fdout = 1;
		else
			execute->fdout = execute->fd[i * 2 + 3];
	}
}
