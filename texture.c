/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:45 by gverissi          #+#    #+#             */
/*   Updated: 2024/11/13 16:37:46 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

    printf("Setting texture paths to NULL...\n");
    tex->north_path = NULL;
    tex->south_path = NULL;
    tex->east_path = NULL;
    tex->west_path = NULL;
    
    printf("Texture initialization complete\n");
    return (tex);
}

int parse_texture_paths(t_game *game, char *line)
{
    char **split;
    char *clean_path;
    int len;
    int i;
    split = ft_split(line, ' ');
    if (!split)
        return (0);

    if (!split[1])
    {
        perror("Error: Missing texture path\n");
        return (0);
    }

    len = ft_strlen(split[1]);
    while (len > 0 && (split[1][len - 1] == '\n' ||\
    split[1][len - 1] == ' ' || split[1][len - 1] == '\r'))
    {
        split[1][len - 1] = '\0';
        len--;
    }
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
    
    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
    
    return (1);
}

void load_textures(t_game *game)
{
    printf("\nAttempting to load textures...\n");
    printf("North path: '%s'\n", game->textures->north_path);
    printf("South path: '%s'\n", game->textures->south_path);
    printf("East path: '%s'\n", game->textures->east_path);
    printf("West path: '%s'\n", game->textures->west_path);

    if (!game->textures->north_path || !game->textures->south_path || 
        !game->textures->east_path || !game->textures->west_path)
    {
        perror("Error: Missing texture paths\n");
    handle_exit(game);
    }

    game->textures->north->img_ptr = mlx_xpm_file_to_image(game->win->mlx_ptr, 
        game->textures->north_path, &game->textures->north->w, &game->textures->north->h);
    if (!game->textures->north->img_ptr)
    {
        perror("Error");
        handle_exit(game);
    }
    else
    {
        game->textures->north->addr = mlx_get_data_addr(game->textures->north->img_ptr,
            &game->textures->north->bpp, &game->textures->north->line_len,
            &game->textures->north->endian);
    }

    printf("\nLoading South texture...\n");
    game->textures->south->img_ptr = mlx_xpm_file_to_image(game->win->mlx_ptr,
        game->textures->south_path, &game->textures->south->w, &game->textures->south->h);
    if (!game->textures->south->img_ptr)
    {
        perror("Failed to load South texture!\n");
        handle_exit(game);
    }
    else
    {
        printf("South texture loaded, getting address...\n");
        game->textures->south->addr = mlx_get_data_addr(game->textures->south->img_ptr,
            &game->textures->south->bpp, &game->textures->south->line_len,
            &game->textures->south->endian);
    }

    printf("\nLoading East texture...\n");
    game->textures->east->img_ptr = mlx_xpm_file_to_image(game->win->mlx_ptr,
        game->textures->east_path, &game->textures->east->w, &game->textures->east->h);
    if (!game->textures->east->img_ptr)
    {
        perror("Failed to load East texture!\n");
        handle_exit(game);
    }
    else
    {
        printf("East texture loaded, getting address...\n");
        game->textures->east->addr = mlx_get_data_addr(game->textures->east->img_ptr,
            &game->textures->east->bpp, &game->textures->east->line_len,
            &game->textures->east->endian);
    }
    
    printf("\nLoading West texture...\n");
    game->textures->west->img_ptr = mlx_xpm_file_to_image(game->win->mlx_ptr,
        game->textures->west_path, &game->textures->west->w, &game->textures->west->h);
    if (!game->textures->west->img_ptr)
    {
        perror("Failed to load West texture!\n");
        handle_exit(game);
    }
    else
    {
        printf("West texture loaded, getting address...\n");
        game->textures->west->addr = mlx_get_data_addr(game->textures->west->img_ptr,
            &game->textures->west->bpp, &game->textures->west->line_len,
            &game->textures->west->endian);
    }
    printf("--- Texture loading complete ---\n\n");
}
