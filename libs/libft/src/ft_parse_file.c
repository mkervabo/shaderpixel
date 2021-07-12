/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:29:17 by gperez            #+#    #+#             */
/*   Updated: 2020/01/03 18:02:25 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_str	*ft_parse_file(char *file)
{
	int			fd;
	int			check;
	char		*line;
	t_lst_str	*lst_str;

	lst_str = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	while ((check = get_next_line(fd, &line)) > 0)
	{
		if (line && lst_str == NULL)
			lst_str = parse_lst_str(lst_str, line);
		else if (line)
			parse_lst_str(lst_str, line);
	}
	if (check == -1)
		return (free_lst_str(lst_str));
	if (close(fd) == -1)
		return (free_lst_str(lst_str));
	return (lst_str);
}
