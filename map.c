/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:44:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/11/29 16:29:47 by jle-goff         ###   ########.fr       */
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
		if (line[0] == ' ' || line[0] == '1')
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

	map_arr = malloc(sizeof(char *) * (rows + 1));
	if (!map_arr)
	{
		perror("Failed to allocate map array!\n");
		return (NULL);
	}
	return (map_arr);
}

void	validate_map(t_game *game, char **map_arr)
{
	printf("\nValidating map...\n");
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
	printf("Map validation complete\n");
}

int	read_map_file(char *path, t_game *game, char **map_arr)
{
	int		map_fd;
	char	*line;
	int		i;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		return (0);
	i = 0;
	game->textures->tex_count = 0;
	line = get_next_line(map_fd);
	while (line)
	{
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

	rows = count_map_rows(path);
	if (rows == -1)
		handle_exit(game);
	map_arr = allocate_map_array(rows);
	if (!map_arr)
	{
		perror("Failed to allocate map array!\n");
		return ;
	}
	if (!read_map_file(path, game, map_arr))
	{
		perror("Map error: ");
		map_free(map_arr);
		return ;
	}
	game->map = map_arr;
	validate_map(game, map_arr);
	printf("--- Map opening process complete ---\n\n");
}
