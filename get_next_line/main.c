/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:10 by jle-goff          #+#    #+#             */
/*   Updated: 2023/05/07 18:54:39 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>


int	main(void)
{
	int	fd;
	char	*str;


	fd = open("test.txt", O_RDONLY);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	 str = get_next_line(fd);
	 printf("%s", str);
	 free(str);


	str = get_next_line(fd);
	 printf("%s", str);
	 free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);

	str = get_next_line(fd);
	printf("%s", str);
	free(str);


	close(fd);
}

