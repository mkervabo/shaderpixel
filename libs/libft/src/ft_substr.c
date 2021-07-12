/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:06:23 by gperez            #+#    #+#             */
/*   Updated: 2019/11/11 13:04:40 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, int index, size_t length)
{
	char	*substr;
	size_t	len_stri;

	if (!str || index < 0 || (size_t)index > ft_strlen(str) - 1)
		return (NULL);
	len_stri = ft_strlen(&str[index]);
	if (!len_stri)
		return (NULL);
	if (len_stri < length)
		length = len_stri;
	substr = ft_strnew(length + 1);
	ft_strncpy(substr, &str[index], length);
	return (substr);
}
