/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:15:42 by gperez            #+#    #+#             */
/*   Updated: 2019/11/19 15:26:06 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_prec(double n, int prec, char *res, double s)
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

static char	*fill_neg(double *n, double lng, int prec, char *res)
{
	int		i;

	i = 0;
	res[i++] = '-';
	if (*n > -1.0f)
	{
		res[i++] = '0';
		lng--;
	}
	lng = ft_pow(10, lng - 1 - prec - 1);
	while (lng > 1.0f - PREC)
	{
		res[i++] = -(int)(*n / lng) + '0';
		*n = *n - (int)(*n / lng) * lng;
		lng /= 10.0;
	}
	res[i++] = '.';
	return (res + i);
}

static char	*fill_pos(double *n, double lng, int prec, char *res)
{
	int	i;

	i = 0;
	if (*n < 1.0f)
	{
		res[i++] = '0';
		lng--;
	}
	lng = ft_pow(10, lng - prec - 1);
	while (lng > 1.0f - PREC)
	{
		res[i++] = (int)(*n / lng) + '0';
		*n = *n - (int)(*n / lng) * lng;
		lng /= 10.0;
	}
	res[i++] = '.';
	return (res + i);
}

static void	calc_len(double nb_clone, int prec, int *lng)
{
	if (nb_clone > -PREC && nb_clone < PREC)
		(*lng) = 1 + prec;
	else if (nb_clone > -PREC)
	{
		(*lng) = nb_clone > 1.0f - PREC ? 0 : 1;
		while (nb_clone > 1.0f - PREC)
		{
			nb_clone /= 10;
			(*lng)++;
		}
		(*lng) += prec;
	}
	else
	{
		(*lng) = nb_clone < -1.0f + PREC ? 1 : 2;
		while (nb_clone < -1.0f + PREC)
		{
			nb_clone /= 10;
			(*lng)++;
		}
		(*lng) += prec;
	}
}

char		*ft_itoad(double nb, int prec)
{
	char			*result;
	int				lng;
	char			*res_dec;
	int				restart;
	double			s_n;

	prec = prec < 0 ? 0 : prec;
	if (prec == 0 && !(nb < PREC && nb > -PREC))
		nb += 0.5 * (nb < PREC ? -1 : 1);
	s_n = nb;
	calc_len(nb, prec, &lng);
	if (!(result = (char *)ft_memalloc(sizeof(char) * lng + 1 + sizeof('.'))))
		return (NULL);
	if (nb < PREC && !(nb > -PREC))
		res_dec = fill_neg(&nb, lng, prec, result);
	else
		res_dec = fill_pos(&nb, lng, prec, result);
	restart = fill_prec(nb, prec, res_dec, nb < PREC ? -1.0 : 1.0);
	nb = s_n + ft_pow(10.0, -(prec + 1)) * 4.9 * (s_n < PREC ? -1.0 : 1.0);
	if (restart && (nb > s_n || nb < s_n))
	{
		ft_memdel((void**)&result);
		return (ft_itoad(nb, prec));
	}
	return (result);
}
