/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:23:16 by jle-goff          #+#    #+#             */
/*   Updated: 2024/10/02 15:57:03 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_img *data, int colour)
{
    int	i;
    int	j;

    i = 0;
    j = 0;
    while (i < data->w)
    {
        j = 0;
        while (j < data->h)
        {
            my_mlx_pixel_put(data, i, j, colour);
            j++;
        }
        i++;
    }
}

void	cast_rays(t_game *game, t_player *player)
{
    double	raydirX;
    double	raydirY;
    double	posX;
    double	posY;
    double	cameraX;
    double	deltaDistX;
    double	deltaDistY;
    double	sideDistX;
    double	sideDistY;
    double	perpWallDist;
    int		stepX;
    int		stepY;
    int		i;
    int		mapX;
    int		mapY;
    int		hit;
    int		side;
    int		lineHeight;
    int		drawStart;
    int		drawEnd;
    
    raydirX = player->dirX;
    raydirY = player->dirY;
    posX = player->posX;
    posY = player->posY;
    i = 0;
    
    clear_image(game->wall, 0x00000000);
    while (i < game->win->width)
    {
        mapX = (int)posX;
        mapY = (int)posY;
        cameraX = (2 * i) / (float)game->win->width - 1;
        raydirX = player->dirX + (player->planeX * cameraX);
        raydirY = player->dirY + (player->planeY * cameraX);
        perpWallDist = 0;
        
        if (raydirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1 / raydirX);
        if (raydirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1 / raydirY);

        if (raydirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (raydirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // DDA Algorithm
        hit = 0;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map[mapY][mapX] == '1')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;

        // calculate wall height and boundaries 
        lineHeight = (int)(game->win->height / perpWallDist);
        drawStart = -lineHeight / 2 + game->win->height / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + game->win->height / 2;
        if (drawEnd >= game->win->height)
            drawEnd = game->win->height - 1;

        // Calculate texture xy
        double wallX;
        if (side == 0)
            wallX = posY + perpWallDist * raydirY;
        else
            wallX = posX + perpWallDist * raydirX;
        wallX -= floor(wallX);

        // Get x coordinate 
        int texX = (int)(wallX * TEX_WIDTH);
        if (side == 0 && raydirX > 0)
            texX = TEX_WIDTH - texX - 1;
        if (side == 1 && raydirY < 0)
            texX = TEX_WIDTH - texX - 1;

        // Select texture 
        t_img *current_texture;
        if (side == 0)
            current_texture = raydirX > 0 ? game->textures->east : game->textures->west;
        else
            current_texture = raydirY > 0 ? game->textures->south : game->textures->north;

        // Draw the textured vertical line
        double step = 1.0 * TEX_HEIGHT / lineHeight;
        double texPos = (drawStart - game->win->height / 2 + lineHeight / 2) * step;
        
        int y = drawStart;
        while (y < drawEnd)
        {
            int texY = (int)texPos & (TEX_HEIGHT - 1);
            texPos += step;
            
            // Get color from texture
            char *tex_pixel = current_texture->addr + 
                (texY * current_texture->line_len + texX * (current_texture->bpp / 8));
            int color = *(unsigned int*)tex_pixel;
            
            // Apply shading for sides
            if (side == 1)
                color = (color >> 1) & 8355711; // Make sides darker

            my_mlx_pixel_put(game->wall, i, y, color);
            y++;
        }
        i++;
    }
    mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->bgd->img_ptr, 0, 0);
    mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->wall->img_ptr, 0, 0);
}