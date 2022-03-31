/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:07:40 by hzona             #+#    #+#             */
/*   Updated: 2021/11/11 12:07:40 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"

int	init_terminal(t_line *data, t_list_2val *env)
{
	struct termios	change;

	while (env)
	{
		if (!ft_strcmp(env->flag, "TERM"))
			break ;
		env = env->next;
	}
	tgetent(NULL, env->value);
	tcgetattr(0, &change);
	change.c_lflag &= ~(ECHO);
	change.c_lflag &= ~(ICANON);
	change.c_cc[VMIN] = 1;
	change.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &change);
	ioctl(0, TIOCGWINSZ, &data->window_size);
	data->width = data->window_size.ws_col;
	data->height = data->window_size.ws_row;
	tputs(tgetstr("sc", NULL), 1, &ft_putchar_int);
	init_line(data);
	return (0);
}

void	write_n(int test)
{
	test = 0;
	write(1, "\n", 1);
}

void	restore_term(void)
{
	struct termios	change;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &change);
	change.c_lflag |= ICANON;
	change.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &change);
	signal(SIGINT, write_n);
	signal(SIGQUIT, quiet_signal);
}

void	init_cursor(t_line *data)
{
	size_t	tmp;

	ioctl(0, TIOCGWINSZ, &data->window_size);
	data->width = data->window_size.ws_col;
	data->height = data->window_size.ws_row;
	data->line_size = ft_strlen(data->line);
	tmp = data->cursor_pos;
	data->coord_x = 0;
	while (tmp >= data->width)
	{
		tmp -= data->width;
		data->coord_x++;
	}
	data->coord_y = tmp;
}

char	*ft_termcap(t_history **history, t_list_2val *env)
{
	t_line			*data;
	char			*res;
	t_history		*tmp;

	data = init_data(history);
	tmp = *history;
	res = NULL;
	init_terminal(data, env);
	while ((read(0, data->buf, 6)) && data->buf[0] != 10)
	{
		init_cursor(data);
		input(data, history, &tmp);
	}
	write(1, "\n", 1);
	if (data->buf[0] == 10 && ft_strlen(data->name) == ft_strlen(data->line))
	{
		free_all(&data);
		restore_term();
		return (ft_termcap(history, env));
	}
	res = ft_strdup(data->line + ft_strlen(data->name));
	ft_lstadd_front_2(history, ft_lstnew_2(ft_strdup(res)));
	restore_term();
	free_all(&data);
	return (res);
}
