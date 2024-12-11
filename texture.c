/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:45 by gverissi          #+#    #+#             */
/*   Updated: 2024/12/11 18:43:05 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

static char	*trim_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n' || str[len - 1] == '\r'))
		str[--len] = '\0';
	return (str);
}

static char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	check_texture_duplicate(char *line, t_game *game)
{
	static t_tex_check	textures[] = {
	{"NO", 0},
	{"SO", 0},
	{"WE", 0},
	{"EA", 0}};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(skip_whitespace(line), textures[i].id, 2) == 0)
		{
			if (++textures[i].count > 1)
			{
				perror("Error\nDuplicate texture\n");
				free(line);
				handle_exit(game);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static int	has_duplicate_texture(t_game *game, const char *identifier)
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

t_tex	*init_textures(void *mlx_ptr)
{
	t_tex	*tex;

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

void	init_clean_path(t_game *game, char **split)
{
	char	*clean_path;

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

int	parse_texture_paths(t_game *game, char *line)
{
	char	*id;
	char	*path;
	char	**split;

	split = malloc(sizeof(char *) * 2);
	id = ft_strdup(line);
	id[2] = '\0';
	split[0] = id;
	path = skip_whitespace(line + 2);
	split[1] = trim_end(ft_strdup(path));
	if (has_duplicate_texture(game, split[0]))
	{
		free(split[0]);
		free(split[1]);
		free(split);
		return (0);
	}
	init_clean_path(game, split);
	free(split[0]);
	free(split[1]);
	free(split);
	return (1);
}
