/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:26:46 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 19:30:09 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (s == ((void *)0) || !f)
		return ((void *)0);
	len = ft_strlen(s);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return ((void *)0);
	i = -1;
	while (++i < len)
		*(tmp + i) = (*f)(i, *(s + i));
	*(tmp + i) = '\0';
	return (tmp);
}
