/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:23:54 by jle-goff          #+#    #+#             */
/*   Updated: 2023/05/07 17:26:56 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			n;

	if (fd < 0 || FOPEN_MAX < fd)
		return (0);
	line = NULL;
	while (1)
	{
		if (!buffer[fd][0])
		{
			n = read(fd, buffer[fd], BUFFER_SIZE);
			if (n == -1)
			{
				free(line);
				return (NULL);
			}
			else if (n == 0)
				return (line);
		}
		line = ft_strjoin_nl(line, buffer[fd]);
		if (ft_clean(buffer[fd]))
			return (line);
	}
	return (NULL);
}
