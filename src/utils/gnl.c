/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:40:41 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:42:26 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*gnl_reminder(char *rem, char **line)
{
	char	*p_n;

	p_n = ((void *)0);
	if (*rem)
	{
		p_n = ft_strchr(rem, '\n');
		if (p_n)
		{
			*p_n = '\0';
			*line = ft_strdup(rem);
			rem = ft_strcpy(rem, ++p_n);
		}
		else
		{
			*line = ft_strdup(rem);
			*rem = '\0';
		}
	}
	else
		*line = ft_strdup("");
	return (p_n);
}

static int	return_and_free_line(char **line)
{
	free(*line);
	*line = NULL;
	return (0);
}

static int	gnl_read(char *rem, char *buf, char **line, int fd)
{
	char	*tmp;
	char	*p_n;
	int		r;

	r = 1;
	p_n = ((void *)0);
	while (!p_n && r)
	{
		r = read(fd, buf, 20);
		if (r == 0)
			return (return_and_free_line(line));
		buf[r] = '\0';
		p_n = ft_strchr(buf, '\n');
		if (p_n)
		{
			*p_n = '\0';
			rem = ft_strcpy(rem, ++p_n);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		if (!(*line))
			return (-1);
	}
	return (1);
}

int	gnl(int fd, char **line)
{
	static char	remainder[20 + 1];
	char		buffer[20 + 1];
	char		*tmp;

	if (fd < 0 || !line || \
		read(fd, buffer, 0) != 0)
	{
		if (line)
			*line = ((void *)0);
		return (-1);
	}
	tmp = gnl_reminder(remainder, line);
	if (!(*line))
		return (-1);
	if (tmp)
		return (1);
	return (gnl_read(remainder, buffer, line, fd));
}
