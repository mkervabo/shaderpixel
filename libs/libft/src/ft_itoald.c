/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoald.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:36:40 by gperez            #+#    #+#             */
/*   Updated: 2019/11/19 15:26:22 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_prec(long double n, int prec, char *res, long double s)
{
	int		i;
	int		numb;

	i = 0;
	while (i < (int)prec)
	{
		n = n * 10;
		numb = (int)(n + PREC * s) * s < PREC ? 0 : (int)(n + PREC * s) * s;
		numb = numb > 9 ? 9 : numb;
		res[i] = numb + '0';
		n = n - (numb * s);
		if (i == (int)(prec - 1))
		{
			n = n * 10;
			numb = (int)(n + PREC * s) * s < 0 ? 0 : (int)(n + PREC * s) * s;
			numb = numb > 9 ? 9 : (int)(n + PREC * s) * s;
			res[i] = numb >= 5 && numb <= 9 ? res[i] + 1 : res[i];
			if (res[i] > '9' || res[i] < '0')
				return (res[i] = '9');
		}
		i++;
	}
	return (0);
}

static char	*fill_neg(long double *n, long double lng, int prec, char *res)
{
	int		i;

	i = 0;
	res[i++] = '-';
	if (*n > -1.0L)
	{
		res[i++] = '0';
		lng--;
	}
	lng = ft_powld(10, lng - 1 - prec - 1);
	while (lng > 1.0L - PREC)
	{
		res[i++] = -(int)(*n / lng) + '0';
		*n = *n - (int)(*n / lng) * lng;
		lng /= 10.0L;
	}
	res[i++] = '.';
	return (res + i);
}

static char	*fill_pos(long double *n, long double lng, int prec, char *res)
{
	int	i;

	i = 0;
	if (*n < 1.0L)
	{
		res[i++] = '0';
		lng--;
	}
	lng = ft_powld(10, lng - prec - 1);
	while (lng > 1.0L - PREC)
	{
		res[i++] = (int)(*n / lng) + '0';
		*n = *n - (int)(*n / lng) * lng;
		lng /= 10.0L;
	}
	res[i++] = '.';
	return (res + i);
}

static void	calc_len(long double nb_clone, int prec, int *lng)
{
	if (nb_clone > -PREC && nb_clone < PREC)
		(*lng) = 1 + prec;
	else if (nb_clone > -PREC)
	{
		(*lng) = nb_clone > 1.0L - PREC ? 0 : 1;
		while (nb_clone > 1.0L - PREC)
		{
			nb_clone /= 10.0L;
			(*lng)++;
		}
		(*lng) += prec;
	}
	else
	{
		(*lng) = nb_clone < -1.0L + PREC ? 1 : 2;
		while (nb_clone < -1.0L + PREC)
		{
			nb_clone /= 10.0L;
			(*lng)++;
		}
		(*lng) += prec;
	}
}

char		*ft_itoald(long double nb, int prec)
{
	char			*result;
	int				lng;
	char			*res_dec;
	int				restart;
	long double		s;

	prec = prec < 0 ? 0 : prec;
	if (prec == 0 && !(nb < PREC && nb > -PREC))
		nb += 0.5L * (nb < PREC ? -1.0L : 1.0L);
	s = nb;
	calc_len(nb, prec, &lng);
	if (!(result = (char *)ft_memalloc(sizeof(char) * lng + 1 + sizeof('.'))))
		return (NULL);
	if (nb < PREC && !(nb > -PREC))
		res_dec = fill_neg(&nb, lng, prec, result);
	else
		res_dec = fill_pos(&nb, lng, prec, result);
	restart = fill_prec(nb, prec, res_dec, nb < PREC ? -1.0L : 1.0L);
	nb = s + ft_powld(10.0L, -(prec + 1)) * 4.9L * (s < PREC ? -1.0L : 1.0L);
	if (restart && (nb > s || nb < s))
	{
		ft_memdel((void**)&result);
		return (ft_itoald(nb, prec));
	}
	return (result);
}
