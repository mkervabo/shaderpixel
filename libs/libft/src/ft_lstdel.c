/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 08:15:12 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 14:50:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	while ((*alst))
	{
		next = (*alst)->next;
		(*del)((*alst)->content, (*alst)->content_size);
		ft_memdel((void**)alst);
		*alst = next;
	}
	*alst = NULL;
}
