/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:42:14 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/03 16:57:20 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	printf("a\n");
	while (map[i])
	{
		printf("b\n");
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player_count++;
				printf("a\n");
			}
			j++;
		}
		i++;
	}
	if (player_count == 1)
		return (1);
	else
		return (0);
}

// if (!is_valid_char(map[i + 1][j]) || !is_valid_char(map[i][j + 1]))
// 	return (0);
int	enclosed_helper(char **map, int i, int j)
{
	if (i == 0 && map[i][j] != '1')
	{
		return (0);
	}
	if (j == 0 && map[i][j] != '1')
	{
		return (0);
	}
	return (1);
}

int	check_enclosed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (enclosed_helper(map, i, j) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
