/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:03:58 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:29:32 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		cmpt;
	char	*dst;

	if (s)
	{
		cmpt = 0;
		if ((dst = ft_strdup(s)) == NULL)
			return (NULL);
		while (s[cmpt])
		{
			dst[cmpt] = (*f)(s[cmpt]);
			cmpt++;
		}
		return (dst);
	}
	return (NULL);
}
