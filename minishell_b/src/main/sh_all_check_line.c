/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_all_check_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:06:47 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:59:57 by cdarrell         ###   ########.fr       */
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
		if (*(s + i) == '\'')
			pass_quotes(s, &i, '\'');
		else if (*(s + i) == '\"')
			pass_quotes(s, &i, '\"');
		else if ((*(s + i) == '&' && *(s + i + 1) == '&') || \
			(*(s + i) == '|' && *(s + i + 1) == '|'))
		{
			words++;
			i += 2;
		}
		else
			i++;
	}
	return (words + 1);
}

static int	ft_split_word_len(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '\'')
			pass_quotes(s, &i, '\'');
		else if (*(s + i) == '\"')
			pass_quotes(s, &i, '\"');
		else if ((*(s + i) == '&' && *(s + i + 1) == '&') || \
				(*(s + i) == '|' && *(s + i + 1) == '|'))
			break ;
		else
			i++;
	}
	return (i + 1);
}

static char	**make_array(int words, char *line)
{
	char	**tmp;

	if (words == 1)
		tmp = (char **)malloc((words + 2) * sizeof(char *));
	else
		tmp = (char **)malloc((words + 1) * sizeof(char *));
	if (!tmp)
		ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp");
	if (words == 1)
	{
		tmp[0] = strdup(line);
		if (!tmp[0])
			ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp[i]");
		tmp[1] = ((void *)0);
	}
	else
		tmp[words] = ((void *)0);
	return (tmp);
}

static char	**sh_all_split_check_easy(char *s)
{
	char	**tmp;	
	int		words;
	int		len_word;
	int		i;

	if (s == ((void *)0))
		return ((void *)0);
	words = ft_split_words(s);
	tmp = make_array(words, s);
	i = -1;
	while (++i < words && words != 1)
	{
		len_word = ft_split_word_len(s);
		tmp[i] = (char *)malloc(len_word * sizeof(char));
		if (!tmp[i])
			ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp[i]");
		ft_strlcpy(tmp[i], s, len_word);
		s += len_word;
		if (*s == '&' || *s == '|')
			s++;
	}
	return (tmp);
}

int	sh_all_check_line(char *line, char **error_syntax)
{
	char	**tmp;
	int		i;
	int		num_tmp;

	tmp = sh_all_split_check_easy(line);
	i = -1;
	num_tmp = 0;
	while (tmp[++i])
		num_tmp++;
	i = -1;
	while (tmp[++i])
	{
		if (pars_check_line(tmp[i], error_syntax) || \
							(num_tmp > 1 && tmp[i][0] == '\0'))
		{
			if (!*error_syntax)
				*error_syntax = strdup("syntax error near \
unexpected token '&&' or '||'");
			ft_free_split(tmp);
			return (1);
		}
	}
	ft_free_split(tmp);
	return (0);
}
