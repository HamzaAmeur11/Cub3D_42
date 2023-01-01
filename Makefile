# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hameur <hameur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 13:48:25 by hameur            #+#    #+#              #
#    Updated: 2023/01/01 01:33:14 by hameur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#__________________Makefile________________________

NAME	:=	cub3D

HEADER	:=	Cub3d.h

CC	:=	gcc

CFLAGS	:=	-Wall -Wextra -Werror

MLXFLAGS := -lmlx -framework OpenGL -framework AppKit
#new files : `hooks.c ....
SRC	:=	cub3D.c \
		cub_utils.c \
		ft_split.c \
		gnl.c \
		check_map.c \
		parse_map.c \
		put_map.c \
		textures.c \
		hooks.c \
		check_map_utils.c \
		cub_math.c \
		cub_utils_2.c \
		edit_pos.c \
		find_interaction.c \
		find_interaction_h.c \
		find_interaction_v.c \
		init_xpm_clr.c \
		check_xpm_clr.c \

OBJS	:=	$(SRC:.c=.o)

all : $(NAME)
	@echo "Making Cub3D"

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)
	@echo "Removing objects files"

fclean : clean
	@rm -rf $(NAME)
	@echo "Removing Cub3D"

re :	fclean all