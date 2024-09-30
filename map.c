/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:44:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/09/20 20:42:03 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//assuming gnl doesnt skip spaces lol
void	open_map(char *path, t_game *game)
{
	char	**map_arr;
	int		map_fd;
	char	*map_temp;
	char	*line_temp;
	int		i;
	int		j;
	int		rows;

	map_arr = NULL;
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
	{
		write(1, "Error\nFile not found\n", 22);
		return ;
	}
	rows = 0;
	while (get_next_line(map_fd))
		rows++;
	map_arr = malloc(sizeof(char *) * (rows + 1));
	if (!map_arr)
		return ;
	close(map_fd);
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
	{
		write(1, "Error\nFile not found\n", 22);
		return ;
	}
	i = 0;
	while (1)
	{
		j = 0;
		line_temp = get_next_line(map_fd);
		if (!line_temp)
			break ;
		while (line_temp[j])
			j++;
		if (line_temp[j - 1] == '\n')
			line_temp[j - 1] = '\0';
		map_arr[i] = line_temp;
		i++;
	}
	map_arr[i] = NULL;
	game->map = map_arr;
	if (!check_enclosed(map_arr))
	{
		printf("map not enclosed\n");
		exit (1);
	}
}

