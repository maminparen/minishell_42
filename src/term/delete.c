/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:33:31 by hzona             #+#    #+#             */
/*   Updated: 2021/11/15 19:02:30 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

static void	delete_last(t_line *data)
{
	int	i;

	if (data->coord_y == 0)
	{
		i = -1;
		while (i++ < (int)data->width)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar_int);
		return ;
	}
	tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
	tputs(tgetstr("dc", NULL), 1, &ft_putchar_int);
}

static void	delete_middle_lowerline(t_line *data)
{
	size_t	temp;

	temp = data->coord_x;
	tputs(tgetstr("sc", NULL), 1, &ft_putchar_int);
	while (temp < data->line_size / data->width)
	{
		tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
		temp++;
	}
	tputs(tgetstr("rc", NULL), 1, &ft_putchar_int);
}

static void	delete_middle(t_line *data)
{
	int	i;

	delete_middle_lowerline(data);
	if (data->coord_y == 0)
	{
		i = -1;
		tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
		while (i++ < (int)data->width)
			tputs(tgetstr("nd", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar_int);
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("dc", NULL), 1, &ft_putchar_int);
	}
	tputs(tgetstr("sc", NULL), 1, &ft_putchar_int);
	ft_putstr_fd(&data->line[data->cursor_pos], 1);
	tputs(tgetstr("rc", NULL), 1, &ft_putchar_int);
}

void	delete2(t_line *data)
{
	data->line = realloc(data->line, data->line_size + 1);
	data->line[data->line_size] = 0;
	ft_memmove(data->line + data->cursor_pos - 1, data->line + data->cursor_pos,
		data->line_size - data->cursor_pos + 1);
	data->cursor_pos--;
	if (data->line_size == data->cursor_pos + 1)
		delete_last(data);
	else
		delete_middle(data);
}

void	delete_down(t_line *data)
{
	while (data->coord_x++ < data->line_size / (int)data->width)
		tputs(tgetstr("do", NULL), 1, &ft_putchar_int);
	while (data->coord_x-- > 1)
	{
		tputs(tgetstr("dl", NULL), 1, &ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
	}
}
