/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:14 by gverissi          #+#    #+#             */
/*   Updated: 2024/11/13 16:05:10 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void cleanup_game(t_game *game)
{
	if (game->textures)
	{
		if (game->textures->north)
		{
			if (game->textures->north->img_ptr)
				mlx_destroy_image(game->win->mlx_ptr, game->textures->north->img_ptr);
			free(game->textures->north);
		}
		if (game->textures->south)
		{
			if (game->textures->south->img_ptr)
				mlx_destroy_image(game->win->mlx_ptr, game->textures->south->img_ptr);
			free(game->textures->south);
		}
		if (game->textures->east)
		{
			if (game->textures->east->img_ptr)
				mlx_destroy_image(game->win->mlx_ptr, game->textures->east->img_ptr);
			free(game->textures->east);
		}
		if (game->textures->west)
		{
			if (game->textures->west->img_ptr)
				mlx_destroy_image(game->win->mlx_ptr, game->textures->west->img_ptr);
			free(game->textures->west);
		}

		if (game->textures->north_path)
			free(game->textures->north_path);
		if (game->textures->south_path)
			free(game->textures->south_path);
		if (game->textures->east_path)
			free(game->textures->east_path);
		if (game->textures->west_path)
			free(game->textures->west_path);
		free(game->textures);
	}

	if (game->map)
	{
		int i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}

	if (game->wall && game->wall->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, game->wall->img_ptr);
	if (game->bgd && game->bgd->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, game->bgd->img_ptr);
	if (game->player && game->player->img && game->player->img->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, game->player->img->img_ptr);

	if (game->win)
	{
		if (game->win->win_ptr)
			mlx_destroy_window(game->win->mlx_ptr, game->win->win_ptr);
        if (game->win->mlx_ptr)
        {
            mlx_destroy_display(game->win->mlx_ptr);
            free(game->win->mlx_ptr);
        }
    }
}

int handle_exit(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}