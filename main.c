/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:58 by jle-goff          #+#    #+#             */
/*   Updated: 2024/09/30 14:03:24 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img   new_sprite(void *mlx, int width, int height)
{
	t_img   image;

	image.img_ptr = mlx_new_image(mlx, width, height);
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
									&image.line_len, &image.endian);
	image.w = width;
	image.h = height;
	return (image);
}


t_img	new_xpm_sprite(void *mlx, char *path)
{
	t_img   image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.w, &image.h);
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


// void	plot_line (int x0, int y0, int x1, int y1, t_game *game, int colour)
// {
//   int dx =  abs (x1 - x0);
//   int sx = x0 < x1 ? 1 : -1;
//   int dy = -abs (y1 - y0);
//   int sy = y0 < y1 ? 1 : -1; 
//   int err = dx + dy;
//   int e2; /* error value e_xy */
 
//   while (1)
//   {  /* loop */
//     mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x0,y0, colour);
//     if (x0 == x1 && y0 == y1) 
// 		break;
//     e2 = 2 * err;
//     if (e2 >= dy)
// 	{
// 		err += dy;
// 		x0 += sx;
// 	}
//     if (e2 <= dx)
// 	{ 
// 		err += dx;
// 		y0 += sy;
// 	}
//   }
// }

// void	plot_line (int x0, int y0, int x1, int y1, t_game *game, int colour)
// {
//   int dx =  abs (x1 - x0);
//   int sx = x0 < x1 ? 1 : -1;
//   int dy = -abs (y1 - y0);
//   int sy = y0 < y1 ? 1 : -1; 
//   int err = dx + dy;
//   int e2; /* error value e_xy */
 
//   while (1)
//   {  /* loop */
//     //mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x0,y0, colour);
//     if (x0 == x1 && y0 == y1) 
// 		break;
//     e2 = 2 * err;
//     if (e2 >= dy)
// 	{
// 		err += dy;
// 		x0 += sx;
// 	}
//     if (e2 <= dx)
// 	{ 
// 		err += dx;
// 		y0 += sy;
// 	}
//   }
// }

// void	draw_line(t_game *game, int colour)
// {
// 	int size_offset_posX = round(game->player->posX * SIZE + SIZE/2);
// 	int size_offset_posY = round(game->player->posY * SIZE + SIZE/2);
// 	int	size_offset_pos2X = round(size_offset_posX + (SIZE * 2 * game->player->dirX));
// 	int	size_offset_pos2Y = round(size_offset_posY + (SIZE * 2 * game->player->dirY));

// 	printf("Center: (%d, %d)\n", size_offset_posX, size_offset_posY);
// 	printf("End: (%d, %d)\n", size_offset_pos2X, size_offset_pos2Y);
	
// 	plot_line(size_offset_posX, size_offset_posY, size_offset_pos2X, size_offset_pos2Y, game, colour);
// }

void	draw_line(t_game *game, int x, int y0, int y1, int colour)
{
	int	i;

	i = y0;
	while (i < y1)
	{
		my_mlx_pixel_put(game->wall, x, i, colour);
		i++;
	}
	//mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->wall->img_ptr, x, 0);
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

int	check_collision(t_player *player, int keycode, char **map)
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;

	posX = player->posX;
	posY = player->posY;
	dirX = player->dirX;
	dirY = player->dirY;

	if (keycode == S)
	{
		if (map[(int)(posY - dirY)][(int)(posX - dirX)] == '1')
			return 1;
	}
	else if (keycode == W)
	{
		// printf("MAP Y COORDINATE: %i, MAP X COORDINATE: %i\n", (int)(posY + dirY), (int)(posX + dirX));
		// printf("MAP CHAR: %c\n", map[(int)(posY + dirY)][(int)(posX + dirX)]);
		if (map[(int)(posY + dirY)][(int)(posX + dirX)] == '1')
		{
			printf("will collide with a wall\n");
			return (1);
		}
	}
	else if (keycode == D)
	{
		printf("MAP Y COORDINATE: %i, MAP X COORDINATE: %i\n", (int)(posY + dirX), (int)(posX - dirY));
		printf("MAP CHAR: %c\n", map[(int)(posY + dirX)][(int)(posX - dirY)]);
		if (map[(int)(posY + dirX)][(int)(posX - dirY)] == '1')
			return (1);
	}
	else if (keycode == A && map[(int)(posY - dirX)][(int)(posX + dirY)] == '1')
		return (1);
	return (0);
}

