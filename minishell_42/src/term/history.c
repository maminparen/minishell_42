/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:31:35 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 18:49:44 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

t_history	*search_up(t_line *data, t_history *history)
{
	if (history == 0)
		return (history);
	else
	{
		if (ft_strlen(data->line) > data->name_size && !history->prev)
		{
			if (data->tmp)
				free(data->tmp);
			data->tmp = ft_strdup(data->line + data->name_size);
		}
		if (data->line_size > data->width)
			delete_down(data);
		free_line(&data->line);
		data->line = ft_strjoin(data->name, history->cmd);
		tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("cr", NULL), 1, &ft_putchar_int);
		write(1, data->line, ft_strlen(data->line));
		data->cursor_pos = ft_strlen(data->line);
		if (history->next)
			history = history->next;
		return (history);
	}
}

t_history	*search_first(t_line *data, t_history *history)
{
	free_line(&data->line);
	if (data->tmp)
		data->line = ft_strjoin(data->name, data->tmp);
	else
		data->line = ft_strjoin(data->name, "");
	tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, &ft_putchar_int);
	write(1, data->line, ft_strlen(data->line));
	data->cursor_pos = ft_strlen(data->line);
	return (history);
}

t_history	*search_second(t_line *data, t_history *history)
{
	history = history->prev;
	if (data->line_size > data->width)
		delete_down(data);
	free_line(&data->line);
	data->line = ft_strjoin(data->name, history->cmd);
	tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, &ft_putchar_int);
	write(1, data->line, ft_strlen(data->line));
	data->cursor_pos = ft_strlen(data->line);
	return (history);
}

t_history	*search_history(t_line *data, t_history *history, char arrow)
{
	if (arrow == 65)
		return (search_up(data, history));
	else if (history)
	{
		if ((ft_lstsize_2(history) == 0 || history->prev == 0)
			&& data->line_size > data->name_size
			&& strcmp(data->line + data->name_size, history->cmd))
			return (history);
		else if (!history->prev)
			return (search_first(data, history));
		else
			return (search_second(data, history));
	}
	return (history);
}
