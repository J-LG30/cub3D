/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:15:54 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/25 15:18:55 by jle-goff         ###   ########.fr       */
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

int	draw_floor(t_game *game)
{
	int	floor_color;
	int	x;
	int	y;

	floor_color = (game->floor_color.r << 16)
		| (game->floor_color.g << 8)
		| game->floor_color.b;
	if (!game->wall || !game->wall->img_ptr)
		return (1);
	y = game->win->height / 2;
	while (y < game->win->height)
	{
		x = 0;
		while (x < game->win->width)
		{
			my_mlx_pixel_put(game->wall, x, y, floor_color);
			x++;
		}
		y++;
	}
	return (0);
}


int	draw_ceiling(t_game *game)
{
	int	ceiling_color;
	int	y;
	int	x;

	ceiling_color = (game->ceiling_color.r << 16)
		| (game->ceiling_color.g << 8)
		| game->ceiling_color.b;
	if (!game->wall || !game->wall->img_ptr)
		return (1);
	y = 0;
	while (y < game->win->height / 2)
	{
		x = 0;
		while (x < game->win->width)
		{
			my_mlx_pixel_put(game->wall, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	return (0);
}