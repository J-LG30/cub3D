/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:48:43 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 15:14:06 by jle-goff         ###   ########.fr       */
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

static char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**check_split(char **split)
{
	if (!split || !split[1])
	{
		perror("Failed to split line by space\n");
		if (split)
			return (free_split(split));
		return (NULL);
	}
	return (split);
}

char	**split_rgb(char *line)
{
	char	**rgb;
	int		i;

	printf("SPLIT RGB LINE: %s\n", line);
	line++;
	if (*line != ' ' && *line != '\t' && !ft_isdigit(*line))
	{
		perror("wrong identifier colour\n");
		return (NULL);
	}
	line = skip_whitespace(line);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (NULL);
	i = 0;
	while (rgb[i])
	{
		printf("RGB LINE: %s\n", rgb[i]);
		i++;
	}
	if (i != 3)
	{
		perror("Failed to split RGB values.\n");
		return (free_split(rgb));
	}
	return (rgb);
}

// char	**split_rgb(char *line)
// {
// 	char	**split;
// 	char	**rgb;
// 	int		i;

// 	split = ft_split(line, ' ');
// 	if (!check_split(split))
// 		return (NULL);
// 	rgb = ft_split(split[1], ',');
// 	free_split(split);
// 	if (!rgb)
// 		return (NULL);
// 	i = 0;
// 	while (rgb[i])
// 	{
// 		printf("RGB LINE: %s\n", rgb[i]);
// 		i++;
// 	}
// 	if (i != 3)
// 	{
// 		perror("Failed to split RGB values.\n");
// 		return (free_split(rgb));
// 	}
// 	return (rgb);
// }

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
