/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:08:17 by gperez            #+#    #+#             */
/*   Updated: 2019/11/14 12:44:02 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_db(char const *str, int *cmpt, double out, double signe)
{
	double	db;
	int		i_db;

	(*cmpt)++;
	db = 0;
	i_db = 0;
	while (str[*cmpt + i_db] != '\0')
	{
		if (str[*cmpt + i_db] < '0' || str[*cmpt + i_db] > '9')
		{
			if (signe == -1)
				return (out - db);
			else
				return (out + db);
		}
		db += (str[*cmpt + i_db] - '0') / ft_pow(10, i_db + 1);
		i_db++;
	}
	if (signe == -1)
		return (out - db);
	else
		return (out + db);
}

static double	ft_atoi_s(char const *str, int *cmpt, int signe)
{
	double	resultat;

	resultat = 0.0;
	while (str[*cmpt] != '\0')
	{
		if (str[*cmpt] < '0' || str[*cmpt] > '9')
		{
			if (resultat > -PREC && resultat < PREC)
				return (resultat * signe);
			return (resultat * -signe);
		}
		resultat -= (str[*cmpt] - '0');
		if (str[(*cmpt) + 1] >= '0' && str[(*cmpt) + 1] <= '9')
			resultat *= 10.0;
		(*cmpt)++;
	}
	if (resultat > -PREC && resultat < PREC)
		return (resultat * signe);
	return (resultat * -signe);
}

double			ft_atoi_db(char const *str)
{
	int		cmpt;
	double	signe;
	double	out;

	out = 0.0;
	cmpt = 0;
	signe = 1.0;
	while (str && (str[cmpt] == ' ' || str[cmpt] == '\r' || str[cmpt] == '\v' ||
	str[cmpt] == '\f' || str[cmpt] == '\t' || str[cmpt] == '\n'))
		cmpt++;
	if (str && ((str[cmpt] >= '0' && str[cmpt] <= '9') || str[cmpt] == '+'
	|| str[cmpt] == '-'))
	{
		if (str[cmpt] == '+' || str[cmpt] == '-')
		{
			if (str[cmpt] == '-')
				signe = -1.0;
			cmpt++;
		}
		out = ft_atoi_s(str, &cmpt, signe);
		if (str[cmpt] == '.')
			out = ft_db(str, &cmpt, out, signe);
	}
	return (out);
}
