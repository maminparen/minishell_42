/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:07:59 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 21:17:53 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

void	read_file(int read_b)
{
	int		fd;
	char	buffer[11];

	fd = open("./src/term/head.txt", O_RDONLY);
	if (!fd || fd < 0)
		return ;
	while (read_b)
	{
		read_b = read(fd, buffer, 10);
		buffer[read_b] = '\0';
		printf("%s", buffer);
	}
	printf("\n");
	close(fd);
}

void	free_sh(t_sh **sh)
{
	t_cmd		*tmp_cmd;
	t_list_2val	*tmp_fd;

	free((*sh)->line);
	(*sh)->line = NULL;
	while ((*sh)->l_cmd)
	{
		tmp_cmd = (*sh)->l_cmd;
		free(tmp_cmd->part_cmd);
		while (tmp_cmd->fd_list)
		{
			tmp_fd = tmp_cmd->fd_list;
			free(tmp_fd->flag);
			free(tmp_fd->value);
			tmp_cmd->fd_list = tmp_cmd->fd_list->next;
			free(tmp_fd);
		}
		ft_free_split(tmp_cmd->cmd);
		(*sh)->l_cmd = (*sh)->l_cmd->next;
		free(tmp_cmd);
	}
	free((*sh)->error_syntax);
	(*sh)->error_syntax = NULL;
	free(*sh);
	(*sh) = NULL;
}

int	main(int argc, char **argv, char **envm)
{
	char		*last_cmd;
	t_history	*history;
	t_sh		*sh;
	t_list_2val	*l_env;

	(void)argc;
	(void)argv;
	history = NULL;
	l_env = pars_env(envm, -1);
	read_file(1);
	while (1)
	{
		last_cmd = ft_termcap(&history, l_env);
		sh = pars(last_cmd, l_env);
		if (!sh->flag_error_syntax)
			make_execute(sh);
		free_sh(&sh);
	}
	return (0);
}
