/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:40:24 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/29 19:46:22 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_identifier_format(const char *line)
{
	const char	*valid_ids[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int i;
	int len;

	i = 0;
	while (valid_ids[i])
	{
		len = ft_strlen(valid_ids[i]);
		if (ft_strncmp(line, valid_ids[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char *trim_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static int is_valid_line(char *line, t_game *game)
{
	char *trimmed;

	trimmed = trim_whitespace(line);
	if (trimmed[0] == '1' || trimmed[0] == ' ')
		return (1);
	if (trimmed[0] == '\n' || ft_strlen(trimmed) <= 0)
		return (1);

	if (!is_valid_identifier_format(trimmed))
	{
		perror("Error\nInvalid identifier format in map file\n");
		handle_exit(game);
	}
	return (1);
}

void process_ceiling_color(char *line, t_game *game)
{
	printf("Processing ceiling color: %s", line);
	if (!parse_color(line, &game->ceiling_color))
	{
		perror("Error: Invalid ceiling color format\n");
		free(line);
		exit(1);
	}
}

void process_map_line(char *line, char **map_arr, int *i)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map_arr[*i] = ft_strdup(line);
	printf("Map line %d: %s\n", *i, map_arr[*i]);
	(*i)++;
}

static void process_texture_line(char *line, t_game *game)
{
	if (!line || !game)
	{
		perror("Invalid line or game pointer\n");
		return;
	}
	if (!parse_texture_paths(game, trim_whitespace(line)))
		handle_exit(game);
}

void process_line(char *line, t_game *game, char **map_arr, int *i)
{
	if (!is_valid_line(line, game))
		return;
	if (ft_strlen(line) <= 0 || line[0] == '\n')
		return;
	if (check_texture_duplicate(line, game))
		process_texture_line(line, game);
	else if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
			 ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		perror("Error\nInvalid texture format\n");
		handle_exit(game);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
		process_ceiling_color(line, game);
	else if (line[0] == ' ' || line[0] == '1')
		process_map_line(line, map_arr, i);
	else if (ft_strncmp(line, "F ", 2) == 0 &&
			 !parse_color(line, &game->floor_color))
	{
		perror("Error\nInvalid floor color format\n");
		handle_exit(game);
	}
}
