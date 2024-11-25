/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:14 by gverissi          #+#    #+#             */
/*   Updated: 2024/11/25 15:32:16 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_free(char **map_arr)
{
	int	i;

	i = 0;
	if (map_arr)
	{
		while (map_arr[i])
		{
			free(map_arr[i]);
			i++;
		}
		free(map_arr);
	}
}

void	destroy_textures(t_img *tex, t_game *game)
{
	if (tex->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, tex->img_ptr);
	free(tex);
}

void	free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

//mlx_destroy_display needs to be commented
//for it to run on a mac bc minilibx_opengl
//doesn't support that function
void	cleanup_game(t_game *game)
{
	free_map(game);
	if (game->wall && game->wall->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, game->wall->img_ptr);
	if (game->bgd && game->bgd->img_ptr)
		mlx_destroy_image(game->win->mlx_ptr, game->bgd->img_ptr);
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

int	handle_exit(t_game *game)
{
	if (game->textures)
	{
		if (game->textures->north)
			destroy_textures(game->textures->north, game);
		if (game->textures->south)
			destroy_textures(game->textures->south, game);
		if (game->textures->east)
			destroy_textures(game->textures->east, game);
		if (game->textures->west)
			destroy_textures(game->textures->west, game);
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
	cleanup_game(game);
	exit(0);
	return (0);
}
