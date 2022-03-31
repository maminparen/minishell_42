/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:02:16 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/04 22:42:01 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp_s;

	tmp_s = (char *)s;
	while (*tmp_s)
		tmp_s++;
	while (tmp_s >= s)
	{
		if (*tmp_s == c)
			return (tmp_s);
		tmp_s--;
	}
	return ((void *)0);
}
