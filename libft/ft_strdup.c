/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:01:36 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 18:27:00 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(s1) + 1;
	tmp = (char *)malloc(len * sizeof(char));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, s1, len);
	return (tmp);
}
