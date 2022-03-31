/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:22:45 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 16:44:59 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fdin_fdout(t_execute *execute)
{
	if (execute->fdin > 0)
		close(execute->fdin);
	if (execute->fdout > 1)
		close(execute->fdout);
}

void	close_fd(t_execute *execute)
{
	int	i;

	i = -1;
	while (++i < (execute->num_cmd + 1) * 2)
		close(execute->fd[i]);
}

void	clear_execute(t_execute *execute)
{
	free(execute->fd);
	free(execute->pid);
	free(execute->error_fd);
	free(execute);
}

void	update_execute(t_execute *execute)
{
	close_fdin_fdout(execute);
	execute->fdin = 0;
	execute->fdout = 1;
	free(execute->error_fd);
	execute->error_fd = ((void *)0);
}

void	close_all_execute(t_execute *execute, int ifff)
{
	int	i;
	int	status;

	close_fd(execute);
	close_fdin_fdout(execute);
	i = -1;
	status = 0;
	while (++i < execute->num_cmd)
		waitpid(execute->pid[i], &status, 0);
	if (!execute->error_fd && !execute->err_fd && ifff != 2)
	{
		if (WIFEXITED(status))
			update_errno(WEXITSTATUS(status), execute->l_env);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				update_errno(130, execute->l_env);
			else
				update_errno(WTERMSIG(status), execute->l_env);
		}
		else if (WIFSTOPPED(status))
			update_errno(WSTOPSIG(status), execute->l_env);
	}
	clear_execute(execute);
}
