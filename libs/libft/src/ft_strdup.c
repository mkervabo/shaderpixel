/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:15:26 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 13:03:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	int		len;
	char	*dst;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!(dst = ft_memalloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strcpy(dst, s1);
	return (dst);
}
