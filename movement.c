/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:55:39 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/25 14:39:15 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision(t_player *player, int keycode, char **map)
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;

	posx = player->posx;
	posy = player->posy;
	dirx = player->dirx;
	diry = player->diry;
	if (keycode == S && map[(int)(posy - diry)][(int)(posx - dirx)] == '1')
		return (1);
	else if (keycode == W && map[(int)(posy + diry)][(int)(posx + dirx)] == '1')
		return (1);
	else if (keycode == D && map[(int)(posy + dirx)][(int)(posx - diry)] == '1')
		return (1);
	else if (keycode == A && map[(int)(posy - dirx)][(int)(posx + diry)] == '1')
		return (1);
	return (0);
}

void	handle_movement(int keycode, t_game *game)
{
	if (keycode == S)
	{
		game->player->posx -= game->player->dirx;
		game->player->posy -= game->player->diry;
	}
	if (keycode == W)
	{
		game->player->posx += game->player->dirx;
		game->player->posy += game->player->diry;
	}
	if (keycode == D)
	{
		game->player->posx -= game->player->diry;
		game->player->posy += game->player->dirx;
	}
	if (keycode == A)
	{
		game->player->posx += game->player->diry;
		game->player->posy -= game->player->dirx;
	}
}

void	handle_rotation(int keycode, t_game *game)
{
	double	olddirx;
	double	oldplanex;
	double	rot_speed;

	if (keycode == LEFT)
		rot_speed = -ROT_SPEED;
	else
		rot_speed = ROT_SPEED;
	olddirx = game->player->dirx;
	game->player->dirx = game->player->dirx * cos(rot_speed)
		- game->player->diry * sin(rot_speed);
	game->player->diry = olddirx * sin(rot_speed)
		+ game->player->diry * cos(rot_speed);
	oldplanex = game->player->planex;
	game->player->planex = game->player->planex * cos(rot_speed)
		- game->player->planey * sin(rot_speed);
	game->player->planey = oldplanex * sin(rot_speed)
		+ game->player->planey * cos(rot_speed);
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!check_collision(game->player, keycode, game->map))
		handle_movement(keycode, game);
	if (keycode == LEFT || keycode == RIGHT)
		handle_rotation(keycode, game);
	if (keycode == ESC)
		handle_exit(game);
	cast_rays(game, game->player);
	return (0);
}
