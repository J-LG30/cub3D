/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafasant <rafasant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:08:08 by jle-goff          #+#    #+#             */
/*   Updated: 2024/07/23 17:00:57 by rafasant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "minilibx_opengl/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

#define SIZE 16

#if defined(__APPLE__) && defined(__MACH__)
	#define ESC 53
	#define W 13
	#define A 0
	#define S 1
	#define D 2
	#define UP 126
	#define LEFT 123
	#define DOWN 125
	#define RIGHT 124
	#define FRAMES 20

#else
	#define ESC 65307
	#define W 119
	#define A 97
	#define S 115
	#define D 100
	#define UP 65362
	#define LEFT 65361
	#define DOWN 65364
	#define RIGHT 65363
	#define FRAMES 6000
#endif

typedef struct  s_win
{
	void    *mlx_ptr;
	void    *win_ptr;
	int     width;
	int     height;
}   t_win;

typedef struct s_img
{
	t_win	*win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
	int		x;
	int		y;
}		t_img;

typedef struct s_player
{
	t_img	*img;
	int		x;
	int		y;
}	t_player;


typedef struct s_game
{
	t_win		*win;
	t_img		*bgd;
	t_player	*player;
	char		**map;
}	t_game;

void	open_map(char *path, t_game *game);

#endif

