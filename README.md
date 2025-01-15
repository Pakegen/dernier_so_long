so_long.h

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "../utils/libft/libft.h"
# define TILE_SIZE 64
# define WINDOW_TITLE "so_long"
# define MAX_MAP_WIDTH 1920   // Largeur maximale de la fenêtre en pixels
# define MAX_MAP_HEIGHT 1080  // Hauteur maximale de la fenêtre en pixels
# define MAX_TILE_WIDTH 200   // Largeur maximale en tuiles
# define MAX_TILE_HEIGHT 200  // Hauteur maximale en tuiles

typedef enum e_tiletype
{
    EMPTY = '0',
    WALL = '1',
    COLLECTABLE = 'C',
    PLAYER = 'P',
    EXIT = 'E'
} t_tiletype;

typedef struct s_map
{
    char    **data;
    int     width;
    int     height;
} t_map;

typedef struct s_game
{
    void    *mlx;
    void    *window;
    t_map   map;
    void    *player_up;
    void    *player_down;
    void    *player_left;
    void    *player_right;
    void    *current_player_img;
    void    *wall_img;
    void    *floor_img;
    void    *collect_img;
    void    *exit_img;
    int     player_x;
    int     player_y;
    int     collectable;
    int     steps;
} t_game;

int  validate_filename(const char *filename);
char **read_map(const char *file, t_map *map);
int  validate_map(t_map *map);
int  validate_borders(t_map *map);
void count_elements(t_map *map, int *player, int *exit, int *collectables);
int  validate_element(t_map *map);
int  validate_line_lengths(t_map *map);
int  validate_map_data(t_map *map);
int  validate_map_dimensions(t_map *map);
void free_map(t_map *map);
void find_player_position(t_map *map, int *player_x, int *player_y);
void free_map_copy(char **map_copy, int height);
char **copy_map(t_map *map);
void explore_path(char **map, int y, int x, int *info);
int  validate_paths(t_map *map, int player_x, int player_y);
void free_images(t_game *game);
int  close_game(t_game *game);
void load_sprites(t_game *game);
void render_map(t_game *game);
int  handle_input(int keycode, t_game *game);
void init_collectables(t_game *game);
void move_player(t_game *game, int new_y, int new_x);
void *safe_load_image(void *mlx, const char *path, int *width, int *height);
void render_tile(t_game *game, int y, int x);

#endif
///////////////////////////////////////////////////////////////////////////////////////



main.c


#include "so_long.h"

int main(int ac, char **av)
{
    t_game game;

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
    if (!game.mlx)
        return (write(2, "MLX INIT FAILED\n", 17), 1);

    if (game.map.width * TILE_SIZE > MAX_MAP_WIDTH || game.map.height * TILE_SIZE > MAX_MAP_HEIGHT)
    {
        free_map(&game.map);
        return (write(2, "ERROR: Window size exceeds screen resolution\n", 46), 1);
    }

    game.window = mlx_new_window(game.mlx, game.map.width * TILE_SIZE,
            game.map.height * TILE_SIZE, WINDOW_TITLE);
    if (!game.window)
        close_game(&game);

    load_sprites(&game);
    render_map(&game);

    mlx_key_hook(game.window, handle_input, &game);
    mlx_hook(game.window, 17, 0, close_game, &game);
    mlx_loop(game.mlx);

    return (0);
}


///////////////////////////////////////////////////////////////////////////////////

map.c


#include "so_long.h"

void free_map(t_map *map)
{
    if (!map->data)
        return;

    for (int i = 0; i < map->height; i++)
        free(map->data[i]);
    free(map->data);
    map->data = NULL;
}

int validate_map_dimensions(t_map *map)
{
    if (map->width > MAX_TILE_WIDTH || map->height > MAX_TILE_HEIGHT)
    {
        write(2, "ERROR: Map dimensions too large\n", 33);
        return (0);
    }
    if (map->width * TILE_SIZE > MAX_MAP_WIDTH || map->height * TILE_SIZE > MAX_MAP_HEIGHT)
    {
        write(2, "ERROR: Map exceeds screen resolution\n", 38);
        return (0);
    }
    return (1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


sprites.c

#include "so_long.h"

void *safe_load_image(void *mlx, const char *path, int *width, int *height)
{
    void *image = mlx_xpm_file_to_image(mlx, path, width, height);
    if (!image)
    {
        write(2, "ERROR: Failed to load image: ", 29);
        write(2, path, strlen(path));
        write(2, "\n", 1);
        return NULL;
    }
    if (*width > TILE_SIZE || *height > TILE_SIZE)
    {
        write(2, "ERROR: Image dimensions too large: ", 36);
        write(2, path, strlen(path));
        write(2, "\n", 1);
        mlx_destroy_image(mlx, image);
        return NULL;
    }
    return image;
}

void load_sprites(t_game *game)
{
    int sprite_width = 0;
    int sprite_height = 0;

    game->floor_img = safe_load_image(game->mlx, "texture/BACKGROUND.xpm", &sprite_width, &sprite_height);
    if (!game->floor_img)
        close_game(game);

    game->wall_img = safe_load_image(game->mlx, "texture/WALL.xpm", &sprite_width, &sprite_height);
    if (!game->wall_img)
        close_game(game);

    game->player_down = safe_load_image(game->mlx, "texture/slime_down.xpm", &sprite_width, &sprite_height);
    if (!game->player_down)
        close_game(game);

    game->player_up = safe_load_image(game->mlx, "texture/slime_up.xpm", &sprite_width, &sprite_height);
    if (!game->player_up)
        close_game(game);

    game->player_left = safe_load_image(game->mlx, "texture/slime_left.xpm", &sprite_width, &sprite_height);
    if (!game->player_left)
        close_game(game);

    game->player_right = safe_load_image(game->mlx, "texture/slime_right.xpm", &sprite_width, &sprite_height);
    if (!game->player_right)
        close_game(game);

    game->collect_img = safe_load_image(game->mlx, "texture/piece.xpm", &sprite_width, &sprite_height);
    if (!game->collect_img)
        close_game(game);

    game->exit_img = safe_load_image(game->mlx, "texture/exit.xpm", &sprite_width, &sprite_height);
    if (!game->exit_img)
        close_game(game);

    game->current_player_img = game->player_right;
}
////////////////////////////////

#include "so_long.h"

int close_game(t_game *game)
{
    // Libérer la carte si elle est allouée
    if (game->map.data)
    {
        for (int i = 0; i < game->map.height; i++)
            free(game->map.data[i]);
        free(game->map.data);
    }

    // Libérer toutes les images
    if (game->mlx)
    {
        if (game->floor_img)
            mlx_destroy_image(game->mlx, game->floor_img);
        if (game->wall_img)
            mlx_destroy_image(game->mlx, game->wall_img);
        if (game->player_down)
            mlx_destroy_image(game->mlx, game->player_down);
        if (game->player_up)
            mlx_destroy_image(game->mlx, game->player_up);
        if (game->player_left)
            mlx_destroy_image(game->mlx, game->player_left);
        if (game->player_right)
            mlx_destroy_image(game->mlx, game->player_right);
        if (game->collect_img)
            mlx_destroy_image(game->mlx, game->collect_img);
        if (game->exit_img)
            mlx_destroy_image(game->mlx, game->exit_img);
    }

    // Détruire la fenêtre si elle existe
    if (game->mlx && game->window)
        mlx_destroy_window(game->mlx, game->window);

    // Quitter proprement
    exit(0);
    return (0);
}

tous les fichiers a apporté des modifications 
