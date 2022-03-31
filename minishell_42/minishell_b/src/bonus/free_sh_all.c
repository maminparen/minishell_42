/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:55:54 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 16:15:09 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

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

void	free_sh_all(t_sh_all **sh_all)
{
	free((*sh_all)->line);
	(*sh_all)->line = NULL;
	if ((*sh_all)->sh_array)
		free((*sh_all)->sh_array);
	(*sh_all)->sh_array = NULL;
	free((*sh_all)->connect);
	(*sh_all)->connect = NULL;
	free((*sh_all)->skobka);
	(*sh_all)->skobka = NULL;
	free(*sh_all);
	(*sh_all) = NULL;
}
