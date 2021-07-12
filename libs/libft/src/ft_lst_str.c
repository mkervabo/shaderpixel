/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:30:48 by gperez            #+#    #+#             */
/*   Updated: 2020/01/03 17:46:39 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_lst_str	*allocate_lst_str(char *line)
{
	t_lst_str *lst;

	if (!(lst = ft_memalloc(sizeof(t_lst_str))))
		return (NULL);
	lst->str = line;
	lst->next = NULL;
	return (lst);
}

static size_t		lst_strlen(t_lst_str *lst_str, int ret_char)
{
	t_lst_str	*cp;
	size_t		ret;
	int			i;

	cp = lst_str;
	ret = 0;
	while (cp)
	{
		i = 0;
		while (cp->str[i])
		{
			i++;
			ret++;
		}
		if (ret_char)
			ret++;
		cp = cp->next;
	}
	return (ret);
}

t_lst_str			*parse_lst_str(t_lst_str *lst_str, char *line)
{
	t_lst_str	*cp;

	if (lst_str == NULL)
		return (allocate_lst_str(line));
	else
	{
		cp = lst_str;
		while (cp->next)
			cp = cp->next;
		cp->next = allocate_lst_str(line);
		return (cp->next);
	}
}

t_lst_str			*free_lst_str(t_lst_str *lst_str)
{
	if (lst_str)
	{
		if (lst_str->next)
			free_lst_str(lst_str->next);
		ft_memdel((void**)(&(lst_str->str)));
		ft_memdel((void**)(&lst_str));
	}
	return (NULL);
}

int					stock_file(t_lst_str *lst_str, char **out, int ret_char)
{
	t_lst_str	*cp;
	int			i_str;
	int			i;
	size_t		nb_c;

	cp = lst_str;
	nb_c = lst_strlen(lst_str, ret_char);
	if (!(*out = ft_memalloc(sizeof(char) * nb_c + 1)))
		return (1);
	i_str = 0;
	while (cp)
	{
		i = 0;
		while (cp->str[i])
			(*out)[i_str++] = cp->str[i++];
		if (ret_char)
			(*out)[i_str++] = '\n';
		cp = cp->next;
	}
	(*out)[i_str] = '\0';
	return (0);
}
