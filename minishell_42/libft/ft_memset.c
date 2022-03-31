/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:00:54 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/04 22:43:32 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_s;
	unsigned char	tmp_c;
	size_t			i;

	tmp_s = (unsigned char *)b;
	tmp_c = (unsigned char)c;
	i = 0;
	while (i < len)
		*(tmp_s + i++) = tmp_c;
	return (b);
}
