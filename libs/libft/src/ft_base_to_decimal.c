/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_to_decimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:53:35 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:53:38 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_base_to_decimal(char *nb, char const *base)
{
	int			len;
	int			dec;
	long long	out;
	int			cmpt;
	int			i;

	dec = ft_strlen(nb) - 1;
	len = ft_strlen(base);
	out = 0;
	cmpt = 0;
	while (nb[cmpt])
	{
		i = ft_strindexof(base, ft_toupper(nb[cmpt]));
		if (i == -1)
			return (-1);
		out += ft_pow(len, dec) * i;
		dec--;
		cmpt++;
	}
	return (out);
}
