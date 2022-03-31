/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fdin_from_stdin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:50:44 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/19 16:57:07 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_stdin_fork(t_execute *execute, int ret)
{
	int	status;

	waitpid(ret, &status, 0);
	update_errno(WEXITSTATUS(status), execute->l_env);
	if (errno)
	{
		execute->error_fd = ft_strdup(strerror(errno));
		errno = 0;
	}
}

void	sigint_quit(int first)
{
	(void)first;
	exit(1);
}

void	check_ret(int ret)
{
	if (ret < 0)
		ft_error_malloc("Error fork: find_fdin_fdout.c - ret");
}

void	create_fd_from_stdin(t_execute *execute, int i, char *value, int ret)
{
	int		r;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	ret = fork();
	check_ret(ret);
	if (ret == 0)
	{
		signal(SIGINT, sigint_quit);
		dup2(0, STDIN_FILENO);
		dup2(execute->fd[i * 2 + 1], STDOUT_FILENO);
		close_fd(execute);
		while (1)
		{
			r = gnl(0, &line);
			if ((r == 0 && !line) || r == -1 || !ft_strcmp(value, line))
				break ;
			write(1, line, ft_strlen(line));
			if (r != 0)
				write(1, "\n", 1);
			free(line);
		}
		exit (0);
	}
	close_stdin_fork(execute, ret);
}
