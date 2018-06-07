#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 12:26:10 by tlutsyk           #+#    #+#              #
#    Updated: 2017/10/27 12:26:11 by tlutsyk          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FLAGS = -Wall -Wextra -Werror

CFILES = ft_memcmp.c ft_strcmp.c ft_strncmp.c ft_isalpha.c ft_isdigit.c \
 ft_isalnum.c ft_isprint.c ft_islower.c ft_isupper.c ft_toupper.c ft_tolower.c \
 ft_atoi.c ft_strequ.c ft_strnequ.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
 ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
 ft_strnew.c ft_itoa.c ft_strmap.c ft_strmapi.c ft_strsub.c ft_strjoin.c \
 ft_strtrim.c ft_strsplit.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
 ft_memset.c ft_memalloc.c ft_bzero.c ft_strdel.c ft_putchar.c ft_putstr.c \
 ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
 ft_putnbr_fd.c ft_strclr.c ft_striter.c ft_striteri.c ft_memdel.c \
 ft_strlcat.c ft_strlen.c ft_isascii.c ft_lstnew.c ft_lstdelone.c \
 ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_realloc.c ft_strjoin_def.c\
 ft_strcalc.c ft_sqrt.c ft_power.c ft_list_push_back.c ft_itoa_long.c \
 get_next_line.c ft_printf.c ft_print_p.c ft_print_s.c ft_print_un_char.c \
 ft_print_un_string.c ft_print_integer.c ft_undigit.c ft_print_x.c \
 ft_print_o.c ft_add_unc_unstr.c ft_addinteger.c ft_print_add.c \
 ft_strsplit_cw.c

O_FILES = ft_memcmp.o ft_strcmp.o ft_strncmp.o ft_isalpha.o ft_isdigit.o \
 ft_isalnum.o ft_isprint.o ft_islower.o ft_isupper.o ft_toupper.o ft_tolower.o \
 ft_atoi.o ft_strequ.o ft_strnequ.o ft_strdup.o ft_strcpy.o ft_strncpy.o \
 ft_strcat.o ft_strncat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o \
 ft_strnew.o ft_itoa.o ft_strmap.o ft_strmapi.o ft_strsub.o ft_strjoin.o \
 ft_strtrim.o ft_strsplit.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o \
 ft_memset.o ft_memalloc.o ft_bzero.o ft_strdel.o ft_putchar.o ft_putstr.o \
 ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
 ft_putnbr_fd.o ft_strclr.o ft_striter.o ft_striteri.o ft_memdel.o \
 ft_strlcat.o ft_strlen.o ft_isascii.o ft_lstnew.o ft_lstdelone.o \
 ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_realloc.o ft_strjoin_def.o\
 ft_strcalc.o ft_sqrt.o ft_power.o ft_list_push_back.o ft_itoa_long.o \
 get_next_line.o ft_printf.o ft_print_p.o ft_print_s.o ft_print_un_char.o \
 ft_print_un_string.o ft_print_integer.o ft_undigit.o ft_print_x.o \
 ft_print_o.o ft_add_unc_unstr.o ft_addinteger.o ft_print_add.o \
 ft_strsplit_cw.o

all: $(addprefix ../obj/,$(O_FILES))

../obj/%.o: %.c
	@echo "$(STYLE_BOLD)$(COLOR_YELLOW) $< has been compiled.$(STYLE_NORMAL)"
	@gcc -c $(FLAGS) $< -o $@ 
    
clean:
	@echo "$(STYLE_BOLD)$(COLOR_RED)All the object files (libft) have been deleted.$(STYLE_NORMAL)"
	@rm -rf $(addprefix ../obj/,$(O_FILES))

fclean: clean
	@echo "$(STYLE_BOLD)$(COLOR_RED)$(NAME) has been deleted.$(STYLE_NORMAL)"

re: fclean all

.PHONY: clean all fclean re