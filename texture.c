/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:45 by gverissi          #+#    #+#             */
/*   Updated: 2024/11/25 15:30:23 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture_duplicate(char *line, t_game *game)
{
    static t_tex_check textures[] = {
        {"NO ", 0},
        {"SO ", 0},
        {"WE ", 0},
        {"EA ", 0}
    };
    int i;

    i = 0;
    while (i < 4)
    {
        if (ft_strncmp(line, textures[i].id, 3) == 0)
        {
            if (++textures[i].count > 1)
            {
                printf("Error\nDuplicate %s texture\n", textures[i].id);
                handle_exit(game);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

static int has_duplicate_texture(t_game *game, const char *identifier)
{
	if (ft_strncmp(identifier, "NO", 3) == 0 && game->textures->north_path)
		return (1);
	if (ft_strncmp(identifier, "SO", 3) == 0 && game->textures->south_path)
		return (1);
	if (ft_strncmp(identifier, "EA", 3) == 0 && game->textures->east_path)
		return (1);
	if (ft_strncmp(identifier, "WE", 3) == 0 && game->textures->west_path)
		return (1);
	return (0);
}

t_tex *init_textures(void *mlx_ptr)
{
	t_tex *tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
	{
		printf("Failed to malloc tex structure\n");
		return (NULL);
	}
	tex->north = ft_calloc(1, sizeof(t_img));
	tex->south = ft_calloc(1, sizeof(t_img));
	tex->east = ft_calloc(1, sizeof(t_img));
	tex->west = ft_calloc(1, sizeof(t_img));
	if (!tex->north || !tex->south || !tex->east || !tex->west)
	{
		perror("Failed to malloc individual texture structures\n");
		return (NULL);
	}
	tex->north_path = NULL;
	tex->south_path = NULL;
	tex->east_path = NULL;
	tex->west_path = NULL;
	printf("Texture initialization complete\n");
	return (tex);
}

void init_clean_path(t_game *game, char **split)
{
	char *clean_path;

	clean_path = ft_strdup(split[1]);
	if (ft_strncmp(split[0], "NO", 3) == 0)
		game->textures->north_path = clean_path;
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		game->textures->south_path = clean_path;
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		game->textures->east_path = clean_path;
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		game->textures->west_path = clean_path;
	else
		free(clean_path);
}

int parse_texture_paths(t_game *game, char *line)
{
	char **split;
	int len;
	int i;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	if (!split[1] || has_duplicate_texture(game, split[0]))
	{
		perror("Error\nInvalid or duplicate texture configuration\n");
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	len = ft_strlen(split[1]);
	while (len > 0 && (split[1][len - 1] == '\n' ||
					   split[1][len - 1] == ' ' || split[1][len - 1] == '\r'))
	{
		split[1][len - 1] = '\0';
		len--;
	}
	init_clean_path(game, split);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (1);
}