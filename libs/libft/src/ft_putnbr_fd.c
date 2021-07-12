/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:21:18 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:06:16 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		nb_clone;
	int		div_dix;
	char	nb_conv;

	if (n < 0)
		ft_putchar_fd('-', fd);
	div_dix = 1;
	if (n > 0)
		n *= -1;
	nb_clone = n;
	while ((nb_clone / 10) < 0)
	{
		nb_clone /= 10;
		div_dix *= 10;
	}
	while (n > 0 || div_dix > 0)
	{
		nb_clone = n;
		nb_clone /= div_dix;
		nb_conv = -nb_clone + '0';
		ft_putchar_fd(nb_conv, fd);
		n %= div_dix;
		div_dix /= 10;
	}
}
