/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:06:47 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:10:53 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	fill_error_syntex(char qqq, char **error_syntax)
{
	char	*tmp;

	*error_syntax = ft_strdup("syntax error near unexpected token '");
	if (!*error_syntax)
		ft_error_malloc("Error malloc: pars_check _line.c - error_syntax");
	tmp = *error_syntax;
	if (qqq == '|')
		*error_syntax = ft_strjoin(*error_syntax, "|'");
	else if (qqq == '>')
		*error_syntax = ft_strjoin(*error_syntax, ">'");
	else if (qqq == '<')
		*error_syntax = ft_strjoin(*error_syntax, "<'");
	if (!*error_syntax)
		ft_error_malloc("Error malloc: pars_check _line.c - error_syntax");
	free(tmp);
	return (1);
}

static int	check_pipe(char *line, int i, char qqq, char **error_syntax)
{
	int	j;

	j = i + 1;
	while (*(line + j) && *(line + j) != '|' && \
			(*(line + j) == ' ' || *(line + j) == '\t' || \
			*(line + j) == '<' || *(line + j) == '>' ))
		j++;
	if (*(line + j) == '\0' || *(line + j) == qqq)
		return (fill_error_syntex(qqq, error_syntax));
	j = i - 1;
	while (j >= 0 && *(line + j) != '|' && \
			(*(line + j) == ' ' || *(line + j) == '\t' || \
			*(line + j) == '<' || *(line + j) == '>'))
		j--;
	if (j < 0 || *(line + j) == qqq)
		return (fill_error_syntex(qqq, error_syntax));
	return (0);
}

static int	check_redir(char *line, int i, char qqq, char **error_syntax)
{
	int	j;

	j = i + 1;
	if (*(line + j) == qqq)
	{
		if (*(line + j + 1) == qqq)
			return (fill_error_syntex(qqq, error_syntax));
		else
			j++;
	}
	while (*(line + j) && *(line + j) != '|' && \
			(*(line + j) == ' ' || *(line + j) == '\t'))
		j++;
	if (*(line + j) == '\0' || *(line + j) == '|' || \
		*(line + j) == '>' || *(line + j) == '<')
		return (fill_error_syntex(qqq, error_syntax));
	return (0);
}

int	pars_check_line(char *line, char **error_syntax)
{
	int		i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) == '\'')
			pass_quotes(line, &i, '\'');
		else if (*(line + i) == '\"')
			pass_quotes(line, &i, '\"');
		else if (*(line + i) == '\"')
			pass_quotes(line, &i, ' ');
		if (*(line + i) == '|' && check_pipe(line, i, '|', error_syntax))
			return (1);
		else if (*(line + i) == '<' && check_redir(line, i, '<', error_syntax))
			return (1);
		else if (*(line + i) == '>' && check_redir(line, i, '>', error_syntax))
			return (1);
		else
			i++;
	}
	return (0);
}
