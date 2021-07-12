/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:17:58 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:31:54 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i + j])
	{
		while (haystack[i + j] && haystack[i + j] == needle[j] && needle[j] &&
				i + j < (int)len)
			j++;
		if (needle[j] == '\0')
			return ((char*)haystack + i);
		if (i + j == (int)len - 1)
			return (NULL);
		j = 0;
		i++;
	}
	return (NULL);
}
