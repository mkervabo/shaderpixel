/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 20:03:26 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:00:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cmpt;

	cmpt = 0;
	if (src)
	{
		while (((char *)src)[cmpt] && cmpt < n)
		{
			((char *)dst)[cmpt] = ((char *)src)[cmpt];
			cmpt++;
		}
	}
	return (dst);
}
