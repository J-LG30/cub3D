/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:44:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/12/17 18:01:46 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// while ((line = get_next_line(fd)))
	// {
	// 	if (is_texture_line(line))
	// 		(*texture_lines)++;
	// 	else if (ft_strlen(line) > 1)
	// 		(*rows)++;
	// 	free(line);
	// }
// static void	count_rows(char *path, int *rows, int *texture_lines)
// {
// 	int		fd;
// 	char	*line;

// 	*rows = 0;
// 	*texture_lines = 0;
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return ;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (is_texture_line(line))
// 			(*texture_lines)++;
// 		else if (ft_strlen(line) > 1)
// 			(*rows)++;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }

int	count_map_rows(char *path)
{
	int		map_fd;
	char	*line;
	int		rows;

	rows = 0;
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
	{
		perror("Error ");
		return (-1);
	}
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '\t')
			rows++;
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (rows);
}

char	**allocate_map_array(int rows)
{
	char	**map_arr;

	map_arr = ft_calloc(sizeof(char *), (rows + 1));
	if (!map_arr)
	{
		perror("Failed to allocate map array!\n");
		return (NULL);
	}
	return (map_arr);
}

void	validate_map(t_game *game, char **map_arr)
{
	if (!game->parsed_ceiling || !game->parsed_floor)
	{
		perror("Missing floor or celing colour!\n");
		handle_exit(game);
	}
	if (!check_enclosed(map_arr))
	{
		perror("Error: Map not enclosed!\n");
		handle_exit(game);
	}
	if (!check_player(map_arr))
	{
		perror("Error: Invalid player configuration!\n");
		handle_exit(game);
	}
	if (!check_all_valid_char(map_arr))
	{
		perror("Error: Invalid character in map!\n");
		handle_exit(game);
	}
}

int	read_map_file(char *path, t_game *game, char **map_arr)
{
	int		map_fd;
	char	*line;
	int		i;
	int		j;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (0);
	i = 0;
	game->textures->tex_count = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		game->map[i] = NULL;
		process_line(line, game, map_arr, &i);
		free(line);
		line = get_next_line(map_fd);
	}
	map_arr[i] = NULL;
	close(map_fd);
	return (1);
}

void	open_map(char *path, t_game *game)
{
	char	**map_arr;
	int		rows;

	game->map = NULL;
	rows = count_map_rows(path);
	if (rows == -1)
		handle_exit(game);
	map_arr = allocate_map_array(rows);
	if (!map_arr)
	{
		perror("Failed to allocate map array!\n");
		return ;
	}
	game->map = map_arr;
	if (!read_map_file(path, game, map_arr) || !map_arr || !map_arr[0])
	{
		perror("Unable to parse map");
		handle_exit(game);
	}
	validate_map(game, map_arr);
}
