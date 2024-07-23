# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 17:10:34 by jle-goff          #+#    #+#              #
#    Updated: 2024/07/21 17:11:31 by jle-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = @cc
FLAGS = -Wall -Wextra -Werror

UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	INCLUDE = -lXext -lX11
	MLX_DIR = ./minilibx-linux
else
	INCLUDE = -framework OpenGL -framework Appkit
	MLX_DIR = ./minilibx_opengl
endif

MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	@$(CC) $(FLAGS) $(OBJS) $(MLX) $(INCLUDE) -o $(@)

$(MLX):
	@$(MAKE) --no-print-directory -C $(MLX_DIR)
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re