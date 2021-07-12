/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_to_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:50:15 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:54:25 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*calcul(unsigned long long nb, int *cmpt, char const *base,
	int fill)
{
	int		len;
	char	*itoa_b;

	if (fill && !(itoa_b = ft_memalloc(sizeof(char) * *cmpt + 1)))
		return (NULL);
	len = ft_strlen(base);
	while (nb > 0)
	{
		if (fill)
		{
			(*cmpt)--;
			itoa_b[*cmpt] = base[nb % len];
		}
		else
			(*cmpt)++;
		nb /= len;
	}
	return (itoa_b);
}

char		*ft_decimal_to_base(unsigned long long nb, char const *base)
{
	int		len_out;
	char	*itoa_b;

	if (!ft_strcmp(base, DEC))
		return (ft_itoaul(nb));
	if (!base)
		return (NULL);
	len_out = 0;
	if (nb == 0)
	{
		if (!(itoa_b = ft_memalloc(sizeof(char) + 1)))
			return (NULL);
		itoa_b[0] = base[0];
		return (itoa_b);
	}
	calcul(nb, &len_out, base, 0);
	return (calcul(nb, &len_out, base, 1));
}
