/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:38:51 by gperez            #+#    #+#             */
/*   Updated: 2019/11/14 14:19:52 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_pow(double n, int p)
{
	double	resultat;

	resultat = 1;
	if (p <= -1)
	{
		while (p <= -1)
		{
			resultat /= n;
			p++;
		}
		return (resultat);
	}
	else if (p >= 1)
	{
		while (p >= 1)
		{
			resultat *= n;
			p--;
		}
		return (resultat);
	}
	return (1);
}

long double	ft_powld(long double n, int p)
{
	long double	resultat;

	resultat = 1;
	if (p <= -1)
	{
		while (p <= -1)
		{
			resultat /= n;
			p++;
		}
		return (resultat);
	}
	else if (p >= 1)
	{
		while (p >= 1)
		{
			resultat *= n;
			p--;
		}
		return (resultat);
	}
	return (1);
}
