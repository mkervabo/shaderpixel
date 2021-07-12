/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:12:43 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:06:56 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	cmpt;

	if (s)
	{
		cmpt = 0;
		while (s[cmpt])
		{
			ft_putchar_fd(s[cmpt], fd);
			cmpt++;
		}
	}
}
