/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:31:55 by gperez            #+#    #+#             */
/*   Updated: 2020/01/03 02:46:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	int		cmpt;

	cmpt = 0;
	if (!s)
		return (NULL);
	while (s[cmpt])
	{
		if (s[cmpt] == c)
			return ((char *)s + cmpt);
		cmpt++;
	}
	if (c == '\0')
		return ((char *)s + cmpt);
	return (NULL);
}
