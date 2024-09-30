#include "cub3d.h"

int	is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != 'N'
		&& c != 'E' && c != 'W' && c != 'S')
		return (0);
	return (1);
}

//this will segfault when the there is no previous char in case of invalid maps but ill deal with that later lol
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
				if (!is_valid_char(map[i + 1][j]) || !is_valid_char(map[i - 1][j])
					|| !is_valid_char(map[i][j + 1]) || !is_valid_char(map[i][j - 1]))
				{
					//printf("%i ROW, %i COLUMN, %c CHAR\n", i, j, map[i][j]);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

