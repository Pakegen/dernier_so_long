/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:36:28 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/08 09:54:18 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_horizontal_borders(t_map *map)
{
	int	x;

	x = 0;
	if (!map->data[0] || !map->data[map->height - 1])
		return (write(2, "INVALID HORIZONTAL BORDER\n", 27), 0);
	while (x < map->width)
	{
		if (map->data[0][x] != '1' || map->data[map->height - 1][x] != '1')
			return (write(2, "HORIZONTAL BORDERS NOT CLOSED\n", 31), 0);
		x++;
	}
	return (1);
}

static int	validate_vertical_borders(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (!map->data[y])
			return (write(2, "INVALID VERTICAL BORDERS\n", 26), 0);
		if (map->data[y][0] != '1' || map->data[y][map->width - 1] != '1')
			return (write(2, "VERTICAL BORDERS ARE NOT CLOSED\n", 33), 0);
		y++;
	}
	return (1);
}

int	validate_borders(t_map *map)
{
	if (!map || !map->data || map->width <= 0 || map->height <= 0)
		return (write(2, "INVALID MAP DIMENSION\n", 23), 0);
	if (!validate_horizontal_borders(map))
		return (0);
	if (!validate_vertical_borders(map))
		return (0);
	return (1);
}
