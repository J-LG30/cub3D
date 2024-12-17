/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enclosed_map_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gverissi <gverissi@42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:29:57 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 18:19:51 by gverissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top(char **map, int i, int j)
{
	if (i > 0 && ft_strlen(map[i - 1]) >= j)
	{
		if (!is_surrounding_char(map[i - 1][j]))
			return (0);
	}
	else
		return (0);
	if (i > 0 && ft_strlen(map[i - 1]) >= j + 1)
	{
		if (!is_surrounding_char(map[i - 1][j + 1]))
			return (0);
	}
	else
		return (0);
	if (i > 0 && j > 0)
	{
		if (!is_surrounding_char(map[i - 1][j - 1]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_bottom(char **map, int i, int j)
{
	if (map[i + 1] && ft_strlen(map[i + 1]) >= j)
	{
		if (!is_surrounding_char(map[i + 1][j]))
			return (0);
	}
	else
		return (0);
	if (map[i + 1] && ft_strlen(map[i + 1]) >= j + 1)
	{
		if (!is_surrounding_char(map[i + 1][j + 1]))
			return (0);
	}
	else
		return (0);
	if (map[i + 1] && j > 0)
	{
		if (!is_surrounding_char(map[i + 1][j - 1]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_right(char **map, int i, int j)
{
	if (!is_surrounding_char(map[i][j + 1]))
		return (0);
	return (1);
}

int	check_left(char **map, int i, int j)
{
	if (j > 0)
	{
		if (!is_surrounding_char(map[i][j - 1]))
		{
			return (0);
		}
	}
	else
	{
		return (0);
	}
	return (1);
}
