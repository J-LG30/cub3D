/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:55:41 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/11 18:36:41 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(t_game *game, t_img *texture, int x, t_rayval *rval)
{
	double	step;
	int		y;
	char	*tex_pixel;
	int		color;

	y = rval->drawstart;
	step = 1.0 * TEX_HEIGHT / rval->lineheight;
	rval->tex_pos = (rval->drawstart - game->win->height / 2
			+ rval->lineheight / 2) * step;
	while (y < rval->drawend)
	{
		rval->tex_y = (int)rval->tex_pos & (TEX_HEIGHT - 1);
		rval->tex_pos += step;
		tex_pixel = texture->addr + (rval->tex_y * texture->line_len
				+ rval->tex_x * (texture->bpp / 8));
		color = *(unsigned int *)tex_pixel;
		if (rval->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(game->wall, x, y, color);
		y++;
	}
}

t_img	*get_texture(t_game *game, t_rayval *rval)
{
	if (rval->side == 0)
	{
		if (rval->raydirx > 0)
			return (game->textures->east);
		else
			return (game->textures->west);
	}
	else
	{
		if (rval->raydiry > 0)
			return (game->textures->south);
		else
			return (game->textures->north);
	}
}

void	draw_wall(t_game *game, t_player *player, t_rayval *rval, int x)
{
	t_img	*current_texture;

	rval->lineheight = (int)(game->win->height / rval->perpwalldist);
	rval->drawstart = -(rval->lineheight) / 2 + game->win->height / 2;
	rval->drawend = rval->lineheight / 2 + game->win->height / 2;
	if (rval->drawstart < 0)
		rval->drawstart = 0;
	if (rval->drawend >= game->win->height)
		rval->drawend = game->win->height - 1;
	if (rval->side == 0)
		rval->wall_x = player->posy + rval->perpwalldist * rval->raydiry;
	else
		rval->wall_x = player->posx + rval->perpwalldist * rval->raydirx;
	rval->wall_x -= floor(rval->wall_x);
	current_texture = get_texture(game, rval);
	rval->tex_x = (int)(rval->wall_x * current_texture->w);
	rval->tex_x = rval->tex_x % current_texture->w;
	if (rval->side == 0 && rval->raydirx > 0)
		rval->tex_x = current_texture->w - rval->tex_x - 1;
	if (rval->side == 1 && rval->raydiry < 0)
		rval->tex_x = current_texture->w - rval->tex_x - 1;
	draw_texture(game, current_texture, x, rval);
}
