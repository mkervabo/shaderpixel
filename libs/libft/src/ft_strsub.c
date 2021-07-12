/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:57:55 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:34:59 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		cmpt;
	char	*ret;

	if (s)
	{
		if (start < (unsigned int)ft_strlen(s))
		{
			cmpt = 0;
			if (len <= ft_strlen(s) - start)
			{
				if (!(ret = (char*)ft_memalloc(sizeof(char) * len + 1)))
					return (NULL);
				while (s[start + cmpt] && (int)len > cmpt)
				{
					ret[cmpt] = s[start + cmpt];
					cmpt++;
				}
				ret[cmpt] = '\0';
				return (ret);
			}
		}
	}
	return (NULL);
}
