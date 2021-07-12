/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:13:54 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 13:04:05 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisdigit(char *str)
{
	int	i;
	int	digit;

	i = 0;
	digit = 1;
	if (!str)
		return (0);
	while (str[i] && digit)
	{
		digit = ft_isdigit(str[i]);
		i++;
	}
	return (digit);
}
