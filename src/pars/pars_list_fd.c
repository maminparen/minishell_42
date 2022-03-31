/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:00:46 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:06 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_value(char *line, int i, t_list_2val *env)
{
	int		start;
	int		j;
	char	*value;

	start = i;
	j = 0;
	while (*(line + i) && (*(line + i) == ' ' || *(line + i) == '\t'))
		i++;
	j = i;
	while (*(line + i) && *(line + i) != ' ' && *(line + i) != '\t')
		i++;
	value = ft_substr(line, j, i - j);
	if (!value)
		ft_error_malloc("Error malloc: pars_list_fd.c - value");
	if (ft_strchr(value, '$'))
		value = pars_list_qoute_dollar_fd(value, env);
	while (start < i)
		*(line + start++) = ' ';
	return (value);
}

static void	add_list_fd(t_list_2val **fd, char *line, int i, t_list_2val *env)
{
	char		*flag;
	char		*value;
	t_list_2val	*tmp;

	if (*(line + i) == '>' && *(line + i + 1) == '>')
		flag = ft_strdup(">>");
	else if (*(line + i) == '>')
		flag = ft_strdup(">");
	else if (*(line + i) == '<' && *(line + i + 1) == '<')
		flag = ft_strdup("<<");
	else
		flag = ft_strdup("<");
	if (!flag)
		ft_error_malloc("Error malloc: pars_list_fd.c - flag");
	while (*(line + i) == '>' || *(line + i) == '<')
		*(line + i++) = ' ';
	value = find_value(line, i, env);
	if (!value || !flag)
		ft_error_malloc("Error: malloc fd value");
	tmp = ft_lstnew_2val(flag, value);
	if (!tmp)
		ft_error_malloc("Error: malloc env list");
	ft_lstadd_back_2val(fd, tmp);
}

t_list_2val	*pars_list_fd(char *line, t_list_2val *env)
{
	int			i;
	t_list_2val	*fd;

	i = 0;
	fd = ((void *)0);
	while (*(line + i))
	{
		if (*(line + i) == '\'')
			pass_quotes(line, &i, '\'');
		else if (*(line + i) == '\"')
			pass_quotes(line, &i, '\"');
		else if (*(line + i) == '>' || *(line + i) == '<' )
			add_list_fd(&fd, line, i, env);
		else
			i++;
	}
	return (fd);
}
