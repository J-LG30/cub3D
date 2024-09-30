#include "cub3d.h"

/*
I'm doing separate functions for each error checking so looping over the array each time.
I don't think this affects performance in any big way, and for norminette its easier to split it.
But I could probably put two error checkings in one function.
*/

int	is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N'
		&& c != 'E' && c != 'W' && c != 'S')
		return (0);
	return (1);
}

int	enclosed_helper(char **map, int i, int j)
{
	// if (!is_valid_char(map[i + 1][j]) || !is_valid_char(map[i][j + 1]))
	// 	return (0);
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

int check_all_valid_char(char **map)
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

