/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:48:34 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 14:15:06 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_helper(t_game *game, t_player *player, int i, int j)
{
	if (game->map[i][j] == 'N')
	{
		player->dirx = 0 + OFFSET;
		player->diry = -1 + OFFSET;
	}
	else if (game->map[i][j] == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
	}
	else if (game->map[i][j] == 'W')
	{
		player->dirx = -1 + OFFSET;
		player->diry = 0 + OFFSET;
	}
	else if (game->map[i][j] == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
	}
}

void	init_player(t_game *game, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (game && game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'W' ||
				game->map[i][j] == 'S' || game->map[i][j] == 'E')
			{
				player->posx = j;
				player->posy = i;
				init_player_helper(game, player, i, j);
			}
			j++;
		}
		i++;
	}
	player->planex = player->diry * -1 * FOV;
	player->planey = player->dirx * FOV;
}

int	init_window(t_win *win)
{
	win->width = 1280;
	win->height = 768;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return (0);
	win->win_ptr = mlx_new_window(win->mlx_ptr,
			win->width, win->height, "Cub3D");
	return (1);
}
