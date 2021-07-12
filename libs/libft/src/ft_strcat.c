/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 09:07:27 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:12:05 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	size_t		cmpt_s1;
	size_t		cmpt_s2;
	size_t		i;

	cmpt_s1 = 0;
	cmpt_s2 = 0;
	i = ft_strlen(s1);
	while (cmpt_s1 < i)
		cmpt_s1++;
	while (s2[cmpt_s2])
	{
		s1[cmpt_s1] = s2[cmpt_s2];
		cmpt_s1++;
		cmpt_s2++;
	}
	s1[cmpt_s1] = '\0';
	return (s1);
}
