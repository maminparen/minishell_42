/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcharutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:17:05 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 15:58:54 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"

int	ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (1);
}

void	quiet_signal(int sig)
{
	write(1, "Quit: ", 6);
	write(1, ft_itoa(sig), 1);
	write(1, "\n", 1);
}
