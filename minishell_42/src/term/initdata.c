/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:19:40 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 20:40:46 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

void	sigint_start(int first)
{
	int		flag;

	if (g_data->line == 0)
		return ;
	free_line(&g_data->line);
	g_data->line = ft_strdup("\n\033[1;32mmini_shell:\033[0m");
	g_data->line_size = ft_strlen(g_data->line);
	g_data->cursor_pos = ft_strlen(g_data->line);
	ft_bzero(g_data->buf, 6);
	write(1, "\n\033[1;32mmini_shell: \033[0m", 25);
	g_data->sigint_flag = 1;
	flag = first;
}

t_line	*init_data(t_history **history)
{
	t_line		*data;

	if (!g_data)
		data = malloc(sizeof(t_line));
	else
		data = g_data;
	data->name = ft_strdup("\033[1;32mmini_shell: \033[0m");
	data->line = NULL;
	data->tmp = NULL;
	data->free_history = *history;
	g_data = data;
	data->sigint_flag = 0;
	signal(SIGINT, sigint_start);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(EOF, SIG_IGN);
	return (data);
}
