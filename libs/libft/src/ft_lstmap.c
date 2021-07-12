/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 08:34:42 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 14:50:41 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*m_new;
	t_list	*save;

	if (lst)
	{
		m_new = (*f)(lst);
		save = m_new;
		while (lst->next)
		{
			m_new->next = (*f)(lst->next);
			m_new = m_new->next;
			lst = lst->next;
		}
		return (save);
	}
	return (NULL);
}
