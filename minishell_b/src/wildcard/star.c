/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:37:50 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 16:54:45 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"
#include "../../include/wildcard.h"

int	find_start(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] == ' ' || str[i] == ')' || str[i] == '(')
			return (i + 1);
		i--;
	}
	return (0);
}

int	find_end(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == ')' || str[i] == '(')
			return (i);
		i++;
	}
	return (i);
}

char	*replace_star(char *str, int i)
{
	int			start;
	int			end;
	static char	*star;
	static char	*replace;

	start = find_start(str, i);
	end = find_end(str, i);
	star = ft_substr(str, start, end - start);
	if (!star)
		return (str);
	replace = parse_star(star, array_wood(), NULL, NULL);
	if (!replace)
		return (str);
	replace = ft_strjoin_free(replace, str + end);
	str[start] = '\0';
	str = ft_strjoin_free(str, replace);
	free(replace);
	free(star);
	return (str);
}

char	*pars_list_star(char *line)
{
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (*(line + i))
	{
		if (*(line + i) == '\'')
			pass_quotes(line, &i, '\'');
		else if (*(line + i) == '\"')
			pass_quotes(line, &i, '\"');
		else if (*(line + i) == '*')
		{
			line = replace_star(line, i);
			i++;
			j = i;
		}
		else
			i++;
	}
	return (line);
}
