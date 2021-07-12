/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:23:26 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:59:16 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbrl(long long int n)
{
	long long int	nb_clone;
	long long int	div_dix;
	char			nb_conv;

	if (n < 0)
		ft_putchar('-');
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
		ft_putchar(nb_conv);
		n %= div_dix;
		div_dix /= 10;
	}
}
