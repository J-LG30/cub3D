/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:02:55 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 18:04:59 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_identifier_format(const char *line)
{
	const char	*valid_ids[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;
	int			len;

	i = 0;
	while (valid_ids[i])
	{
		len = ft_strlen(valid_ids[i]);
		if (ft_strncmp(line, valid_ids[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

// char	*trim_whitespace(char *line)
// {
// 	while (*line == ' ' || *line == '\t')
// 		line++;
// 	return (line);
// }

int	is_valid_line(char *line, t_game *game)
{
	char	*trimmed;

	if (line[0] == '\n' && game->parsed_map == 1)
	{
		game->empty_line = 1;
		return (0);
	}
	trimmed = skip_whitespace(line);
	if (trimmed[0] == '1' || trimmed[0] == ' ')
	{
		return (1);
	}
	if (trimmed[0] == '\n' || ft_strlen(trimmed) <= 0)
	{
		return (1);
	}
	if (!is_valid_identifier_format(trimmed))
	{
		perror("Error\nInvalid identifier format in map file\n");
		free(line);
		handle_exit(game);
	}
	return (1);
}
