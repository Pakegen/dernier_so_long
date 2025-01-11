/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:07:07 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/09 00:13:32 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

static int	count_lines(const char	*file)
{
	int		fd;
	int		lines;
	char	buffer;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	while (read(fd, &buffer, 1) > 0)
	{
		if (buffer == '\n')
			lines++;
	}
	close(fd);
	if (lines <= 0)
		return (0);
	return (lines);
}

static void	free_map_on_error(char **map_data, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(map_data[i]);
		i++;
	}
	free(map_data);
}

static int	allocate_map(t_map *map, int line_count, int fd)
{
	int	i;

	i = 0;
	map->data = malloc(sizeof(char *) * (line_count + 1));
	if (!map->data)
		return (write(2, "MEMORY ALLOCATION FAILED\n", 26), close(fd), 0);
	while (i < line_count)
	{
		map->data[i] = get_next_line(fd);
		if (!map->data[i])
		{
			write(2, "FAILED READ A LINE\n", 20);
			return (free_map_on_error(map->data, i), close(fd), 0);
		}
		i++;
	}
	map->data[i] = NULL;
	close(fd);
	return (1);
}

char	**read_map(const char *file, t_map *map)
{
	int	fd;
	int	line_count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "CANNOT OPEN FILE\n", 18), NULL);
	line_count = count_lines(file);
	if (line_count <= 0)
		return (write(2, "NO LINE IN MAP\n", 16), close(fd), NULL);
	if (!allocate_map(map, line_count, fd))
		return (NULL);
	if (map->data[0] != NULL)
		map->width = ft_strlen(map->data[0]) - 1;
	else
		map->width = 0;
	map->height = line_count;
	return (map->data);
}

void	find_player_position(t_map *map, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->data[y][x] == 'P')
			{
				*player_x = x;
				*player_y = y;
				ft_printf("Player found at (%d, %d)\n", *player_x, *player_y);
				return ;
			}
			x++;
		}
		y++;
	}
	write(2, "NO PLAYER FOUND\n", 17);
}
