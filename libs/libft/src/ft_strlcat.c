/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:05:53 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:29:25 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	int		cmpt_s1;
	int		cmpt_s2;
	int		len_dst;

	cmpt_s1 = 0;
	cmpt_s2 = 0;
	len_dst = ft_strlen(dst);
	while (dst[cmpt_s1] && cmpt_s1 < (int)size)
		cmpt_s1++;
	if (dst[cmpt_s1] != '\0')
		return (size + ft_strlen(src));
	while (src[cmpt_s2] && cmpt_s1 < (int)size - 1)
	{
		dst[cmpt_s1] = src[cmpt_s2];
		cmpt_s1++;
		cmpt_s2++;
	}
	dst[cmpt_s1] = '\0';
	return (len_dst + ft_strlen(src));
}
