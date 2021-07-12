/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:00:51 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:28:10 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		cmpt_1;
	int		cmpt_2;
	char	*ret;

	if (s1 && s2)
	{
		cmpt_1 = 0;
		cmpt_2 = 0;
		if (!(ret = (char *)ft_memalloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2)) + 1)))
			return (NULL);
		while (s1[cmpt_1])
		{
			ret[cmpt_1] = s1[cmpt_1];
			cmpt_1++;
		}
		while (s2[cmpt_2])
		{
			ret[cmpt_1 + cmpt_2] = s2[cmpt_2];
			cmpt_2++;
		}
		ret[cmpt_1 + cmpt_2] = '\0';
		return (ret);
	}
	return (NULL);
}
