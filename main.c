/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:58 by jle-goff          #+#    #+#             */
/*   Updated: 2024/07/22 17:03:33 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img   new_sprite(void *mlx, int width, int height)
{
	t_img   image;

	image.img_ptr = mlx_new_image(mlx, width, height);
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
									&image.line_len, &image.endian);
	return (image);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = colour;
}

void	draw_player(t_img *player, int x, int y, int colour)
{
	int	i;
	int	j;

	i = x * SIZE;
	j = y * SIZE;
	while (i < (x * SIZE) + SIZE)
	{
		j = y;
		while (j < (y * SIZE) + SIZE)
		{
			my_mlx_pixel_put(player, i, j, colour);
			j++;
		}
		i++;
	}
	//mlx_put_image_to_window(player->win->mlx_ptr, player->win->win_ptr, player->img_ptr, 0, 0);	
}

int key_press(int keycode, void *param)
{
    t_img   *image;
	t_game	*game;
	int		map_ipos;
	int		map_jpos;

	printf("%i", keycode);
	game = (t_game *)param;
	//draw_player(game->player->img, game->player->x, game->player->y, 0xFFFFFFFF);
    if (keycode == RIGHT && game->player->x + SIZE <= game->win->width)
		game->player->x++;
	if (keycode == LEFT && game->player->x - SIZE >= 0)
		game->player->x--;
	if (keycode == UP)
		game->player->y--;
	if (keycode == DOWN)
		game->player->y++;
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->bgd->img_ptr, 0, 0);
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->player->img->img_ptr,
		game->player->x * SIZE, game->player->y * SIZE);
    return (0);
}

int	main(void)
{
	t_win		win;
	t_player	player;
	t_img		bgd;
	t_img		player_img;
	t_game		game;

	win.width = 1080;
	win.height = 724;
	game.player = &player;
	game.win = &win;
	game.bgd = &bgd;

	bgd.win = &win;

	player.x = 0;
	player.y = 0;

	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, 1024, 768, "Hello world!");
	
	bgd = new_sprite(win.mlx_ptr, win.width, win.height);
	player_img = new_sprite(win.mlx_ptr, SIZE, SIZE);
	player.img = &player_img;

	draw_player(&player_img, player.x, player.y, 0x00FF0000);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, player.img->img_ptr, 0, 0);	
	mlx_key_hook(win.win_ptr, &key_press, &game);
	mlx_loop(win.mlx_ptr);
	return (0);
}








// #include "minilibx_opengl/mlx.h"

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1028, 700, "Hello world!");
// 	img.img = mlx_new_image(mlx, 1028, 700);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }
