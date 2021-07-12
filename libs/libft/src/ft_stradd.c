/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:23:47 by gperez            #+#    #+#             */
/*   Updated: 2019/12/04 16:59:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_out(char *str, char *add)
{
	int		strlen;
	int		addlen;
	char	*out;

	strlen = ft_strlen(str);
	addlen = ft_strlen(add);
	if (!(out = ft_memalloc(strlen + addlen + 1)))
		return (NULL);
	return (out);
}

char		*ft_stradd(char *str, char *add)
{
	char	*out;
	int		i_str;
	int		i_add;

	if (!str && add)
		return (ft_strdup(add));
	else if (str && !add)
		return (ft_strdup(str));
	else if (!str && !add)
		return (NULL);
	i_str = 0;
	i_add = 0;
	if (!(out = allocate_out(str, add)))
		return (NULL);
	while (str[i_str])
	{
		out[i_str] = str[i_str];
		i_str++;
	}
	while (add[i_add])
		out[i_str++] = add[i_add++];
	out[i_str] = '\0';
	return (out);
}
