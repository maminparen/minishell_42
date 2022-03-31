/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:19:41 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/04 22:44:26 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	size_t			i;

	if (src == dst || n == 0)
		return (dst);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	i = -1;
	while (++i < n)
		*(tmp_dst + i) = *(tmp_src + i);
	return (dst);
}
