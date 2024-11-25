/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:58:24 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/22 16:00:25 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	new_sprite(void *mlx, int width, int height)
{
	t_img	image;

	image.img_ptr = mlx_new_image(mlx, width, height);
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
			&image.line_len, &image.endian);
	image.w = width;
	image.h = height;
	return (image);
}

t_img	new_xpm_sprite(void *mlx, char *path)
{
	t_img	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.w, &image.h);
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
			&image.line_len, &image.endian);
	return (image);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = colour;
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
