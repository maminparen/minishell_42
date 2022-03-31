/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_cmd_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:42:33 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:00 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_split_words(char *s)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == ' ' || *(s + i) == '\t')
			i++;
		else
		{
			while (*(s + i) && *(s + i) != ' ' && *(s + i) != '\t')
			{
				if (*(s + i) == '\'')
					pass_quotes(s, &i, '\'');
				else if (*(s + i) == '\"')
					pass_quotes(s, &i, '\"');
				else
					i++;
			}
			words++;
		}
	}
	return (words);
}

static int	ft_split_word_len(char *s)
{
	int	j;

	j = 0;
	while (*(s + j) && *(s + j) != ' ' && *(s + j) != '\t')
	{
		if (*(s + j) == '\'')
			pass_quotes(s, &j, '\'');
		else if (*(s + j) == '\"')
			pass_quotes(s, &j, '\"');
		else
			j++;
	}
	return (j + 1);
}

char	**make_array(int words)
{
	char	**tmp;

	if (words == 0)
		tmp = (char **)malloc((words + 2) * sizeof(char *));
	else
		tmp = (char **)malloc((words + 1) * sizeof(char *));
	if (!tmp)
		ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp");
	if (words == 0)
	{
		tmp[0] = strdup("\0");
		if (!tmp[0])
			ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp[i]");
		tmp[1] = ((void *)0);
	}
	else
		tmp[words] = ((void *)0);
	return (tmp);
}

char	**pars_list_cmd_split(char *s)
{
	char	**tmp;	
	int		words;
	int		len_word;
	int		i;

	if (s == ((void *)0))
		return ((void *)0);
	words = ft_split_words(s);
	tmp = make_array(words);
	i = -1;
	while (++i < words && words != 0)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		len_word = ft_split_word_len(s);
		tmp[i] = (char *)malloc(len_word * sizeof(char));
		if (!tmp[i])
			ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp[i]");
		ft_strlcpy(tmp[i], s, len_word);
		s += len_word;
	}	
	return (tmp);
}
