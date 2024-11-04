/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:44:34 by rafasant          #+#    #+#             */
/*   Updated: 2024/09/30 11:50:34 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void count_rows(char *path, int *rows, int *texture_lines)
{
    int     fd;
    char    *line;

    *rows = 0;
    *texture_lines = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return;
    while ((line = get_next_line(fd)))
    {
        if (is_texture_line(line))
            (*texture_lines)++;
        else if (ft_strlen(line) > 1)  // Skip empty lines
            (*rows)++;
        free(line);
    }
    close(fd);
}
#include "cub3d.h"
#include "cub3d.h"

static void process_texture_line(char *line, t_game *game)
{
    printf("\nProcessing texture line: %s", line);
    if (!line || !game)
    {
        printf("Invalid line or game pointer\n");
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

    printf("\n--- Starting map opening process ---\n");
    printf("Opening map file: %s\n", path);
    
    // First pass: count rows and textures
    rows = 0;
    texture_count = 0;
    map_fd = open(path, O_RDONLY);
    if (map_fd < 0)
    {
        printf("Failed to open map file!\n");
        exit(1);
    }

    printf("Counting rows and textures...\n");
    while ((line = get_next_line(map_fd)))
    {
        if (ft_strlen(line) > 0 && line[0] != '\n')
        {
            if (texture_count < 4 && (ft_strncmp(line, "NO ", 3) == 0 || 
                ft_strncmp(line, "SO ", 3) == 0 || 
                ft_strncmp(line, "WE ", 3) == 0 || 
                ft_strncmp(line, "EA ", 3) == 0))
            {
                texture_count++;
                printf("Found texture line #%d: %s", texture_count, line);
            }
            else
                rows++;
        }
        free(line);
    }
    close(map_fd);
    
    printf("Found %d texture lines and %d map rows\n", texture_count, rows);

    printf("Allocating map array...\n");
    map_arr = malloc(sizeof(char *) * (rows + 1));
    if (!map_arr)
    {
        printf("Failed to allocate map array!\n");
        return;
    }

    printf("Reading map content...\n");
    map_fd = open(path, O_RDONLY);
    i = 0;
    texture_count = 0;
    while ((line = get_next_line(map_fd)))
    {
        if (ft_strlen(line) > 0 && line[0] != '\n')
        {
            if (texture_count < 4 && (ft_strncmp(line, "NO ", 3) == 0 || 
                ft_strncmp(line, "SO ", 3) == 0 || 
                ft_strncmp(line, "WE ", 3) == 0 || 
                ft_strncmp(line, "EA ", 3) == 0))
            {
                process_texture_line(line, game);
                texture_count++;
            }
            else
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
        printf("Error: Map not enclosed!\n");
        exit(1);
    }
    if (!check_player(map_arr))
    {
        printf("Error: Invalid player configuration!\n");
        exit(1);
    }
    if (!check_all_valid_char(map_arr))
    {
        printf("Error: Invalid character in map!\n");
        exit(1);
    }
    printf("Map validation complete\n");
    printf("--- Map opening process complete ---\n\n");
}