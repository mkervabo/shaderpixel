/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:49:22 by gperez            #+#    #+#             */
/*   Updated: 2020/01/05 15:51:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"
# include "msgs.h"
# include "str_color.h"

# define BIN "01"
# define OCT "01234567"
# define HEXA "0123456789ABCDEF"
# define DEC "0123456789"
# define PREC 1e-15

typedef struct	s_3d
{
	double				x;
	double				y;
	double				z;
}				t_3d;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_bzero(void *s, size_t n);
char			*ft_charadd(char add, char *str);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_puttab_s(char **tab, int space);
void			ft_puttab_int(int *tab, int taille, int space);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_strclr(char *s);
size_t			ft_strlen(char const *s);
void			ft_putnbr(int n);
void			ft_putnbrl(long long int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_swap(int *a, int *b);
double			ft_pow(double n, int p);
int				ft_sqrt(int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_toupper(int c);
char			*ft_str_toupper(char *s);
int				ft_tolower(int c);
void			ft_putstr_ptrfct(char *s, int (*f)(int));
char			*ft_str_tolower(char *s);
long long int	ft_atoi(char const *str);
char			*ft_stradd(char *str, char *add);
char			*ft_strstr(char const *haystack, char const *needle);
char			*ft_strnstr(char const *haystack, char const *needle,
				size_t len);
char			*ft_strnew(size_t size);
void			ft_strfill(char *str, size_t size, char c);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strdup(char const *s1);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_strcat(char *s1, char const *s2);
char			*ft_strncat(char *s1, char const *s2, size_t n);
size_t			ft_strlcat(char *dst, char const *src, size_t size);
char			*ft_strcpy(char *dst, char const *src);
char			*ft_strncpy(char *dst, char const *src, size_t len);
int				ft_strindexof(char const *str, char c);
char			*ft_substr(const char *str, int index, size_t length);
char			*ft_itoa(int n);
char			*ft_itoal(long long n);
char			*ft_itoaul(unsigned long n);
char			*ft_itoad(double n, int prec);
char			*ft_decimal_to_base(unsigned long long nb, char const *base);
long long		ft_base_to_decimal(char *nb, char const *base);
char			*ft_itoa_base(void **nb, char const *base_in,
	char const *base_out);
void			ft_lstmdisplay(t_list *list);
void			ft_lstdisplay(t_list *list);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *neww);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_free_tab(char ***tab);
double			ft_atoi_db(char const *str);
long double		ft_atoi_ldb(char const *str);
char			*ft_itoald(long double nb, int prec);
int				ft_strisdigit(char *str);
long double		ft_powld(long double n, int p);
int				ft_putnstr(char *str, int n);
int				ft_equalf(float a, float b);
int				ft_tab_length(char **tab);

typedef struct	s_lst_str
{
	char				*str;
	struct s_lst_str	*next;
}				t_lst_str;

t_lst_str		*free_lst_str(t_lst_str *lst_str);
t_lst_str		*parse_lst_str(t_lst_str *lst_str, char *line);
int				stock_file(t_lst_str *lst_str, char **out, int ret_char);
t_lst_str		*ft_parse_file(char	*file);

#endif
