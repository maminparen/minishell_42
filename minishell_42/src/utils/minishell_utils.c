/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:10:04 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:38:16 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_return(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	ft_error_malloc(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;
	size_t			i;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = -1;
	while (*(tmp_s1 + ++i))
		if (*(tmp_s1 + i) != *(tmp_s2 + i))
			break ;
	if (*(tmp_s1 + i) == '\0' && *(tmp_s2 + i) == '\0')
		return (0);
	return (*(tmp_s1 + i) - *(tmp_s2 + i));
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	if (dest == ((void *)0) || src == ((void *)0))
		return (0);
	i = 0;
	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

void	ft_free_split(char	**tmp)
{
	int	i;

	if (!tmp)
		return ;
	i = -1;
	while (tmp[++i])
		free (tmp[i]);
	free(tmp);
}
