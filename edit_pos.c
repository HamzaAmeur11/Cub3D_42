/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:09:34 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 01:04:24 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	up_2_wall(t_map *map, int x, int y, double angle)
{
	int	x_m;
	int	y_m;

	x_m = map->plr.x_m;
	y_m = map->plr.y_m;
	if (angle >= 0 && angle < 90 && map->map[y_m][x_m + 1] == '1'
			&& map->map[y_m + 1][x_m] == '1' && map->map[y][x - 1] == '1'
			&& map->map[y - 1][x] == '1')
		return (FAILURE);
	if (angle >= 90 && angle < 180 && map->map[y_m][x_m - 1] == '1'
			&& map->map[y_m + 1][x_m] == '1' && map->map[y][x + 1] == '1'
			&& map->map[y - 1][x] == '1')
		return (FAILURE);
	if (angle >= 180 && angle < 270 && map->map[y_m - 1][x_m] == '1' &&
			map->map[y_m][x_m - 1] == '1' &&
			map->map[y + 1][x] == '1' && map->map[y][x + 1] == '1')
		return (FAILURE);
	if (angle >= 270 && angle < 360 && map->map[y_m][x_m + 1] == '1' &&
			map->map[y_m - 1][x_m] == '1' &&
			map->map[y][x - 1] == '1' && map->map[y + 1][x] == '1')
		return (FAILURE);
	return (SUCCESS);
}

int	down_2_wall(t_map *map, int x, int y, double angle)
{
	int	x_m;
	int	y_m;

	x_m = map->plr.x_m;
	y_m = map->plr.y_m;
	if (angle >= 0 && angle < 90 && map->map[y_m][x_m - 1] == '1'
			&& map->map[y_m - 1][x_m] == '1' && map->map[y][x + 1] == '1'
			&& map->map[y + 1][x] == '1')
		return (FAILURE);
	if (angle >= 90 && angle < 180 && map->map[y_m][x_m + 1] == '1'
			&& map->map[y_m - 1][x_m] == '1' && map->map[y][x - 1] == '1'
			&& map->map[y + 1][x] == '1')
		return (FAILURE);
	if (angle >= 180 && angle < 270 && map->map[y_m + 1][x_m] == '1'
			&& map->map[y_m][x_m + 1] == '1' && map->map[y - 1][x] == '1'
			&& map->map[y][x - 1] == '1')
		return (FAILURE);
	if (angle >= 270 && angle < 360 && map->map[y_m][x_m - 1] == '1'
			&& map->map[y_m + 1][x_m] == '1' && map->map[y][x + 1] == '1'
			&& map->map[y - 1][x] == '1')
		return (FAILURE);
	return (SUCCESS);
}

void	edit_pos_walk(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->plr.x + map->plr.walk
		* map->plr.mov_speed * cos(map->plr.beta);
	new_y = map->plr.y + map->plr.walk
		* map->plr.mov_speed * sin(map->plr.beta);
	if (map->map[(int)(new_y / T_S)][(int)(new_x / T_S)] == '1')
		return ;
	else if (up_2_wall(map, (int)(new_x / T_S), (int)(new_y / T_S),
		map->plr.alpha) != SUCCESS && map->plr.walk > 0)
		return ;
	else if (down_2_wall(map, (int)(new_x / T_S), (int)(new_y / T_S)
		, map->plr.alpha) != SUCCESS && map->plr.walk < 0)
		return ;
	else
	{
		map->plr.x = new_x;
		map->plr.x_m = (int)(new_x / T_S);
		map->plr.y = new_y;
		map->plr.y_m = (int)(new_y / T_S);
	}
}

void	edit_pos_side(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->plr.x + map->plr.side * map->plr.mov_speed
		* cos(((3 * M_PI) / 2) - map->plr.beta);
	new_y = map->plr.y + map->plr.side * map->plr.mov_speed
		* sin(((3 * M_PI) / 2) - map->plr.beta);
	if (map->map[(int)(new_y / T_S)][(int)(new_x / T_S)] == '1')
		return ;
	else
	{
		map->plr.x_m = (int)(new_y / T_S);
		map->plr.y_m = (int)(new_y / T_S);
		map->plr.x = new_x;
		map->plr.y = new_y;
	}
}
