/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:04:33 by jle-goff          #+#    #+#             */
/*   Updated: 2023/05/04 12:40:15 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_nl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_nl(char *s1, char *s2)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	size = ft_strlen_nl(s1) + ft_strlen_nl(s2) + 1;
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (0);
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
	{
		str[j] = s2[i];
		if (str[j++] == '\n')
			break ;
		i++;
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nl;

	is_nl = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_nl == 1)
		{
			str[j] = str[i];
			j++;
		}
		if (str[i] == '\n')
			is_nl = 1;
		str[i] = '\0';
		i++;
	}
	return (is_nl);
}
