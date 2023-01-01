/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction_h.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:54:21 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/31 22:04:18 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	find_down_right_h(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
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

void	find_down_left_h(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
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

void	find_up_right_h(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
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

void	find_up_left_h(t_map *map, t_point *p, double angle)
{
	double	x_stp;
	double	y_stp;

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
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

void	horiz_inter(t_map *map, t_point *p, double angle)
{	
	p->pos = 0;
	if (rad_to_deg(angle) >= 0 && rad_to_deg(angle) <= 90)
		find_down_right_h(map, p, angle);
	else if (rad_to_deg(angle) > 90 && rad_to_deg(angle) <= 180)
		find_down_left_h(map, p, angle);
	else if (rad_to_deg(angle) > 180 && rad_to_deg(angle) <= 270)
		find_up_left_h(map, p, angle);
	else if (rad_to_deg(angle) > 270 && rad_to_deg(angle) <= 360)
		find_up_right_h(map, p, angle);
}
