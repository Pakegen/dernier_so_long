/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:29:48 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/13 15:29:11 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include"../minilibx-linux/mlx.h"
# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>
# include <string.h>
# include "../utils/libft/libft.h"
# define TILE_SIZE 64
# define WINDOW_TITLE "so_long"

typedef enum e_tiletype
{
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E'
}t_tiletype;

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
}t_map;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	t_map	map;
	void	*player_up;
	void	*player_down;
	void	*player_left;
	void	*player_right;
	void	*current_player_img;
	void	*wall_img;
	void	*floor_img;
	void	*collect_img;
	void	*exit_img;
	int		player_x;
	int		player_y;
	int		collectable;
	int		steps;
}t_game;

int		validate_filename(const char *filename);
char	**read_map(const char *file, t_map *map);
int		validate_map(t_map *map);
void	count_elements(t_map *map, int *player, int *exit, int *collectables);
int		validate_element(t_map *map);
void	load_sprites(t_game *game);
void	render_map(t_game *game);
int		handle_input(int keycode, t_game *game);
int		close_game(t_game *game);
int		validate_borders(t_map *map);
void	find_player_position(t_map *map, int *player_x, int *player_y);
void	initialize_map(t_map *map);
int		validate_paths(t_map *map, int player_x, int player_y);

#endif
