/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:07:40 by hzona             #+#    #+#             */
/*   Updated: 2021/11/13 11:48:29 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char		*str;
	size_t				i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_memset(void *memptr, int val, size_t num)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)memptr;
	i = 0;
	while (i < num)
	{
		str[i] = (char)val;
		i++;
	}
	return (memptr);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (!dest && !src)
		return (dest);
	i = 0;
	if (dest > src)
	{
		while (n > 0)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}
