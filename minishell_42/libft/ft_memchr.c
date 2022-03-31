/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:29:38 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/04 22:45:12 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	tmp_c;
	unsigned char	*tmp_s;
	size_t			i;

	tmp_c = (unsigned char)c;
	tmp_s = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if (tmp_c == *tmp_s)
			return ((void *)tmp_s);
		tmp_s++;
	}
	return ((void *)0);
}
