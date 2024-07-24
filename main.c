/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:58 by jle-goff          #+#    #+#             */
/*   Updated: 2024/07/24 13:43:54 by jle-goff         ###   ########.fr       */
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
}

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF); // Draw pixel (color is white)
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

//check the up down keycodes bc thats weird
int key_press(int keycode, void *param)
{
    t_img   *image;
	t_game	*game;
	int		map_ipos;
	int		map_jpos;

	printf("%i\n", keycode);
	game = (t_game *)param;
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->bgd->img_ptr,
		game->player->posX * SIZE, game->player->posY * SIZE);
    if (keycode == D)//&& game->map[game->player->posY][game->player->posX + 1] != '1')
	{
		game->player->posX += game->player->dirX;
		game->player->posY += game->player->dirY;
	}
	if (keycode == A)//&& game->map[game->player->posY][game->player->posX - 1] != '1')
	{
		game->player->posX -= game->player->dirX;
		game->player->posY -= game->player->dirY;
	}
	if (keycode == W)//&& game->map[game->player->posY - 1][game->player->posX] != '1')
	{
		game->player->posX += game->player->dirX;
		game->player->posY -= game->player->dirY;
	}
	if (keycode == S)//&& game->map[game->player->posY + 1][game->player->posX] != '1')
	{
		game->player->posX -= game->player->dirX;
		game->player->posY += game->player->dirY;
	}
	if (keycode == LEFT) {
        double oldDirX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(-ROT_SPEED) - game->player->dirY * sin(-ROT_SPEED);
        game->player->dirY = oldDirX * sin(-ROT_SPEED) + game->player->dirY * cos(-ROT_SPEED);
        double oldPlaneX = game->player->planeX;
    	game->player->planeX = game->player->planeX * cos(-ROT_SPEED) - game->player->planeY * sin(-ROT_SPEED);
        game->player->planeY = oldPlaneX * sin(-ROT_SPEED) + game->player->planeY * cos(-ROT_SPEED);
    }
    if (keycode == RIGHT) {
        double oldDirX = game->player->dirX;
        game->player->dirX = game->player->dirX * cos(ROT_SPEED) - game->player->dirY * sin(ROT_SPEED);
        game->player->dirY = oldDirX * sin(ROT_SPEED) + game->player->dirY * cos(ROT_SPEED);
        double oldPlaneX = game->player->planeX;
        game->player->planeX = game->player->planeX * cos(ROT_SPEED) -  game->player->planeY * sin(ROT_SPEED);
         game->player->planeY = oldPlaneX * sin(ROT_SPEED) +  game->player->planeY * cos(ROT_SPEED);
    }

	int line_end_x = game->player->posX * SIZE + game->player->dirX * 32;
    int line_end_y = game->player->posY * SIZE + game->player->dirY * 32;
	
	draw_line(game->win->mlx_ptr, game->win->win_ptr, game->player->posX * SIZE, game->player->posY * SIZE, line_end_x, line_end_y);
	
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->player->img->img_ptr,
		game->player->posX * SIZE, game->player->posY * SIZE);
    return (0);
}

int	main(void)
{
	t_win		win;
	t_player	player;
	t_img		bgd;
	t_img		player_img;
	t_game		game;
	t_img		wall;

	open_map("test_map.txt", &game);

	win.width = 1280;
	win.height = 768;
	game.player = &player;
	game.win = &win;
	game.bgd = &bgd;

	bgd.win = &win;

	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, 1024, 768, "Hello world!");
	
	wall = new_sprite(win.mlx_ptr, SIZE, SIZE);
	player_img = new_sprite(win.mlx_ptr, SIZE, SIZE);
	bgd = new_sprite(win.mlx_ptr, SIZE, SIZE);
	player.img = &player_img;

	int	i = 0;
	int	j = 0;
	draw_player(&wall, 0, 0, 0xFFFFFF);
	draw_player(&bgd, 0, 0, 0x000000);
	draw_player(&player_img, 0, 0, 0x00FF0000);
	while (game.map[i])
	{
		j = 0;
		while (game.map[i][j] != '\0')
		{
			if (game.map[i][j] == '1')
			{
				mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, wall.img_ptr, j * SIZE, i * SIZE);
			}
			if (game.map[i][j] == 'N' || game.map[i][j] == 'W' || game.map[i][j] == 'S' || game.map[i][j] == 'E')
			{
				player.posX = j;
				player.posY = i;
				if (game.map[i][j] == 'N')
				{
					player.dirX = 0;
					player.dirY = 1;
				}
				if (game.map[i][j] == 'S')
				{
					player.dirX = 0;
					player.dirY = -1;
				}
				if (game.map[i][j] == 'W')
				{
					player.dirX = -1;
					player.dirY = 0;
				}
				if (game.map[i][j] == 'E')
				{
					player.dirX = 1;
					player.dirY = 0;
				}
			}
			j++;
		}
		i++;
	}
	printf("Player x position: %i\n", player.posX);
	printf("Player y position: %i\n", player.posY);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, player.img->img_ptr, player.posX * SIZE, player.posY * SIZE);	
	mlx_hook(win.win_ptr, 2, 1L<<0, key_press, &game);
	mlx_loop(win.mlx_ptr);
	return (0);
}
