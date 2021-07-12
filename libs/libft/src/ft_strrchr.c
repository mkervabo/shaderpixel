/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:44:17 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:32:33 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int		cmpt;

	if (s)
	{
		cmpt = ft_strlen(s);
		while (cmpt >= 0)
		{
			if (s[cmpt] == c)
				return ((char *)s + (cmpt));
			cmpt--;
		}
	}
	return (NULL);
}
