/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction_v.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:55:48 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/31 22:07:21 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	find_down_right_v(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE)
			&& p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void	find_down_left_v(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE)
			&& p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void	find_up_right_v(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE)
			&& p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void	find_up_left_v(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE)
			&& p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void	vertic_inter(t_map *map, t_point *p, double angle)
{
	p->pos = 1;
	if (rad_to_deg(angle) >= 0 && rad_to_deg(angle) <= 90)
		find_down_right_v(map, p, angle);
	else if (rad_to_deg(angle) > 90 && rad_to_deg(angle) <= 180)
		find_down_left_v(map, p, angle);
	else if (rad_to_deg(angle) > 180 && rad_to_deg(angle) <= 270)
		find_up_left_v(map, p, angle);
	else if (rad_to_deg(angle) > 270 && rad_to_deg(angle) <= 360)
		find_up_right_v(map, p, angle);
}
