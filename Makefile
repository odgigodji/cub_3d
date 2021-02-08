# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namerei <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/07 18:10:51 by namerei           #+#    #+#              #
#    Updated: 2021/02/07 21:12:37 by namerei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= cub3d.c										\
          engine/do_keys.c      						\
          engine/do_textures.c       					\
          engine/do_sprites.c       					\
          engine/drawing.c       						\
          engine/raycasting.c       					\
          parser/parser.c       						\
          get_next_line/get_next_line.c       			\
          get_next_line/get_next_line_utils.c       	\
          parser/check_map.c       						\
          engine/movement.c       						\
          parser/ft_init.c       						\
          parser/floor_and_ceiling.c       				\
          parser/pars_map.c       						\
          parser/pars_tex_and_res.c       				\
          parser/bmp.c

F_PURPLE		= \033[35m
F_GREEN         = \033[32m
F_NONE			= \033[37m

OBJS	= $(SRCS:.c=.o)
NAME	= cub3D
HEADER	= cub3d.h
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -lmlx \
		  -framework OpenGL -framework AppKit ./libft/libft.a

all: $(NAME)

$(NAME):	$(OBJS) $(HEADER)
			@$(MAKE) all -C ./libft
			@gcc $(CFLAGS) $(OBJS) -o cub3D -I $(HEADER)
			@echo "$(F_PURPLE)Cub3D done! $(F_NONE)"

%.o:		%.c $(HEADER)
			@gcc -c -Wall -Werror -Wextra $< -o $@

clean:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C ./libft
			@echo "$(F_GREEN)Cleaned! $(F_NONE)"

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY: 	re, clean, fclean, all

