NAME = libft.a

FLAG = -Wall -Werror -Wextra

SRC =	src/ft_memset.c \
		src/ft_memcpy.c \
		src/ft_memccpy.c \
		src/ft_memmove.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_memalloc.c \
		src/ft_memdel.c \
		src/ft_bzero.c \
		src/ft_putchar.c \
		src/ft_putstr.c \
		src/ft_putendl.c \
		src/ft_puttab_s.c \
		src/ft_puttab_int.c \
		src/ft_putchar_fd.c \
		src/ft_putstr_fd.c \
		src/ft_putendl_fd.c \
		src/ft_strclr.c \
		src/ft_putnbr.c \
		src/ft_putnbrl.c \
		src/ft_strlen.c \
		src/ft_putnbr_fd.c \
		src/ft_swap.c \
		src/ft_pow.c \
		src/ft_sqrt.c \
		src/ft_isalpha.c \
		src/ft_isdigit.c \
		src/ft_isalnum.c \
		src/ft_isprint.c \
		src/ft_isascii.c \
		src/ft_strcmp.c \
		src/ft_strncmp.c \
		src/ft_strequ.c \
		src/ft_strnequ.c \
		src/ft_toupper.c \
		src/ft_str_toupper.c \
		src/ft_tolower.c \
		src/ft_str_tolower.c \
		src/ft_putstr_ptrfct.c \
		src/ft_atoi.c \
		src/ft_stradd.c \
		src/ft_strstr.c \
		src/ft_strnstr.c \
		src/ft_strnew.c \
		src/ft_strfill.c \
		src/ft_strdel.c \
		src/ft_striter.c \
		src/ft_striteri.c \
		src/ft_strmapi.c \
		src/ft_strmap.c \
		src/ft_strdup.c \
		src/ft_strrchr.c \
		src/ft_strchr.c \
		src/ft_strsub.c \
		src/ft_strjoin.c \
		src/ft_strtrim.c \
		src/ft_strsplit.c \
		src/ft_strcat.c \
		src/ft_strncat.c \
		src/ft_strlcat.c \
		src/ft_strncpy.c \
		src/ft_strcpy.c \
		src/ft_strindexof.c \
		src/ft_substr.c \
		src/ft_itoa.c \
		src/ft_itoa_base.c \
		src/ft_decimal_to_base.c \
		src/ft_base_to_decimal.c \
		src/ft_itoal.c \
		src/ft_itoaul.c \
		src/ft_itoad.c \
		src/ft_lstdisplay.c \
		src/ft_lstmdisplay.c \
		src/ft_lstnew.c \
		src/ft_lstdelone.c \
		src/ft_lstdel.c \
		src/ft_lstadd.c \
		src/ft_lstiter.c \
		src/ft_lstmap.c \
		src/ft_free_tab.c \
		src/get_next_line.c \
		src/ft_atoi_db.c \
		src/ft_itoald.c \
		src/ft_strisdigit.c \
		src/ft_atoi_ldb.c \
		src/ft_putnstr.c \
		src/ft_lst_str.c \
		src/ft_parse_file.c \
		src/ft_equalf.c \
		src/ft_tab_length.c \

NC = \033[0m
BOLD =\033[1m
DIM =\033[2m
ITALIC =\033[3m
UNDER =\033[4m
BLINK =\033[5m

RS_BO = \033[21m
RS_D = \033[22m
RS_I = \033[23m
RS_U =\033[24m
RS_BL = \033[25m

WHITE = \033[37m
BLUE = \033[38;5;37m
CYAN = \033[38;5;117m
GREEN = \033[38;5;120m
MAGENTA = \033[38;5;135m
RED = \033[38;5;203m

COLOR1 = \033[38;5;75m
COLOR2 = \033[38;5;178m

LIBS_H = includes/

INC =	includes/libft.h \
		includes/msgs.h \
		includes/str_color.h \

LIBS = $(addprefix -I,$(LIBS_H))

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $^
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BL)$(RS_BO)$(GREEN)succesfuly made!$(NC)%20s\n" $(NAME)

%.o : %.c $(INC)
	@printf "$(BOLD)$(COLOR1)%20s : $(RS_BO)$(COLOR2)%20s$(WHITE) ...$(NC)" $(NAME) $(<F)
	@gcc $(FLAG) $(LIBS) -o $@ -c $<
	@printf "\r"

clean :
	@/bin/rm -rf src/*.o

fclean : clean
	@/bin/rm -rf $(NAME)

re : fclean all
