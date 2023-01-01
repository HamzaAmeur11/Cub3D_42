/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:00 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 01:32:21 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	check_2_walls(t_map *map, t_point *f, long angle)
{
	if (angle > 0 && angle < 90)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x + 1)
			/ T_S)] == '1' || map->map[(int)((f->y + 1)
			/ T_S)][(int)((f->x - 1) / T_S)] == '1')
			return (EXIT_SUCCESS);
	if (angle > 90 && angle < 180)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x - 1)
			/ T_S)] == '1' || map->map[(int)((f->y + 1)
			/ T_S)][(int)((f->x + 1) / T_S)] == '1')
			return (EXIT_SUCCESS);
	if (angle > 180 && angle < 270)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x + 1)
			/ T_S)] == '1' || map->map[(int)((f->y + 1)
			/ T_S)][(int)((f->x - 1) / T_S)] == '1')
			return (EXIT_SUCCESS);
	if (angle > 270 && angle < 360)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x - 1)
			/ T_S)] == '1' || map->map[(int)((f->y + 1)
			/ T_S)][(int)((f->x + 1) / T_S)] == '1')
			return (EXIT_SUCCESS);
	return (FAILDE);
}

double	val_abs(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

int	check_v(double x)
{
	double	c;
	int		i;

	i = (int)x;
	c = x - i;
	if (c >= 1 / 2)
		return (i + 1);
	return (i);
}

int	check_if_wall(t_map *map, double x, double y)
{
	int	x_pos;
	int	y_pos;

	x_pos = floor(x / T_S);
	y_pos = floor(y / T_S);
	if (x >= 0 && x < map->width * T_S && y >= 0
		&& y < map->height * T_S)
		if (map->map[y_pos][x_pos] && !(map->map[y_pos][x_pos] == '1'))
			return (FAILDE);
	return (EXIT_SUCCESS);
}
