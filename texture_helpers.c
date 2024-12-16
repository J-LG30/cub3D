/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:06:46 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 12:35:33 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n' || str[len - 1] == '\r'))
		str[--len] = '\0';
	return (str);
}

char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	check_texture_duplicate(char *line, t_game *game)
{
	static t_tex_check	textures[] = {
	{"NO", 0},
	{"SO", 0},
	{"WE", 0},
	{"EA", 0}};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(skip_whitespace(line), textures[i].id, 2) == 0)
		{
			if (++textures[i].count > 1)
			{
				perror("Error\nDuplicate texture\n");
				free(line);
				handle_exit(game);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	has_duplicate_texture(t_game *game, const char *identifier)
{
	if (ft_strncmp(identifier, "NO", 3) == 0 && game->textures->north_path)
		return (1);
	if (ft_strncmp(identifier, "SO", 3) == 0 && game->textures->south_path)
		return (1);
	if (ft_strncmp(identifier, "EA", 3) == 0 && game->textures->east_path)
		return (1);
	if (ft_strncmp(identifier, "WE", 3) == 0 && game->textures->west_path)
		return (1);
	return (0);
}
