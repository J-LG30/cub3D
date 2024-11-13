/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:44:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/11/13 16:29:28 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void count_rows(char *path, int *rows, int *texture_lines)
{
	int     fd;
    char	*line;

    *rows = 0;
    *texture_lines = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return;
    while ((line = get_next_line(fd)))
    {
        if (is_texture_line(line))
            (*texture_lines)++;
        else if (ft_strlen(line) > 1)
            (*rows)++;
        free(line);
    }
    close(fd);
}


static void process_texture_line(char *line, t_game *game)
{
    if (!line || !game)
    {
        perror("Invalid line or game pointer\n");
        return;
    }
    parse_texture_paths(game, line);
}

void open_map(char *path, t_game *game)
{
    char    **map_arr;
    int     map_fd;
    char    *line;
    int     i;
    int     rows;
    int     texture_count;

    rows = 0;
    map_fd = open(path, O_RDONLY);
    while ((line = get_next_line(map_fd)))
    {
        if (line[0] == ' ' || line[0] == '1')
            rows++;
        free(line);
    }
    close(map_fd);

    map_arr = malloc(sizeof(char *) * (rows + 1));
    if (!map_arr)
    {
        perror("Failed to allocate map array!\n");
        return;
    }

    map_fd = open(path, O_RDONLY);
    i = 0;
    texture_count = 0;
	//uh uh, looks like we'll need to separate the whole shite
    while ((line = get_next_line(map_fd)))
    {
        if (ft_strlen(line) > 0 && line[0] != '\n')
        {
            // Process textures
            if (texture_count < 4 && (ft_strncmp(line, "NO ", 3) == 0 || 
                ft_strncmp(line, "SO ", 3) == 0 || 
                ft_strncmp(line, "WE ", 3) == 0 || 
                ft_strncmp(line, "EA ", 3) == 0))
            {
                process_texture_line(line, game);
                texture_count++;
            }
            // Process colors
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
            {
                printf("Processing ceiling color: %s", line);
                if (!parse_color(line, &game->ceiling_color))
                {
                    printf("Error: Invalid ceiling color format\n");
                    free(line);
                    exit(1);
                }
            }
            // Process map lines
            else if (line[0] == ' ' || line[0] == '1')
            {
                if (line[ft_strlen(line) - 1] == '\n')
                    line[ft_strlen(line) - 1] = '\0';
                map_arr[i] = ft_strdup(line);
                printf("Map line %d: %s\n", i, map_arr[i]);
                i++;
            }
        }
        free(line);
    }
    map_arr[i] = NULL;
    game->map = map_arr;
    close(map_fd);

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
    printf("--- Map opening process complete ---\n\n");
}