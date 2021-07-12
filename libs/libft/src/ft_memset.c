/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:19:26 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:04:27 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	cmpt;

	cmpt = 0;
	if (b)
	{
		while (((char *)b)[cmpt] && cmpt < len)
		{
			((char *)b)[cmpt] = (char)c;
			cmpt++;
		}
	}
	return (b);
}
