/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 06:34:15 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:10:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_toupper(char *s)
{
	int		cmpt;
	char	*s2;

	if (s)
	{
		s2 = ft_strdup(s);
		cmpt = 0;
		while (s[cmpt])
		{
			s2[cmpt] = ft_toupper(s[cmpt]);
			cmpt++;
		}
		return (s2);
	}
	return (NULL);
}
