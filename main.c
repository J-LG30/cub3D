/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-goff <jle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:06:58 by jle-goff          #+#    #+#             */
/*   Updated: 2024/12/17 14:26:46 by jle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_errors(char **argv, int argc, char *map)
{
	int	i;

	if (argc != 2 || !argv[0] || !argv[1])
	{
		printf("Usage: ./cub3D [Map.cub]\n");
		return (0);
	}
	i = 0;
	while (map[i])
		i++;
	if (ft_strlen(map) >= 4)
	{
		if (map[i - 4] == '.' && map[i - 3] == 'c'
			&& map[i - 2] == 'u' && map[i - 1] == 'b')
			return (1);
	}
	printf("Error: Map file needs to be of type .cub\n");
	return (0);
}

void	finish_game_setup(t_game *game, t_player *player, char *map)
{
	game->parsed_map = 0;
	game->parsed_ceiling = 0;
	game->parsed_floor = 0;
	open_map(map, game);
	load_textures(game);
	init_player(game, player);
	cast_rays(game, player);
	mlx_hook(game->win->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win->win_ptr, 17, 0, handle_exit, game);
	mlx_loop(game->win->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_win		win;
	t_player	player;
	t_game		game;
	t_img		wall;

	if (!check_errors(argv, argc, argv[1]))
		exit(1);
	if (!init_window(&win))
		exit (1);
	game.win = &win;
	game.player = &player;
	game.wall = &wall;
	wall = new_sprite(win.mlx_ptr, win.width, win.height);
	game.textures = init_textures(win.mlx_ptr);
	if (!game.textures)
	{
		perror("Texture initialization failed\n");
		exit(1);
	}
	finish_game_setup(&game, &player, argv[1]);
	return (0);
}
