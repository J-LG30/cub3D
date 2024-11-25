# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 17:10:34 by jle-goff          #+#    #+#              #
#    Updated: 2024/11/25 15:25:21 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = @cc
FLAGS = -Wall -Wextra -Werror -lm

UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	INCLUDE = -lXext -lX11
	MLX_DIR = ./minilibx-linux
else
	INCLUDE = -framework OpenGL -framework Appkit
	MLX_DIR = ./minilibx_opengl
endif

MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c map.c map2.c raycaster.c parser.c parser2.c texture.c color.c cleanup.c \
	movement.c graphic_helpers.c init.c draw_textures.c drawing.c load_textures.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) $(MLX) $(INCLUDE) -o $(@) 

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) --no-print-directory -C $(MLX_DIR)
clean:
	@rm -f $(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re