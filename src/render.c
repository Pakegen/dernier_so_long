/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:07:11 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/08 09:55:19 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void	render_tile(t_game *game, int y, int x)
{
	void	*img;

	img = game->floor_img;
	if (game->map.data[y][x] == '1')
		img = game->wall_img;
	else if (game->map.data[y][x] == 'C')
		img = game->collect_img;
	else if (game->map.data[y][x] == 'E')
		img = game->exit_img;
	mlx_put_image_to_window(game->mlx, game->window, img, x * TILE_SIZE,
		y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, y, x);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->current_player_img,
		game->player_x * TILE_SIZE,
		game->player_y * TILE_SIZE);
}
