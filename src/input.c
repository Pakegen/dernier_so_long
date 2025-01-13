/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:07:00 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/13 15:58:30 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_move_valid(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0
		|| new_x >= game->map.width || new_y >= game->map.height)
		return (write(2, "OUT OF BAND", 12), 0);
	if (game->map.data[new_y][new_x] == '1')
		return (0);
	return (1);
}

static void	update_player_image(t_game *game, int new_x, int new_y)
{
	if (new_y < game->player_y)
		game->current_player_img = game->player_up;
	else if (new_y > game->player_y)
		game->current_player_img = game->player_down;
	else if (new_x < game->player_x)
		game->current_player_img = game->player_left;
	else if (new_x > game->player_x)
		game->current_player_img = game->player_right;
}

static void	process_move(t_game *game, int new_x, int new_y)
{
	if (game->map.data[new_y][new_x] == 'C')
		game->collectable--;
	if (game->map.data[new_y][new_x] == 'E')
	{
		if (game->collectable > 0)
		{
			write(2, "CANNOT EXIT, COLLECTABLE REMAINING\n", 36);
			return ;
		}
		close_game(game);
	}
	game->map.data[game->player_y][game->player_x] = '0';
	game->map.data[new_y][new_x] = 'P';
	game->player_y = new_y;
	game->player_x = new_x;
	game->steps++;
	ft_printf("Steps: %d\n", game->steps);
}

void	move_player(t_game *game, int new_y, int new_x)
{
	if (!is_move_valid(game, new_x, new_y))
		return ;
	update_player_image(game, new_x, new_y);
	process_move(game, new_x, new_y);
	render_map(game);
}

int	handle_input(int keycode, t_game *game)
{
	int	new_y;
	int	new_x;

	new_y = game->player_y;
	new_x = game->player_x;
	ft_printf("Key pressed: %d\n", keycode);
	if (keycode == 65307)
		close_game(game);
	if (keycode == 119 || keycode == 65362)
		new_y--;
	else if (keycode == 115 || keycode == 65364)
		new_y++;
	else if (keycode == 97 || keycode == 65361)
		new_x--;
	else if (keycode == 100 || keycode == 65363)
		new_x++;
	ft_printf("Current position: (%d, %d)\n", game->player_x, game->player_y);
	ft_printf("Move attempt to: (%d, %d)\n", new_x, new_y);
	move_player(game, new_y, new_x);
	return (0);
}
