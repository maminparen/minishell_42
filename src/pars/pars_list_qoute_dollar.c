/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_qoute_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:48:47 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:09 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_value_dollar(char *flag, t_list_2val *env)
{
	char		*value;
	t_list_2val	*tmp;

	value = ((void *)0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(flag, tmp->flag) && \
			(tmp->visible == 1 || !ft_strcmp(tmp->flag, "?")))
		{
			value = ft_strdup(tmp->value);
			if (!value)
				ft_error_malloc("Error malloc: \
								pars_list_qoute_dollar.c - value");
			break ;
		}
		tmp = tmp->next;
	}
	if (value == ((void *)0))
	{
		value = ft_strdup("");
		if (!value)
			ft_error_malloc("Error malloc: pars_list_qoute_dollar.c - value");
	}
	return (value);
}

static char	*ft_three_strjoin(char *tmp_pref, \
								char *value, char *tmp_suff, int *i)
{
	char	*str;

	if (!tmp_pref || !tmp_suff)
		ft_error_malloc("Error malloc: pars_env.c - tmp_pref || tmp_suff");
	str = ft_strjoin(tmp_pref, value);
	if (!str)
		ft_error_malloc("Error malloc: pars_env.c - str");
	free(tmp_pref);
	free(value);
	*i = ft_strlen(str);
	tmp_pref = str;
	str = ft_strjoin(str, tmp_suff);
	if (!str)
		ft_error_malloc("Error malloc: pars_env.c - str");
	free(tmp_pref);
	free(tmp_suff);
	return (str);
}

char	*pars_list_open_dollars(char *str, int *i, t_list_2val *env)
{
	int		start;
	char	*flag;
	char	*value;
	char	*tmp_pref;
	char	*tmp_suff;

	start = *i;
	(*i)++;
	while (*(str + *i) && (*(str + *i) == '_' || ft_isalnum(*(str + *i))))
		(*i)++;
	if (*(str + *i) == '?')
		(*i)++;
	if (*i == start + 1)
		return (str);
	flag = ft_substr(str, start + 1, *i - start - 1);
	if (!flag)
		ft_error_malloc("Error malloc: pars_env.c - flag");
	value = find_value_dollar(flag, env);
	free(flag);
	tmp_pref = ft_substr(str, 0, start);
	tmp_suff = ft_substr(str, *i, ft_strlen(str) - *i);
	free(str);
	str = ft_three_strjoin(tmp_pref, value, tmp_suff, i);
	return (str);
}
