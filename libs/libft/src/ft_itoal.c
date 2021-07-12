/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:30:53 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:55:28 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_sub(long long n, long long lng, int signe, char *resultat)
{
	int		cmpt;

	cmpt = 0;
	if (n == 0)
		resultat[cmpt++] = '0';
	else
	{
		if (signe < 0)
		{
			resultat[cmpt] = '-';
			cmpt++;
			lng--;
		}
		lng = ft_pow(10, lng - 1);
		while (lng > 0)
		{
			resultat[cmpt] = -(n / lng) + '0';
			n %= lng;
			lng /= 10;
			cmpt++;
		}
	}
	resultat[cmpt] = '\0';
	return (resultat);
}

char		*ft_itoal(long long n)
{
	char		*resultat;
	long long	nb_clone;
	int			lng;
	int			signe;

	signe = n > 0 ? 1 : -1;
	lng = 0;
	if (n == 0)
		lng = 1;
	if (signe == -1)
		lng++;
	else
		n *= -1;
	nb_clone = n;
	while (nb_clone < 0)
	{
		nb_clone /= 10;
		lng++;
	}
	if (!(resultat = (char *)ft_memalloc(sizeof(char) * lng + 1)))
		return (NULL);
	return (ft_itoa_sub(n, lng, signe, resultat));
}
