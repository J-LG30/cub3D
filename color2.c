/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:08:05 by gverissi          #+#    #+#             */
/*   Updated: 2024/12/17 18:18:40 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	format_valid(char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ',')
			commas++;
		if (line[i] != ',' && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (commas != 2)
		return (0);
	return (1);
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
		return (0);
	if (!color)
		return (0);
	color->r = int_rgb[0];
	color->g = int_rgb[1];
	color->b = int_rgb[2];
	return (1);
}
