/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:05:29 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 13:06:19 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(void **nb, char const *base_in, char const *base_out)
{
	long long	nb_int;

	if (ft_strcmp(base_in, DEC))
	{
		if ((nb_int = ft_base_to_decimal((char*)nb, base_in)) == -1)
			return (NULL);
		return (ft_decimal_to_base((unsigned long long)nb_int, base_out));
	}
	else
		return (ft_decimal_to_base((unsigned long long)nb, base_out));
}
