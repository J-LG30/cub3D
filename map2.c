/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:40:24 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/22 17:44:34 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_ceiling_color(char *line, t_game *game)
{
	printf("Processing ceiling color: %s", line);
	if (!parse_color(line, &game->ceiling_color))
	{
		printf("Error: Invalid ceiling color format\n");
		free(line);
		exit(1);
	}
}

void	process_map_line(char *line, char **map_arr, int *i)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map_arr[*i] = ft_strdup(line);
	printf("Map line %d: %s\n", *i, map_arr[*i]);
	(*i)++;
}

static void	process_texture_line(char *line, t_game *game)
{
	if (!line || !game)
	{
		perror("Invalid line or game pointer\n");
		return ;
	}
	parse_texture_paths(game, line);
}

void	process_line(char *line, t_game *game, char **map_arr, int *i)
{
	if (ft_strlen(line) > 0 && line[0] != '\n')
	{
		if (game->textures->tex_count < 4 && (ft_strncmp(line, "NO ", 3) == 0
				|| ft_strncmp(line, "SO ", 3) == 0
				|| ft_strncmp(line, "WE ", 3) == 0
				|| ft_strncmp(line, "EA ", 3) == 0))
		{
			process_texture_line(line, game);
			game->textures->tex_count++;
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!parse_color(line, &game->floor_color))
			{
				printf("Error: Invalid floor color format\n");
				free(line);
				exit(1);
			}
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
			process_ceiling_color(line, game);
		else if (line[0] == ' ' || line[0] == '1')
			process_map_line(line, map_arr, i);
	}
}
