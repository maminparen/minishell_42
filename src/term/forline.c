/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:35:53 by hzona             #+#    #+#             */
/*   Updated: 2021/11/13 11:48:09 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

void	up_line(t_line *data)
{
	tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
	data->cursor_pos -= data->width;
	if (data->cursor_pos < data->name_size)
		while (data->cursor_pos++ != data->name_size)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
}

void	down_last(t_line *data)
{
	size_t	temp;

	temp = data->line_size % data->width;
	if (temp >= data->coord_y)
	{
		while (data->coord_y--)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		data->cursor_pos += data->width;
	}
	else
	{
		data->cursor_pos += data->width - data->coord_y;
		data->cursor_pos += temp;
		while (temp-- > 0)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
	}
}

void	down_line(t_line *data)
{
	tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
	if (data->line_size == data->coord_x + 1)
		down_last(data);
	else
	{
		write(1, "qwe\n", 4);
		while (data->coord_y--)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		data->cursor_pos += data->width;
	}
}

void	next_word(t_line *data)
{
	size_t	temp;
	char	*space;

	space = ft_strchr(&data->line[data->cursor_pos], ' ');
	if (!space)
		return ;
	while (*space == ' ')
		space++;
	if (space == NULL)
		return ;
	if (data->coord_x < (space - data->line) / data->width)
	{
		while (data->coord_x++ < (space - data->line) / data->width)
			tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
		temp = (space - data->line) % data->width;
		while (temp--)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		data->cursor_pos = (size_t)(space - data->line);
		return ;
	}
	while ((int)data->cursor_pos++ < (space - data->line))
		tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
	data->cursor_pos--;
}

void	init_line(t_line *data)
{
	ft_bzero(data->buf, 6);
	data->line = ft_strdup(data->name);
	data->name_size = ft_strlen(data->name);
	data->line_size = data->name_size;
	data->cursor_pos = data->name_size;
	if (data->sigint_flag == 1)
	{
		data->sigint_flag = 0;
		return ;
	}
	write(1, "\033[1;32mmini_shell: \033[0m", 24);
}
