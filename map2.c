/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:40:24 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 12:26:52 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_floor_color(char *line, t_game *game)
{
	printf("FLOOR LINE: %s\n", line);
	if (game->parsed_map)
	{
		perror("Map not last in file\n");
		free(line);
		handle_exit(game);
	}
	printf("Processing floor color: %s\n", line);
	if (!parse_color(line, &game->floor_color))
	{
		perror("Error\nInvalid floor color format\n");
		free(line);
		handle_exit(game);
	}
}

void	process_ceiling_color(char *line, t_game *game)
{
	printf("CEILING LINE: %s\n", line);
	if (game->parsed_map)
	{
		perror("Map not last in file\n");
		free(line);
		handle_exit(game);
	}
	printf("Processing ceiling color: %s\n", line);
	if (!parse_color(line, &game->ceiling_color))
	{
		perror("Error: Invalid ceiling color format\n");
		free(line);
		handle_exit(game);
	}
}

//choosing how to handle empty spaces in map
void	process_map_line(char *line, char **map_arr, int *i, t_game *game)
{
	int	j;

	game->parsed_map = 1;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map_arr[*i] = ft_strdup(skip_whitespace(line));
	j = 0;
	while (map_arr[*i][j])
	{
		if (map_arr[*i][j] == ' ' || map_arr[*i][j] == '\t')
			map_arr[*i][j] = '0';
		j++;
	}
	printf("Map line %d: %s\n", *i, map_arr[*i]);
	(*i)++;
}

static void	process_texture_line(char *line, t_game *game)
{
	if (game->parsed_map)
	{
		perror("Map not last in file\n");
		free(line);
		handle_exit(game);
	}
	if (!line || !game)
	{
		perror("Invalid line or game pointer\n");
		return ;
	}
	if (!parse_texture_paths(game, skip_whitespace(line)))
	{
		handle_exit(game);
	}
}

void	process_line(char *line, t_game *game, char **map_arr, int *i)
{
	if (!is_valid_line(line, game))
		return ;
	if (ft_strlen(line) <= 0 || line[0] == '\n')
		return ;
	if (check_texture_duplicate(line, game))
		process_texture_line(line, game);
	else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		perror("Error\nInvalid texture format\n");
		free(line);
		handle_exit(game);
	}
	else if (ft_strncmp(skip_whitespace(line), "C ", 2) == 0)
		process_ceiling_color(line, game);
	else if (ft_strncmp(skip_whitespace(line), "F ", 2) == 0)
		process_floor_color(line, game);
	else if (line[0] == ' ' || line[0] == '1')
		process_map_line(line, map_arr, i, game);
}
