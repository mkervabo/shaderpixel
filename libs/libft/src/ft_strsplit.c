/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:05:21 by gperez            #+#    #+#             */
/*   Updated: 2020/01/03 02:46:05 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_word(char const *s, char c)
{
	int	out;
	int	i;

	out = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			out++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (out);
}

int		count_letter(char const *s, char c)
{
	int	i;
	int out;

	i = 0;
	out = 0;
	if (s)
	{
		while (s[i] && s[i] != c)
		{
			out++;
			i++;
		}
	}
	return (out);
}

char	**malloc_free_out(char **out, int i_w, int l)
{
	if (!(out[i_w] = ft_memalloc(sizeof(char) * l + 1)))
		ft_free_tab(&out);
	return (out);
}

char	**fill_str(char **out, char const *s, char c, int nb_w)
{
	int	i_str;
	int	i_l;
	int	l;
	int	i_w;

	i_w = 0;
	i_str = 0;
	while (i_w < nb_w)
	{
		while (s[i_str] && s[i_str] == c)
			i_str++;
		if (s[i_str] && s[i_str] != c)
		{
			l = count_letter(&(s[i_str]), c);
			if (!(malloc_free_out(out, i_w, l)))
				return (NULL);
			i_l = 0;
			while (i_l < l)
				out[i_w][i_l++] = s[i_str++];
			out[i_w][i_l] = '\0';
			i_w++;
		}
	}
	out[i_w] = NULL;
	return (out);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**out;
	int		nb_w;

	if (!s)
		return (NULL);
	nb_w = count_word(s, c);
	if (!(out = ft_memalloc(sizeof(char*) * nb_w + 1)))
		return (NULL);
	return (fill_str(out, s, c, nb_w));
}
