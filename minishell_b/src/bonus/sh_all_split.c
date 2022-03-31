/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_all_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:42:33 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:54:31 by cdarrell         ###   ########.fr       */
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
		else if (*(s + i) == '(')
			pass_skobka(s, &i, i, 1);
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
		else if (*(s + i) == '(')
			pass_skobka(s, &i, i, 1);
		else if ((*(s + i) == '&' && *(s + i + 1) == '&') || \
				(*(s + i) == '|' && *(s + i + 1) == '|'))
			break ;
		else
			i++;
	}
	return (i + 1);
}

static char	**make_array(int words, char *line, t_sh_all *sh_all)
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
	sh_all->connect = (int *)malloc((words + 2) * sizeof(int));
	sh_all->connect[0] = 1;
	return (tmp);
}

int	*sh_all_check_skobka(char **str, int words, int s, int i)
{
	int	*skobka;
	int	j;
	int	flag;

	skobka = (int *)malloc((words + 2) * sizeof(int));
	while (++i < words)
	{
		flag = 0;
		norminette_j(str, i, &j);
		if (str[i][j] == '(')
			flag = 1;
		if (flag == 1)
		{
			s = j;
			j = ft_strlen(str[i]) - 1;
			while (j > 0 && (str[i][j] == ' ' || str[i][j] == '\t'))
				j--;
			if (str[i][j] == ')')
				flag = 2;
			norminett_flag_2(flag, &skobka[i], &str[i][j], &str[i][s]);
		}
		else
			skobka[i] = 0;
	}
	return (skobka);
}

char	**sh_all_split(char *s, t_sh_all *sh_all, int i, int words)
{
	char	**tmp;	
	int		len_word;

	if (s == ((void *)0))
		return ((void *)0);
	words = ft_split_words(s);
	tmp = make_array(words, s, sh_all);
	while (++i < words && words != 1)
	{
		len_word = ft_split_word_len(s);
		tmp[i] = (char *)malloc(len_word * sizeof(char));
		if (!tmp[i])
			ft_error_malloc("Error malloc: pars_list_cmd_split.c - tmp[i]");
		ft_strlcpy(tmp[i], s, len_word);
		s += len_word;
		if (*s == '|')
			sh_all->connect[i + 1] = 2;
		else
			sh_all->connect[i + 1] = 1;
		if (*s == '&' || *s == '|')
			s++;
	}
	sh_all->skobka = sh_all_check_skobka(tmp, words, 0, -1);
	return (tmp);
}
