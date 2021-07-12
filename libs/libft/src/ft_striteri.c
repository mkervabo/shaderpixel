/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:32:02 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:28:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		cmpt;

	if (s && (*f) != NULL)
	{
		cmpt = 0;
		while (s[cmpt])
		{
			(*f)((unsigned int)cmpt, s + cmpt);
			cmpt++;
		}
	}
}
