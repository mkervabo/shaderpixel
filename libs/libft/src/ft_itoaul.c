/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:17:01 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:56:24 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_sub(unsigned long n, unsigned long lng, char *resultat)
{
	int		cmpt;

	cmpt = 0;
	lng = ft_pow(10, lng - 1);
	while (lng > 0)
	{
		resultat[cmpt] = (n / lng) + '0';
		n %= lng;
		lng /= 10;
		cmpt++;
	}
	resultat[cmpt] = '\0';
	return (resultat);
}

char		*ft_itoaul(unsigned long n)
{
	char			*resultat;
	unsigned long	nb_clone;
	int				lng;

	lng = 0;
	if (n == 0)
		lng = 1;
	nb_clone = n;
	while (nb_clone > 0)
	{
		nb_clone /= 10;
		lng++;
	}
	if (!(resultat = (char *)ft_memalloc(sizeof(char) * lng + 1)))
		return (NULL);
	return (ft_itoa_sub(n, lng, resultat));
}
