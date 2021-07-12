/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:37:06 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 12:54:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***tab)
{
	int		i;
	char	**tabb;

	if (!tab || !(*tab))
		return ;
	tabb = *tab;
	i = 0;
	while (tabb[i])
	{
		ft_memdel((void**)&(tabb[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}
