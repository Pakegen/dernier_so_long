/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:26:58 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/10 12:10:36 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_collectables(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->collectable = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.data[y][x] == 'C')
				game->collectable++;
			x++;
		}
		y++;
	}
	ft_printf("Total collectables: %d\n", game->collectable);
}

void	load_sprites(t_game *game)
{
	int	sprite_width;
	int	sprite_height;

	sprite_width = 0;
	sprite_height = 0;
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"texture/BACKGROUND.xpm", &sprite_width, &sprite_height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"texture/WALL.xpm", &sprite_width, &sprite_height);
	game->player_down = mlx_xpm_file_to_image(game->mlx,
			"texture/slime_down.xpm", &sprite_width, &sprite_height);
	game->player_left = mlx_xpm_file_to_image(game->mlx,
			"texture/slime_left.xpm", &sprite_width, &sprite_height);
	game->player_up = mlx_xpm_file_to_image(game->mlx,
			"texture/slime_up.xpm", &sprite_width, &sprite_height);
	game->player_right = mlx_xpm_file_to_image(game->mlx,
			"texture/slime_right.xpm", &sprite_width, &sprite_height);
	game->current_player_img = mlx_xpm_file_to_image(game->mlx,
			"texture/slime_right.xpm", &sprite_width, &sprite_height);
	game->collect_img = mlx_xpm_file_to_image(game->mlx,
			"texture/piece.xpm", &sprite_width, &sprite_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"texture/exit.xpm", &sprite_height, &sprite_height);
}

void	initialize_map(t_map *map)
{
	map->data = NULL;
	map->width = 0;
	map->height = 0;
}

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	exit (0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (write(2, "ARGUMENT INCORRECT\n", 20), 1);
	initialize_map(&game.map);
	if (!validate_filename(av[1]))
		return (write(2, "INCORRECT FILE\n", 16), 1);
	if (!read_map(av[1], &game.map))
		return (write(2, "CANNOT READ MAP\n", 17), 1);
	if (!validate_map(&game.map))
		return (write(2, "INVALID MAP\n", 13), 1);
	find_player_position(&game.map, &game.player_x, &game.player_y);
	init_collectables(&game);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, game.map.width * TILE_SIZE,
			game.map.height * TILE_SIZE, WINDOW_TITLE);
	game.steps = 0;
	load_sprites(&game);
	render_map(&game);
	mlx_key_hook(game.window, handle_input, &game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
