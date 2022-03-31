/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:16:41 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 21:57:47 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_errno(int status, t_list_2val *l_env)
{
	t_list_2val	*tmp;

	tmp = l_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->flag, "?"))
		{
			free(tmp->value);
			tmp->value = ft_itoa(status);
			if (!tmp->value)
				ft_error_malloc("Error malloc: \
						find_fdin_from_stdin.c - tmp->value");
			break ;
		}	
		tmp = tmp->next;
	}
}

t_execute	*init_execute(int num, t_list_2val *l_env)
{
	t_execute	*execute;
	int			i;

	execute = malloc(sizeof(t_execute));
	if (!execute)
		ft_error_malloc("Error malloc: execute.c - execute");
	execute->fd = (int *)malloc(sizeof(int) * (num + 1) * 2);
	if (!execute->fd)
		ft_error_malloc("Error malloc: execute.c - execute->fd");
	i = -1;
	while (++i < num + 1)
		if (pipe(execute->fd + i * 2) == -1)
			ft_error_malloc("Error pipe: execute.c - fd");
	execute->pid = (int *)malloc(sizeof(int) * num);
	if (!execute->pid)
		ft_error_malloc("Error malloc: execute.c - pid");
	execute->fd_correct = 1;
	execute->fdin = 0;
	execute->fdout = 1;
	execute->num_cmd = num;
	execute->error_fd = ((void *)0);
	execute->err_fd = 0;
	execute->l_env = l_env;
	return (execute);
}
