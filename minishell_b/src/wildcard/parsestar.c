/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsestar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:37:50 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 17:52:15 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"
#include "../../include/wildcard.h"

int	array_wood(void)
{
	struct dirent	*ptr_dirent;
	DIR				*ptr_dir;
	int				i;

	i = 0;
	ptr_dir = opendir("./");
	if (ptr_dir == NULL)
		return (0);
	ptr_dirent = readdir(ptr_dir);
	while (ptr_dirent)
	{
		ptr_dirent = readdir(ptr_dir);
		i++;
	}
	closedir(ptr_dir);
	return (i);
}

char	**new_array_star(int len)
{
	struct dirent	*ptr_dirent;
	DIR				*ptr_dir;
	char			**res;
	int				i;

	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	ptr_dir = opendir("./");
	if (ptr_dir == NULL)
		return (NULL);
	ptr_dirent = readdir(ptr_dir);
	while (ptr_dirent)
	{
		if (ptr_dirent->d_name[0] != '.')
		{
			res[i] = ft_strdup2(ptr_dirent->d_name);
			i++;
		}
		ptr_dirent = readdir(ptr_dir);
	}
	closedir(ptr_dir);
	res[i] = NULL;
	return (res);
}

void	free_star(char *pre, char *su, char **arr)
{
	int	i;

	i = 0;
	if (su)
		free(su);
	if (pre)
		free(pre);
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

char	*parse_star(char *str, int i, char *res, char **arr)
{
	char	*su;
	char	*pre;

	arr = new_array_star(i);
	if (!str || i == 0 || !arr)
		return (NULL);
	pre = pref(str);
	su = suf(str);
	res = ft_strdup("");
	i = 0;
	while (arr[i])
	{
		if (!pre && !su)
			res = ft_strjoin_free(res, arr[i]);
		else if (pre && !ft_strncmp(pre, arr[i] + 1, ft_strlen(pre)) && !su)
			res = ft_strjoin_free(res, arr[i]);
		else if (su && !pre && check_su(arr[i], su))
			res = ft_strjoin_free(res, arr[i]);
		else if (check_su(arr[i], su)
			&& !ft_strncmp(pre, arr[i] + 1, ft_strlen(pre)))
			res = ft_strjoin_free(res, arr[i]);
		i++;
	}
	free_star(pre, su, arr);
	return (res);
}
