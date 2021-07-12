/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:12:38 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:07:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab_int(int *tab, int taille, int space)
{
	int		cmpt;

	cmpt = 0;
	if (tab)
	{
		while (cmpt < taille)
		{
			ft_putnbr(tab[cmpt]);
			if (space == 1)
				ft_putchar('\n');
			cmpt++;
		}
	}
}
