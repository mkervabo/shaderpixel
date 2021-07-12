/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ptrfct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:22:12 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 13:06:56 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_ptrfct(char *s, int (*f)(int))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (!f)
	{
		ft_putstr(s);
		return ;
	}
	while (s[i])
	{
		ft_putchar((*f)(s[i]));
		i++;
	}
}
