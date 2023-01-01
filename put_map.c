/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:25:31 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 01:32:21 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

bool	is_player(t_map *map, double i, double j)
{
	double	x;
	double	y;
	double	px;
	double	py;

	px = map->plr.x / T_S;
	py = map->plr.y / T_S;
	x = i / T_S;
	y = j / T_S;
	return (((x - px) * (x - px)) + ((y - py) * (y - py)) <= 0.16 * 0.16);
}

void	put_square(t_map *map, int start_x, int start_y, int clr)
{
	int	i;
	int	j;

	i = start_x;
	j = start_y;
	while (i < start_x + T_S - 1)
	{
		j = start_y;
		while (j < start_y + T_S - 1)
		{
			if (is_player(map, i, j))
				mlx_pixel_put(map->mlx_.mlx_ptr,
					map->mlx_.win_ptr, i, j++, 0xFF0000);
			else
				mlx_pixel_put(map->mlx_.mlx_ptr,
					map->mlx_.win_ptr, i, j++, clr);
		}
		i++;
	}
}

int	is_upper_char(char c)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	put_char(t_map *map, char c, int i, int j)
{
	if (c == '0' || is_upper_char(c) == EXIT_SUCCESS)
		put_square(map, i * T_S, j * T_S, 0x0000FF);
	else if (c == '1')
		put_square(map, i * T_S, j * T_S, 0x00FF00);
	else if (c == ' ')
		put_square(map, i * T_S, j * T_S, 0x0FFFF0);
}

void	put_wall(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map->map[++i] != NULL)
	{
		j = -1;
		while (map->map[i][++j] != 0)
			put_char(map, map->map[i][j], j, i);
	}
}
