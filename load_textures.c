/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:25:27 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/25 15:31:28 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_paths(t_game *game)
{
	if (!game->textures->north_path || !game->textures->south_path
		|| !game->textures->east_path || !game->textures->west_path)
	{
		perror("Error: Missing texture paths\n");
		handle_exit(game);
	}
}

void	load_texture(t_game *game, t_img *texture, char *path, char *direction)
{
	printf("\nLoading %s texture...\n", direction);
	texture->img_ptr = mlx_xpm_file_to_image(game->win->mlx_ptr,
			path, &texture->w, &texture->h);
	if (!texture->img_ptr)
	{
		perror("Failed to load texture!\n");
		handle_exit(game);
	}
	else
	{
		printf("%s texture loaded, getting address...\n", direction);
		texture->addr = mlx_get_data_addr(texture->img_ptr,
				&texture->bpp, &texture->line_len, &texture->endian);
	}
}

void	load_textures(t_game *game)
{
	printf("\nAttempting to load textures...\n");
	printf("North path: '%s'\n", game->textures->north_path);
	printf("South path: '%s'\n", game->textures->south_path);
	printf("East path: '%s'\n", game->textures->east_path);
	printf("West path: '%s'\n", game->textures->west_path);
	check_texture_paths(game);
	load_texture(game, game->textures->north,
		game->textures->north_path, "North");
	load_texture(game, game->textures->south,
		game->textures->south_path, "South");
	load_texture(game, game->textures->east, game->textures->east_path, "East");
	load_texture(game, game->textures->west, game->textures->west_path, "West");
	printf("--- Texture loading complete ---\n\n");
}
