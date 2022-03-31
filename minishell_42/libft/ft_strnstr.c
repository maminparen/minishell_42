/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:39:12 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 18:35:02 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (*haystack)
	{
		j = 0;
		while (*(needle + j) && i + j < len)
		{
			if (*(needle + j) == *(haystack + j))
				j++;
			else
			{
				j = 0;
				break ;
			}
		}
		if (*(needle + j) == '\0')
			return ((char *)haystack);
		i++;
		haystack++;
	}
	return ((void *)0);
}
