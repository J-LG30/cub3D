/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:08:08 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 18:18:10 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>
# define ROT_SPEED 0.1
# define PI 3.14159265358979323846
# define SIZE 32
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FOV 0.66
# define OFFSET 0.01
# if defined(__APPLE__)//&& defined(__MACH__)
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define UP 126
#  define LEFT 123
#  define DOWN 125
#  define RIGHT 124
#  define FRAMES 20
#  include "minilibx_opengl/mlx.h"
# else
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define UP 65362
#  define LEFT 65361
#  define DOWN 65364
#  define RIGHT 65363
#  define FRAMES 6000
#  include "minilibx-linux/mlx.h"
# endif

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_tex_check
{
	char	*id;
	int		count;
}	t_tex_check;

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
}	t_img;

typedef struct s_rayval
{
	double	raydirx;
	double	raydiry;
	double	camerax;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	double	perpwalldist;
	double	tex_pos;
	double	wall_x;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		tex_x;
	int		tex_y;
}	t_rayval;

typedef struct s_player
{
	t_img	*img;
	t_img	*dir_line;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_tex
{
	t_img	*north;
	t_img	*south;
	t_img	*east;
	t_img	*west;
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	int		tex_count;
}	t_tex;

typedef struct s_game
{
	t_win		*win;
	t_img		*bgd;
	t_img		*wall;
	t_player	*player;
	char		**map;
	t_img		*wall_text;
	t_tex		*textures;
	t_color		floor_color;
	t_color		ceiling_color;
	int			parsed_map;
	int			parsed_floor;
	int			parsed_ceiling;
	int			empty_line;
}	t_game;

// cleaning stuff
void	cleanup_game(t_game *game);
int		handle_exit(t_game *game);
// color stuff
int		parse_color(char *line, t_color *color);
int		is_color_line(char *line);
int		format_valid(char *line);
char	**split_rgb(char *line);
// texture stuff
int		is_texture_line(char *line);
int		is_texture_char(char c);
int		parse_texture_paths(t_game *game, char *line);
t_tex	*init_textures(void *mlx_ptr);
void	load_textures(t_game *game);
int		parse_texture_paths(t_game *game, char *line);
void	free_textures(t_tex *textures, void *mlx_ptr);
int		check_texture_duplicate(char *line, t_game *game);

// drawing
t_img	new_sprite(void *mlx, int width, int height);
t_img	new_xpm_sprite(void *mlx, char *path);
void	draw_img(t_img *img, int x, int y, int colour);
void	my_mlx_pixel_put(t_img *data, int x, int y, int colour);
void	draw_texture(t_game *game, t_img *texture, int x, t_rayval *rval);
int		draw_ceiling(t_game *game);
int		draw_floor(t_game *game);
void	clear_image(t_img *data, int colour);
void	draw_wall(t_game *game, t_player *player, t_rayval *rval, int x);

void	open_map(char *path, t_game *game);
void	process_line(char *line, t_game *game, char **map_arr, int *i);
void	map_free(char **map_arr);
void	cast_rays(t_game *game, t_player *player);
void	clear_image(t_img *data, int colour);
int		check_enclosed(char **map);
int		check_player(char **map);
int		check_all_valid_char(char **map);
int		key_press(int keycode, void *param);
int		init_window(t_win *win);
void	init_player(t_game *game, t_player *player);

//map helpers
int		is_valid_identifier_format(const char *line);
// static char	*trim_whitespace(char *line);
int		is_valid_line(char *line, t_game *game);
int		check_top(char **map, int i, int j);
int		check_bottom(char **map, int i, int j);
int		check_right(char **map, int i, int j);
int		check_left(char **map, int i, int j);
int		is_surrounding_char(char c);

//texture helpers

char	*trim_end(char *str);
char	*skip_whitespace(char *str);
int		check_texture_duplicate(char *line, t_game *game);
int		has_duplicate_texture(t_game *game, const char *identifier);

#endif