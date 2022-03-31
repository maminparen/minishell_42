/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:18:00 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/05 19:24:49 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (1)
	{
		len++;
		n /= 10;
		if (n == 0)
			break ;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	char		*tmp;
	int			len;

	nbr = n;
	len = ft_itoa_len(n);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return ((void *)0);
	*(tmp + len) = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		*tmp = '-';
	}
	while (1)
	{
		*(tmp + --len) = nbr % 10 + '0';
		nbr /= 10;
		if (nbr == 0)
			break ;
	}
	return (tmp);
}
