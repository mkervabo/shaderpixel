/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:03:23 by gperez            #+#    #+#             */
/*   Updated: 2019/09/11 15:35:40 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_stat	*ft_creat_list(t_ret *ret, t_stat **stat, t_stat *save, int *n)
{
	t_stat	*new;

	if (n != NULL)
		*n = 1;
	(*ret) = (t_ret){2, 0, ret->clonefd, 0};
	if (!(new = (t_stat*)ft_memalloc(sizeof(t_stat))))
		return (NULL);
	new->fd = ret->clonefd;
	new->buf_static = NULL;
	new->next = NULL;
	if (*stat == NULL)
	{
		new->save = new;
		*stat = new;
	}
	else
		new->save = save;
	return (new);
}

static t_stat	*ft_lst(t_ret *ret, t_stat *stat, t_stat *save)
{
	int		crea;

	crea = 0;
	ret->len_line = 0;
	ret->buf_too_small = 0;
	ret->ret = 2;
	if (stat->fd != ret->clonefd)
	{
		stat = save;
		while (stat->fd != ret->clonefd && stat->next != NULL)
			stat = stat->next;
		if (stat->fd != ret->clonefd && stat->next == NULL)
		{
			stat->next = ft_creat_list(ret, &stat, save, &crea);
			stat = stat->next;
		}
	}
	return (stat);
}

static int		ft_malloc_line(int cmpt, t_ret r, const char *buf, char **line)
{
	char	*save;
	int		cmpt_s;
	int		cmpt_p;

	cmpt_p = 0;
	cmpt_s = 0;
	if ((save = ft_strnew((size_t)r.len_line +
		(size_t)(cmpt - cmpt_p))) == NULL)
		return (-1);
	if (r.buf_too_small == 1)
	{
		if (r.len_line > 0)
		{
			ft_strcpy(save, *line);
			cmpt_s = (int)ft_strlen(*line);
		}
		ft_strdel(line);
	}
	while (cmpt_p < cmpt)
	{
		save[cmpt_s++] = buf[cmpt_p++];
	}
	save[cmpt_s] = '\0';
	*line = save;
	return ((int)ft_strlen(*line));
}

static int		sub_get_next_line(t_ret *r, t_stat *s, char *buf, char **line)
{
	int		cmpt;

	cmpt = 0;
	if (r->ret == 0)
		return (0);
	while (buf[cmpt] != '\n' && buf[cmpt] != '\0')
		cmpt++;
	r->len_line = ft_malloc_line(cmpt, *r, buf, line);
	if (s->buf_static != NULL)
		ft_strdel(&s->buf_static);
	if ((s->buf_static = ft_strnew(ft_strlen(buf + cmpt + 1))) == NULL)
		return (-1);
	if (buf[cmpt] != '\n')
	{
		r->buf_too_small = 1;
		ft_strdel(&s->buf_static);
		if ((r->ret = (int)read(r->clonefd, buf, BUFF_SIZE)) == 0)
			return (1);
		buf[r->ret] = '\0';
		return (2);
	}
	ft_strcpy(s->buf_static, buf + cmpt + 1);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static	t_stat		*stat;
	char				*buf;
	t_ret				ret;

	if ((ret.clonefd = fd) < 0 || fd > FOPEN_MAX)
		return (-1);
	if (stat == NULL)
		ft_creat_list(&ret, &stat, NULL, NULL);
	else
		stat = ft_lst(&ret, stat, stat->save);
	if ((buf = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	while (ret.ret == 2)
	{
		if (stat->buf_static != NULL && *(stat->buf_static) != '\0')
			ft_strcpy(buf, stat->buf_static);
		else if (ret.len_line == 0)
		{
			if ((ret.ret = (int)read(ret.clonefd, buf, BUFF_SIZE)) == -1)
				return (-1);
		}
		ret.ret = sub_get_next_line(&ret, stat, buf, line);
	}
	ft_strdel(&buf);
	return (ret.ret);
}
