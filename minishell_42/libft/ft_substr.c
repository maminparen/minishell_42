/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:48:50 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 18:40:12 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s == ((void *)0))
		return ((void *)0);
	if (start >= ft_strlen(s))
		len = 0;
	else
		s += start;
	len++;
	tmp = (char *)malloc(len * sizeof(char));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, s, len);
	return (tmp);
}
