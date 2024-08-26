/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:08:08 by jle-goff          #+#    #+#             */
/*   Updated: 2024/07/28 16:59:31 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <math.h>

#define ROT_SPEED 0.1
#define PI const double (4.0 * atan(1.0))
#define SIZE 32

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
	#include "minilibx_opengl/mlx.h"

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
	#include "minilibx-linux/mlx.h"
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
	t_img	*dir_line;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;


typedef struct s_game
{
	t_win		*win;
	t_img		*bgd;
	t_img		*wall;
	t_player	*player;
	char		**map;
}	t_game;

void	open_map(char *path, t_game *game);
void	cast_rays(t_game *game, t_player *player);
void	plot_line (int x0, int y0, int x1, int y1, t_game *game, int colour);
void	draw_line(t_game *game, int x, int y0, int y1, int colour);
void	my_mlx_pixel_put(t_img *data, int x, int y, int colour);
void	clear_image(t_img *data, int colour);

#endif

