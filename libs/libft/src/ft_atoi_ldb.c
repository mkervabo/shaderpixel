/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ldb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:51:40 by gperez            #+#    #+#             */
/*   Updated: 2019/11/14 12:26:19 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_db(char const *str, int *cmpt, long double out,
	long double signe)
{
	long double	db;
	int			i_db;

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
		db += (str[*cmpt + i_db] - '0') / ft_powld(10.0L, i_db + 1);
		i_db++;
	}
	if (signe == -1)
		return (out - db);
	else
		return (out + db);
}

static long double	ft_atoi_s(char const *str, int *cmpt, long double signe)
{
	long double	resultat;

	resultat = 0.0L;
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
			resultat *= 10.0L;
		(*cmpt)++;
	}
	if (resultat > -PREC && resultat < PREC)
		return (resultat * signe);
	return (resultat * -signe);
}

long double			ft_atoi_ldb(char const *str)
{
	int			cmpt;
	long double	signe;
	long double	out;

	out = 0.0L;
	cmpt = 0;
	signe = 1.0L;
	while (str && (str[cmpt] == ' ' || str[cmpt] == '\r' || str[cmpt] == '\v' ||
	str[cmpt] == '\f' || str[cmpt] == '\t' || str[cmpt] == '\n'))
		cmpt++;
	if (str && ((str[cmpt] >= '0' && str[cmpt] <= '9') || str[cmpt] == '+'
	|| str[cmpt] == '-'))
	{
		if (str[cmpt] == '+' || str[cmpt] == '-')
		{
			if (str[cmpt] == '-')
				signe = -1.0L;
			cmpt++;
		}
		out = ft_atoi_s(str, &cmpt, signe);
		if (str[cmpt] == '.')
			out = ft_db(str, &cmpt, out, signe);
	}
	return (out);
}
