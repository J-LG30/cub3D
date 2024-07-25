/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:58 by jle-goff          #+#    #+#             */
/*   Updated: 2024/07/25 12:14:17 by jle-goff         ###   ########.fr       */
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

// void	draw_line(t_img	*img, int x, int y, int colour, t_player *player)
// {
// 	int	i;
// 	int	j;

// 	i = x;
// 	j = y;
// 	printf("a\n");
// 	printf("dirY %f\n", player->dirY);
// 	printf("dirX %f\n", player->dirX);
// 	printf("i %i", i);
// 	printf("j %i", j);
// 	while (i < (x * SIZE) + SIZE && i > 0)
// 	{
// 		j = y;
// 		while (j < (y * SIZE) + SIZE && j > 0)
// 		{
// 			my_mlx_pixel_put(img, i, j, colour);
// 			j++;
// 			j *= player->dirY;
// 		}
// 		printf("in here\n");
// 		i++;
// 		i *= player->dirX;
// 		printf("i is now %i", i);
// 	}
// }


void
plot_line (int x0, int y0, int x1, int y1, t_game *game, int colour)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x0,y0, colour);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void	draw_line(t_game *game, int colour)
{
	int size_offset_posX = round(game->player->posX * SIZE + SIZE/2);
	int size_offset_posY = round(game->player->posY * SIZE + SIZE/2);
	int	size_offset_pos2X = round(size_offset_posX + (SIZE * game->player->dirX));
	int	size_offset_pos2Y = round(size_offset_posY + (SIZE * game->player->dirY));

	printf("Center: (%d, %d)\n", size_offset_posX, size_offset_posY);
	printf("End: (%d, %d)\n", size_offset_pos2X, size_offset_pos2Y);
	
	plot_line(size_offset_posX, size_offset_posY, size_offset_pos2X, size_offset_pos2Y, game, colour);
}

//draws square image
void	draw_img(t_img *img, int x, int y, int colour)
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
			my_mlx_pixel_put(img, i, j, colour);
			j++;
		}
		i++;
	}
}

//check the up down keycodes bc thats weird
int key_press(int keycode, void *param)
{
    t_img   *image;
	t_game	*game;
	int		map_ipos;
	int		map_jpos;

	game = (t_game *)param;

	draw_line(game, 0x00000000);
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->bgd->img_ptr,
		game->player->posX * SIZE, game->player->posY * SIZE);
    if (keycode == S)//&& game->map[game->player->posY][game->player->posX + 1] != '1')
	{
		game->player->posX -= game->player->dirX;
		game->player->posY -= game->player->dirY;
	}
	if (keycode == W)//&& game->map[game->player->posY][game->player->posX - 1] != '1')
	{
		game->player->posX += game->player->dirX;
		game->player->posY += game->player->dirY;
	}
	if (keycode == D) // Strafe Right aka find perpendicular vector with 90 degree clockwise rotation
	{
		game->player->posX -= game->player->dirY; // Move rightward along the X axis
		game->player->posY += game->player->dirX; // Move rightward along the Y axis
	}
	if (keycode == A) // Strafe Left aka find perpendicular vector with 90 degree anti-clockwise rotation
	{
		game->player->posX += game->player->dirY; // Move leftward along the X axis
		game->player->posY -= game->player->dirX; // Move leftward along the Y axis
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
	
	draw_line(game, 0x00FF0000);
	
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
	t_img		dir_line;

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
	dir_line = new_sprite(win.mlx_ptr, SIZE, SIZE);
	player.img = &player_img;
	player.dir_line = &dir_line;

	int	i = 0;
	int	j = 0;
	draw_img(&wall, 0, 0, 0xFFFFFF);
	draw_img(&bgd, 0, 0, 0x000000);
	draw_img(&player_img, 0, 0, 0x00FF0000);
	while (game.map[i])
	{
		j = 0;
		while (game.map[i][j] != '\0')
		{
			if (game.map[i][j] == '1')
				mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, wall.img_ptr, j * SIZE, i * SIZE);
			if (game.map[i][j] == 'N' || game.map[i][j] == 'W' || game.map[i][j] == 'S' || game.map[i][j] == 'E')
			{
				player.posX = j;
				player.posY = i;
				if (game.map[i][j] == 'N')
				{
					player.dirX = 0;
					player.dirY = -1;
				}
				if (game.map[i][j] == 'S')
				{
					player.dirX = 0;
					player.dirY = 1;
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
	
	draw_line(&game, 0x00FF0000);
	
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, dir_line.img_ptr, player.posX * SIZE + SIZE / 2, player.posY * SIZE - SIZE / 2);
	player.planeX = 0;
	player.planeY = 0.66;
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, player.img->img_ptr, player.posX * SIZE, player.posY * SIZE);	
	mlx_hook(win.win_ptr, 2, 1L<<0, key_press, &game);
	mlx_loop(win.mlx_ptr);
	return (0);
}
