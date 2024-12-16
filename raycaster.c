/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:23:16 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 10:55:08 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rayval_helper(t_player *player, t_rayval *rval)
{
	if (rval->raydirx < 0)
	{
		rval->stepx = -1;
		rval->sidedistx = (player->posx - rval->mapx) * rval->deltadistx;
	}
	else
	{
		rval->stepx = 1;
		rval->sidedistx = (rval->mapx + 1.0 - player->posx) * rval->deltadistx;
	}
	if (rval->raydiry < 0)
	{
		rval->stepy = -1;
		rval->sidedisty = (player->posy - rval->mapy) * rval->deltadisty;
	}
	else
	{
		rval->stepy = 1;
		rval->sidedisty = (rval->mapy + 1.0 - player->posy) * rval->deltadisty;
	}
}

t_rayval	*init_rayval(t_game *game, t_player *player, int i)
{
	t_rayval	*rval;

	rval = malloc(sizeof(t_rayval));
	if (!rval)
		return (NULL);
	rval->mapx = (int)player->posx;
	rval->mapy = (int)player->posy;
	rval->camerax = (2 * i) / (float)game->win->width - 1;
	rval->raydirx = player->dirx + (player->planex * rval->camerax);
	rval->raydiry = player->diry + (player->planey * rval->camerax);
	if (rval->raydirx == 0)
		rval->deltadistx = 1e30;
	else
		rval->deltadistx = sqrt(1 + (rval->raydiry * rval->raydiry) / (rval->raydirx * rval->raydirx));
	if (rval->raydiry == 0)
		rval->deltadisty = 1e30;
	else
		rval->deltadisty = sqrt(1 + (rval->raydirx * rval->raydirx) / (rval->raydiry * rval->raydiry));
	init_rayval_helper(player, rval);
	return (rval);
}

void	calculate_wall_distance(t_rayval *rval, t_player *player)
{
	 if (rval->side == 0)
	 {
		if (rval->stepx == -1)
        	rval->perpwalldist = (rval->mapx - player->posx + 1) / rval->raydirx;
		else
			rval->perpwalldist = (rval->mapx - player->posx) / rval->raydirx;
	}
    else
	{
		if (rval->stepy == -1)
			rval->perpwalldist = (rval->mapy - player->posy + 1) / rval->raydiry;
		else
			rval->perpwalldist = (rval->mapy - player->posy) / rval->raydiry;
	}
}

void	perform_dda(t_game *game, t_rayval *rval)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (rval->sidedistx < rval->sidedisty)
		{
			rval->sidedistx += rval->deltadistx;
			rval->mapx += rval->stepx;
			side = 0;
		}
		else
		{
			rval->sidedisty += rval->deltadisty;
			rval->mapy += rval->stepy;
			side = 1;
		}
		if (game->map[rval->mapy][rval->mapx] == '1')
			hit = 1;
	}
	rval->side = side;
}

//clear_image(game->wall, 0x00000000);
void	cast_rays(t_game *game, t_player *player)
{
	int			i;
	t_rayval	*rval;

	if (draw_floor(game) || draw_ceiling(game))
		return ;
	i = 0;
	while (i < game->win->width)
	{
		rval = init_rayval(game, player, i);
		if (!rval)
			return ;
		perform_dda(game, rval);
		calculate_wall_distance(rval, player);
		draw_wall(game, player, rval, i);
		free(rval);
		i++;
	}
	mlx_put_image_to_window(game->win->mlx_ptr,
		game->win->win_ptr, game->bgd->img_ptr, 0, 0);
	mlx_put_image_to_window(game->win->mlx_ptr,
		game->win->win_ptr, game->wall->img_ptr, 0, 0);
}
