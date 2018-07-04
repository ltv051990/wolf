#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 19:59:39 by tlutsyk           #+#    #+#              #
#    Updated: 2018/05/14 19:59:41 by tlutsyk          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=	clang

CFLAGS		=	-Wextra -Werror -Wall -O3 -Os -flto=thin

NAME		=	wolf3d

SRC			=	main.c list.c ft_error.c hooks.c dda_algo.c map_validations.c \
				init_functions.c draw_functions.c

HDRS		=	wolf.h

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

OBJDIR		=	obj

LIBFT = libft

O_FILES =  obj/*.o

LIBR		=	-framework OpenGL -framework AppKit -framework SDL2	\
				-framework SDL2_ttf -framework SDL2_image -rpath ./frameworks

INCLUDES	=	-I./frameworks/SDL2.framework/Headers
INCLUDES	+=	-I./frameworks/SDL2_ttf.framework/Headers
INCLUDES	+=	-I./frameworks/SDL2_image.framework/Headers
INCLUDES	+=	-I./frameworks/SDL2_mixer.framework/Headers
INCLUDES	+=	-F./frameworks

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@echo "Creating" $(NAME) "..."
	make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(O_FILES) $(INCLUDES) $(LIBR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJ): $(OBJDIR)/%.o : %.c $(HDRS)
	@echo "Compiling" $< "..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Obj clean"
	make clean -C libft
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Full clean"
	make fclean -C libft
	@rm -rf $(NAME)

re: fclean all