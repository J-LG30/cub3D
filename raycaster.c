/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:23:16 by jle-goff          #+#    #+#             */
/*   Updated: 2024/10/02 15:57:03 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *data, int colour)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->w)
	{
		j = 0;
		while (j < data->h)
		{
			my_mlx_pixel_put(data, i, j, colour);
			j++;
		}
		i++;
	}
}

void	cast_rays(t_game *game, t_player *player)
{
	double	raydirX;
	double	raydirY;
	double	posX;
	double	posY;
	double	x_next;
	double	y_next;
	double	cameraX;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		i;
	int		mapX;
	int		mapY;
	int		hit;
	int		side; // 0 meaning vertical wall hit and 1 meaning horizontal wall
	int		endrayX;
	int		endrayY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	
	raydirX = player->dirX;
	raydirY = player->dirY;
	posX = player->posX;
	posY = player->posY;
	i = 0;
	
	clear_image(game->wall, 0x00000000);
	while (i < game->win->width)
	{
		stepX = 0;
		stepY = 0;
		mapX = (int)posX;
		mapY = (int)posY;
		cameraX = (2 * i) / (float)game->win->width - 1;
		raydirX = player->dirX + (player->planeX * cameraX);
		raydirY = player->dirY + (player->planeY * cameraX);
		perpWallDist = 0;
		
		if (raydirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / raydirX); // long drawn out explanation need to write in notes
		if (raydirY == 0)
			deltaDistX = 1e30;
		else
			deltaDistY = fabs(1 / raydirY);
		if (raydirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (raydirY < 0) //ray moving upwards
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else// ray moving downwards
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		hit = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map[mapY][mapX] == '1')
			{
				hit = 1;
			}
		}
		//used to be:
		if (side == 0)
		{
			perpWallDist = sideDistX - deltaDistX;
		}		
		else
		{
			perpWallDist = sideDistY - deltaDistY;
		}
		
		lineHeight = game->win->height / perpWallDist;
		drawStart = game->win->height / 2 - (lineHeight / 2);
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = game->win->height / 2 + (lineHeight / 2);
		if (drawEnd >= game->win->height)
			drawEnd = game->win->height;
		if (side == 0)
			draw_line(game, i, drawStart, drawEnd, 0x000FF000);
		else
			draw_line(game, i, drawStart, drawEnd, 0x000000FF);
		i++;
	}
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->bgd->img_ptr, 0, 0);
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->wall->img_ptr, 0, 0);
}
