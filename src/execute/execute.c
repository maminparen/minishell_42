/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:01:48 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 21:53:55 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_execve(char *cmd)
{
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
	write(1, cmd, ft_strlen(cmd));
	write(1, ": command not found\n: ", 20);
}

static void	process_fork_execute(t_execute *execute, \
								t_cmd *tmp, t_sh *sh, int i)
{
	if (execute->pid[i] < 0)
		ft_error_malloc("Error fork: execute.c - pid");
	if (execute->pid[i] == 0)
	{
		dup2(execute->fdin, STDIN_FILENO);
		dup2(execute->fdout, STDOUT_FILENO);
		close_fd(execute);
		close_fdin_fdout(execute);
		if (tmp->cmd[0][0] == '\0')
			;
		else if (tmp->our_cmd == 1)
			do_our_in_pipe(sh, tmp);
		else
		{
			execve(tmp->cmd[0], tmp->cmd, crt_new_env_array(execute->l_env));
			print_execve(tmp->cmd[0]);
			exit(127);
		}
		exit (errno);
	}
}

int	make_execute_no_error_fd(t_execute *execute, \
								t_cmd *tmp, t_sh *sh, int i)
{
	if (!ft_strcmp(tmp->cmd[0], "exit") || \
		!ft_strcmp(tmp->cmd[0], "cd") || \
		(!ft_strcmp(tmp->cmd[0], "export") && tmp->cmd[1] != NULL) || \
		!ft_strcmp(tmp->cmd[0], "unset"))
	{
		if (sh->num_cmd > 1)
		{
			update_execute(execute);
			return (1);
		}
		else
		{
			do_our_out_pipe(sh, tmp);
			return (2);
		}
	}
	execute->pid[i] = fork();
	process_fork_execute(execute, tmp, sh, i);
	update_execute(execute);
	return (0);
}

void	print_fdin_fdout(char *cmd)
{
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
	write(1, cmd, ft_strlen(cmd));
	write(1, "\n", 1);
}

void	make_execute(t_sh *sh)
{
	t_execute	*execute;
	t_cmd		*tmp;
	int			i;
	int			ifff;

	execute = init_execute(sh->num_cmd, sh->l_env);
	tmp = sh->l_cmd;
	i = -1;
	while (tmp)
	{
		i++;
		find_fdin_fdout_upgrade(execute, tmp, i);
		if (execute->error_fd)
			print_fdin_fdout(execute->error_fd);
		else if (!execute->err_fd)
			ifff = make_execute_no_error_fd(execute, tmp, sh, i);
		if (ifff == 2)
			break ;
		tmp = tmp->next;
	}
	close_all_execute(execute, ifff);
}
