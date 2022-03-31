/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:39:04 by hzona             #+#    #+#             */
/*   Updated: 2021/11/15 19:03:31 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

static void	add_last(t_line *data)
{
	write(1, &data->buf[0], 1);
	if (data->cursor_pos % data->width == 0)
		tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
}

static void	add_middle(t_line *data)
{
	size_t	i;

	tputs(tgetstr("sc", NULL), 1, &ft_putchar_int);
	ft_putstr_fd(data->line + data->cursor_pos - 1, 1);
	tputs(tgetstr("rc", NULL), 1, &ft_putchar_int);
	if (data->cursor_pos % data->width == 0)
	{
		tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
		i = data->width;
		while (i--)
			tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
	}
	else
		tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
}

void	ctrl_arrow(t_line *data, char arrow)
{
	if (arrow == 67)
		next_word(data);
	else if (arrow == 65)
	{
		if (data->coord_x < 1)
			return ;
		up_line(data);
	}
	else
	{
		if (data->coord_x == data->line_size / data->width)
			return ;
		down_line(data);
	}
}

void	insert(t_line *data)
{
	data->line = realloc(data->line, (data->line_size + 2));
	ft_memset(data->line + data->line_size, 0, 2);
	ft_memmove(data->line + data->cursor_pos + 1, data->line + data->cursor_pos,
		ft_strlen(data->line + data->cursor_pos));
	data->line[data->cursor_pos] = data->buf[0];
	data->cursor_pos++;
	if (data->line_size == data->cursor_pos - 1)
		add_last(data);
	else
		add_middle(data);
}

void	input(t_line *data, t_history **history, t_history **tmp)
{
	if (data->buf[0] == 4 && ft_strlen(data->line) == data->name_size)
		command_exit();
	else if (data->buf[0] == 27 && data->buf[5] != 0)
		ctrl_arrow(data, data->buf[5]);
	else if (ft_isprint(data->buf[0]) && data->buf[1] == 0)
		insert(data);
	else if (data->buf[0] == 127 && data->cursor_pos > data->name_size)
		delete2(data);
	else if (data->buf[0] == 27 && (data->buf[2] == 65 || data->buf[2] == 66))
		*tmp = search_history(data, *tmp, data->buf[2]);
	else if (data->buf[0] == 27)
		move_cursor(data);
	ft_bzero(data->buf, 6);
	if (ft_lstsize_2(*history) != 0 && tmp == 0)
		*tmp = *history;
}
