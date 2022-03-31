/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:25:57 by hzona             #+#    #+#             */
/*   Updated: 2021/11/13 11:47:57 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

void	left_move(t_line *data)
{
	int		i;

	data->cursor_pos--;
	if (data->coord_x == 0)
	{
		tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
		return ;
	}
	if (data->coord_x > 0)
	{
		if ((int)data->coord_y != 0)
		{
			tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
			return ;
		}
		else
		{
			i = -1;
			while (++i < (int)data->width + 1)
				tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
			tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
			return ;
		}
	}
}

void	right_move(t_line *data)
{
	if (data->cursor_pos >= ft_strlen(data->line))
		return ;
	if (data->coord_y >= data->width - 1)
	{
		tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
		data->cursor_pos++;
		return ;
	}
	data->cursor_pos++;
	tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
}

void	move_home(t_line *data)
{
	if (data->cursor_pos == data->name_size)
		return ;
	while (data->coord_x-- > 0)
		tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
	if (data->coord_y > data->name_size)
		while (data->coord_y-- > data->name_size)
			tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
	else
		while (data->coord_y++ < data->name_size)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
	data->cursor_pos = data->name_size;
}

void	move_end(t_line *data)
{
	int			flag;
	size_t		i;

	i = 0;
	flag = 0;
	if (data->cursor_pos == data->line_size)
		return ;
	else if (data->line_size < data->width && data->coord_x == 0)
		while (data->coord_y++ < data->line_size)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
	else
	{
		while (data->coord_x++ < data->line_size / data->width && (++flag))
			tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
		if (flag == 0)
			while (data->coord_y++ < data->line_size % data->width)
				tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		else
			while (i++ < data->line_size % data->width)
				tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
	}
	data->cursor_pos = data->line_size;
}

void	move_cursor(t_line *data)
{
	if (data->buf[2] == 72)
		move_home(data);
	else if (data->buf[2] == 70)
		move_end(data);
	else if (data->buf[2] == 68)
	{
		if (!(data->cursor_pos > data->name_size))
			return ;
		else
			left_move(data);
	}
	else
		right_move(data);
}
