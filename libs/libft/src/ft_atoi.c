/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:08:17 by gperez            #+#    #+#             */
/*   Updated: 2019/09/27 18:40:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	ft_atoi_s(char const *str, int cmpt, int signe)
{
	long	resultat;

	resultat = 0;
	while (str && str[cmpt] != '\0')
	{
		if (str[cmpt] < '0' || str[cmpt] > '9')
			return (resultat * -signe);
		resultat -= (str[cmpt] - '0');
		if ((resultat <= -922337203685477580 && str[cmpt + 1] >= '8' &&
			str[cmpt + 1] <= '9' && signe == -1) || (resultat <=
				-922337203685477581 && signe == -1 &&
				str[cmpt + 1] >= '0' && str[cmpt + 1] <= '9'))
			return (0);
		if ((resultat <= -922337203685477580 && str[cmpt + 1] >= '8' &&
			str[cmpt + 1] <= '9' && signe == 1) || (resultat <=
				-922337203685477581 && signe == 1 &&
				str[cmpt + 1] >= '0' && str[cmpt + 1] <= '9'))
			return (-1);
		if (str[cmpt + 1] >= '0' && str[cmpt + 1] <= '9')
			resultat *= 10;
		cmpt++;
	}
	return ((int)resultat * -signe);
}

long long int			ft_atoi(char const *str)
{
	int		cmpt;
	int		signe;

	cmpt = 0;
	signe = 1;
	while (str && (str[cmpt] == ' ' || str[cmpt] == '\r' || str[cmpt] == '\v' ||
	str[cmpt] == '\f' || str[cmpt] == '\t' || str[cmpt] == '\n'))
		cmpt++;
	if (str && ((str[cmpt] >= '0' && str[cmpt] <= '9') || str[cmpt] == '+'
	|| str[cmpt] == '-'))
	{
		if (str[cmpt] == '+' || str[cmpt] == '-')
		{
			if (str[cmpt] == '-')
				signe = -1;
			cmpt++;
		}
		return (ft_atoi_s(str, cmpt, signe));
	}
	else
		return (0);
}
