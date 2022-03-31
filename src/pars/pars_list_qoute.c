/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_qoute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:57:26 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:14 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	open_quotes(char *str, int *i, char qqq)
{
	int	start;

	start = *i;
	(*i)++;
	while (*(str + *i) != qqq && *(str + *i) != '\0')
		(*i)++;
	if (*i == (int)ft_strlen(str))
		*i = start + 1;
	else
	{
		ft_strcpy(str + *i, str + *i + 1);
		(*i)--;
		ft_strcpy(str + start, str + start + 1);
		(*i)--;
	}
}

static char	*open_double_quotes(char *str, int *i, char qqq, t_list_2val *env)
{
	int	start;

	start = *i;
	(*i)++;
	while (*(str + *i) != qqq && *(str + *i) != '\0')
		(*i)++;
	if (*i == (int)ft_strlen(str))
		*i = start + 1;
	else
	{	
		*i = start;
		ft_strcpy(str + *i, str + *i + 1);
		if (*i > 0)
			(*i)--;
		while (*(str + *i) != qqq)
		{
			if (*(str + *i) == '$')
				str = pars_list_open_dollars(str, i, env);
			else
				(*i)++;
		}
		ft_strcpy(str + *i, str + *i + 1);
		(*i)--;
	}
	return (str);
}

void	pars_list_qoute_dollar_cmd(char **cmd, t_list_2val *env)
{
	int		i;
	int		j;

	j = 0;
	while (cmd[j])
	{
		i = 0;
		while (cmd[j][i])
		{
			if (cmd[j][i] == '\'')
				open_quotes(cmd[j], &i, '\'');
			else if (cmd[j][i] == '\"')
				cmd[j] = open_double_quotes(cmd[j], &i, '\"', env);
			else if (cmd[j][i] == '$')
				cmd[j] = pars_list_open_dollars(cmd[j], &i, env);
			else
				i++;
		}
		j++;
	}
}

char	*pars_list_qoute_dollar_fd(char *line, t_list_2val *env)
{
	int		i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) == '\'')
			open_quotes(line, &i, '\'');
		else if (*(line + i) == '\"')
			line = open_double_quotes(line, &i, '\"', env);
		else if (*(line + i) == '$')
			line = pars_list_open_dollars(line, &i, env);
		else
			i++;
	}		
	return (line);
}
