/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:42:14 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 17:21:46 by jle-goff         ###   ########.fr       */
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
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player_count++;
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

// int	check_up_down(char **map, int i, int j, int dir, int rows)
// {
// 	printf("in here\n");
// 	while (map[i])
// 	{
// 		printf("a: %s\n", map[i]);
// 		if (map[i][j] == '1')
// 			return (1);
// 		else if (i == 0 || i == rows || ft_strlen(map[i + dir]) < j + 1)
// 			return (0);
// 		i += dir;
// 	}
// 	return (0);
// }

// if (!is_valid_char(map[i + 1][j]) || !is_valid_char(map[i][j + 1]))
// 	return (0);
// int	enclosed_helper(char **map, int i, int j)
// {
// 	int	up;
// 	int	down;
// 	int	rows;
// 	rows = 0;
// 	while (map && map[rows])
// 		rows++;
// 	if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
// 	{
// 		printf("not enclosed by wall each row\n");
// 		return (0);
// 	}
// 	up = check_up_down(map, i, j, -1, rows);
// 	down = check_up_down(map, i, j, 1, rows);
// 	if (up == 1 && down == 1)
// 		return (1);
// 	else
// 		return (0);
// }

// int	check_enclosed(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
// 				|| map[i][j] == 'W' || map[i][j] == 'E')
// 			{
// 				if (enclosed_helper(map, i, j) == 0)
// 					return (0);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

//first and last rows have only wall characters
int	first_last_all_walls(char **map, int rows)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (map[rows - 1][i])
	{
		if (map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

//every row starts and finishes with a wall character
int	start_finish_wall(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	draw_border(char **map, int rows)
{
	int	i;
	int	j;
	int	row_len;
	int	next_len;

	i = 0;
	while (map[i] && i != rows - 1)
	{
		row_len = ft_strlen(map[i]);
		next_len = ft_strlen(map[i + 1]);
		if (row_len < next_len)
		{
			while (map[i + 1][row_len])
			{
				if (map[i + 1][row_len] != '1')
					return (0);
				row_len++;
			}
		}
		else if (row_len > next_len && map[i][next_len] != '1')
			return (0);
		i++;
	}
	return (1);
}

// int	check_enclosed(char **map)
// {
// 	int	i;
// 	int	j;
// 	int	rows;

// 	i = 0;
// 	j = 0;
// 	rows = 0;
// 	while (map[rows])
// 		rows++;
// 	if (!first_last_all_walls(map, rows))
// 		return (0);
// 	if (!start_finish_wall(map))
// 		return (0);
// 	if (!draw_border(map, rows))
// 		return (0);
// 	return (1);
// }

int	is_surrounding_char(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E')
	{
		return (1);
	}
	return (0);
}
int	check_surrounding(char **map, int i, int j)
{
	if (i > 0 && ft_strlen(map[i - 1]) >= j)
	{
		if (!is_surrounding_char(map[i - 1][j]))
		{
			printf("a\n");
			return (0);
		}
	}
	else
	{
		printf("LINE: %s\n", map[i]);
		printf("w\n");
		return (0);
	}
	if (map[i + 1] && ft_strlen(map[i + 1]) >= j)
	{
		if (!is_surrounding_char(map[i + 1][j]))
		{
			printf("LINE: %s\n", map[i]);
			printf(": %c\n", map[i + 1][j]);
			printf("b\n");
			return (0);
		}
	}
	else
	{
		printf("k\n");
		return (0);
	}
	if (!is_surrounding_char(map[i][j + 1]))
	{
		printf("c\n");
		return (0);
	}
	if (j > 0)
	{
		if (!is_surrounding_char(map[i][j - 1]))
			{
				printf("d\n");
				return (0);
			}
			
	}
	else
	{
		printf("z\n");
		return (0);
	}
	if (i > 0 && ft_strlen(map[i - 1]) >= j + 1)
	{
		if (!is_surrounding_char(map[i - 1][j + 1]))
		{
			printf("a\n");
			return (0);
		}
	}
	else
	{
		printf("LINE: %s\n", map[i]);
		printf("w\n");
		return (0);
	}
	if (i > 0 && j > 0)
	{
		if (!is_surrounding_char(map[i - 1][j - 1]))
		{
			printf("a\n");
			return (0);
		}
	}
	else
	{
		printf("LINE: %s\n", map[i]);
		printf("w\n");
		return (0);
	}
	if (map[i + 1] && ft_strlen(map[i + 1]) >= j + 1)
	{
		if (!is_surrounding_char(map[i + 1][j + 1]))
		{
			printf("LINE: %s\n", map[i]);
			printf(": %c\n", map[i + 1][j]);
			printf("b\n");
			return (0);
		}
	}
	else
	{
		printf("k\n");
		return (0);
	}
	
	if (map[i + 1] && j > 0)
	{
		if (!is_surrounding_char(map[i + 1][j - 1]))
		{
			printf("b\n");
			return (0);
		}
	}
	else
	{
		printf("k\n");
		return (0);
	}
	
	
	return (1);
}

int	check_enclosed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
			{
				if (!check_surrounding(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