//check the up down keycodes bc thats weird
int key_press(int keycode, void *param)
{
    t_img   *image;
	t_game	*game;
	int		map_ipos;
	int		map_jpos;
	int		x_factor;
	int		y_factor;

	game = (t_game *)param;
	if (!check_collision(game->player, keycode, game->map))
	{
		printf("passed collision check\n");
		if (keycode == S)
		{
			game->player->posX -= game->player->dirX;
			game->player->posY -= game->player->dirY;
		}
		if (keycode == W)
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
	}

		// 	if ((keycode == S) && game->map[(int)(game->player->posY - game->player->dirY)][(int)game->player->posX] != '1')
		// {
		// 	game->player->posX -= game->player->dirX;
		// 	game->player->posY -= game->player->dirY;
		// }
		// if (keycode == W &&( game->map[(int)(game->player->posY + game->player->dirY)][(int)game->player->posX]) != '1')
		// {
		// 	// printf("Y FACTOR: %i\n", y_factor);
		// 	// printf("INT OF THE NEW Y POS: %i\n", (int)(game->player->posY + game->player->dirY));
		// 	game->player->posX += game->player->dirX;
		// 	game->player->posY += game->player->dirY;
		// }
		// if (keycode == D && game->map[(int)game->player->posY][(int)(game->player->posX + game->player->dirX)] != '1') // Strafe Right aka find perpendicular vector with 90 degree clockwise rotation
		// {
		// 	game->player->posX -= game->player->dirY; // Move rightward along the X axis
		// 	game->player->posY += game->player->dirX; // Move rightward along the Y axis
		// }
		// if (keycode == A && game->map[(int)game->player->posY][(int)(game->player->posX - game->player->dirX)] != '1') // Strafe Left aka find perpendicular vector with 90 degree anti-clockwise rotation
		// {
		// 	game->player->posX += game->player->dirY; // Move leftward along the X axis
		// 	game->player->posY -= game->player->dirX; // Move leftward along the Y axis
		// }
	
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
	cast_rays(game, game->player);
	printf("PLAYER POS X: %i\n", (int)game->player->posX);
	printf("PLAYER POS Y: %i\n", (int)game->player->posY);
	//draw_line(game, 0x00FF0000);
	
	// mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->player->img->img_ptr,
	// 	game->player->posX * SIZE, game->player->posY * SIZE);
    return (0);
}

int	check_extension(char *map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (ft_strlen(map) >= 4)
	{
		if (map[i - 4] == '.' && map[i - 3] == 'c'
			&& map[i - 2] == 'u' && map[i - 1] == 'b')
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_win		win;
	t_player	player;
	t_img		bgd;
	t_img		player_img;
	t_game		game;
	t_img		wall;
	t_img		dir_line;
	t_img		wall_text;

	if (argc != 2 || !argv[0] || !argv[1])
	{
		printf("Usage: ./cub3d [Map.cub]\n");
		exit (1);
	}
	if (!check_extension(argv[1]))
	{
		printf("Error: Map file needs to be of type .cub\n");
		exit (1);
	}
	open_map(argv[1], &game);

	// if (!game.map)
	// {
	// 	printf("uh oh no map\n");
	// 	exit (1);
	// }
	win.width = 1280;
	win.height = 768;
	game.player = &player;
	game.win = &win;
	game.bgd = &bgd;
	game.wall = &wall;
	game.wall_text = &wall_text;

	wall_text = new_xpm_sprite(win.mlx_ptr, "bark.xpm");
	bgd.win = &win;

	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, 1280, 768, "Hello world!");
	
	wall = new_sprite(win.mlx_ptr, win.width, win.height);
	player_img = new_sprite(win.mlx_ptr, SIZE, SIZE);
	bgd = new_sprite(win.mlx_ptr, win.width, win.height);
	player.img = &player_img;
	player.dir_line = &dir_line;

	int	i = 0;
	int	j = 0;
	draw_img(&bgd, 0, 0, 0x000000);
	while (game.map[i])
	{
		j = 0;
		while (game.map[i][j] != '\0')
		{
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
	
	float FOV = 0.66;
	player.planeX = player.dirY * -1 * FOV; 
	player.planeY = player.dirX * FOV;
	cast_rays(&game, &player);
	
	mlx_hook(win.win_ptr, 2, 1L<<0, key_press, &game);
	mlx_loop(win.mlx_ptr);
	return (0);
}
