/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:48:43 by jle-goff          #+#    #+#             */
/*   Updated: 2024/11/22 15:42:09 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color_line(char *line)
{
	if (!line || ft_strlen(line) < 2)
		return (0);
	if (line[0] == 'F' || line[0] == 'C')
		if (line[1] == ' ')
			return (1);
	return (0);
}

char	**split_rgb(char *line)
{
	char	**split;
	char	**rgb;
	int		i;

	printf("Parsing color line: '%s'\n", line);
	split = ft_split(line, ' ');
	if (!split || !split[1])
	{
		printf("Failed to split line by space\n");
		return (NULL);
	}
	rgb = ft_split(split[1], ',');
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		printf("Failed to split RGB values\n");
		return (NULL);
	}
	return (rgb);
}

int	parse_color(char *line, t_color *color)
{
	char	**rgb;
	int		int_rgb[3];
	int		i;

	rgb = split_rgb(line);
	if (!rgb)
		return (0);
	int_rgb[0] = ft_atoi(rgb[0]);
	int_rgb[1] = ft_atoi(rgb[1]);
	int_rgb[2] = ft_atoi(rgb[2]);
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	if (int_rgb[0] < 0 || int_rgb[0] > 255 || int_rgb[1] < 0 || int_rgb[1] > 255
		|| int_rgb[2] < 0 || int_rgb[2] > 255)
	{
		return (0);
	}
	if (!color)
		return (0);
	color->r = int_rgb[0];
	color->g = int_rgb[1];
	color->b = int_rgb[2];
	return (1);
}
