/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:37 by gverissi          #+#    #+#             */
/*   Updated: 2024/11/29 16:49:14 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
I'm doing separate functions for each
error checking so looping over the array each time.
I don't think this affects performance in any big way,
and for norminette its easier to split it.
But I could probably put two error checkings in one function.
*/

// O for NO/SO, A for EA
int	is_texture_char(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != 'O' && c != 'A')
		return (0);
	return (1);
}

// New function to check if a line contains valid texture identifier
int	is_texture_line(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (0);
	if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N'
		&& c != 'E' && c != 'W' && c != 'S')
		return (0);
	return (1);
}

int	check_all_valid_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]) && map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
