/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:37:50 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 22:05:14 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"
#include "../../include/wildcard.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		k;

	if (!s1 || !s2)
		return ((void *)0);
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return ((void *)0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2[k])
	{
		res[i] = s2[k];
		i++;
		k++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

char	*ft_strdup2(char *str)
{
	char	*res;
	int		len;
	int		i;

	i = 1;
	len = ft_strlen(str);
	res = (char *) malloc(len + 4);
	if (res == (void *)0)
		return ((void *)0);
	res[0] = 39;
	while (str[i - 1])
	{
		res[i] = str[i - 1];
		i++;
	}
	res[i] = 39;
	res[i + 1] = ' ';
	res[i + 2] = '\0';
	return (res);
}

char	*pref(char *str)
{
	char	*res;
	int		i;

	if (str && str[0] == '*')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '*')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*suf(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = ft_strlen(str) - 1;
	if (str && str[i] == '*')
		return (NULL);
	j = 0;
	while (i >= 0 && str[i] != '*')
	{
		j++;
		i--;
	}
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[++i])
	{
		res[j] = str[i];
		j++;
	}
	res[i] = '\0';
	return (res);
}

int	check_su(char *str, char *su)
{
	int	i;
	int	j;

	if (!str || !su)
		return (0);
	i = ft_strlen(str) - 3;
	j = ft_strlen(su) - 1;
	while (i >= 0 && j >= 0)
	{
		if (str[i] != su[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}
