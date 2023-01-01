/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:00 by hameur            #+#    #+#             */
/*   Updated: 2022/12/31 21:30:00 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"



int check_2_walls(t_map *map, t_point *f, long angle)
{
	if (angle > 0 && angle < 90)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x + 1) / T_S)] == '1'  || 
			map->map[(int)((f->y + 1) / T_S)][(int)((f->x - 1) / T_S)] == '1')
				return (SUCCESS);
	if (angle > 90 && angle < 180)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x - 1) / T_S)] == '1'  || 
			map->map[(int)((f->y + 1) / T_S)][(int)((f->x + 1) / T_S)] == '1')
				return (SUCCESS);
	if ( angle > 180 && angle < 270)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x + 1) / T_S)] == '1'  || 
			map->map[(int)((f->y + 1) / T_S)][(int)((f->x - 1) / T_S)] == '1')
				return (SUCCESS);
	if ( angle > 270 && angle < 360)
		if (map->map[(int)((f->y - 1) / T_S)][(int)((f->x - 1) / T_S)] == '1'  || 
			map->map[(int)((f->y + 1) / T_S)][(int)((f->x + 1) / T_S)] == '1')
				return (SUCCESS);
	return(FAILDE);
}

double val_abs(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

int	check_v(double x)
{
	int i = (int)x;
	double c = x - i;
	if (c >= 1 / 2)
		return (i + 1);
	return (i);
}

// void put_line(t_map *map, t_point n, t_point m, int clr)
// {
// 	double dx = m.x - n.x;
// 	double dy = m.y - n.y;
// 	int i = -1;
// 	double x = n.x, y = n.y;
// 	int steps;
// 	if (val_abs(dx) > val_abs(dy))
// 		steps = val_abs(dx);
// 	else
// 		steps = val_abs(dy);
	
// 	double x_inc = (double)dx / (double)steps;
// 	double y_inc = (double)dy / (double)steps;
// 	if (x_inc > 0 && n.x > m.x)
// 		x_inc *= -1;
// 	if (y_inc > 0 && n.y > m.y)
// 		y_inc *= -1;
// 	while (++i < steps)
// 	{
// 		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x, y, clr);
// 		x += x_inc;
// 		y += y_inc;
// 	}
// }



int check_if_wall(t_map *map, double x, double y)
{
	int	x_pos;
	int	y_pos;

	x_pos = floor(x / T_S);
	y_pos = floor(y / T_S);
	if (x >= 0 && x < map->width * T_S && y >= 0 && y < map->height * T_S) 
		if (map->map[y_pos][x_pos] && !(map->map[y_pos][x_pos] == '1'))
			return (FAILDE);
	return (SUCCESS);

}


void find_down_right_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->x = floor(map->plr.x / T_S) * T_S + T_S;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = T_S;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_down_left_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->x = floor(map->plr.x / T_S) * T_S;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -T_S;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}
void find_up_right_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->x = floor(map->plr.x / T_S) * T_S + T_S;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = T_S;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_left_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->x = floor(map->plr.x / T_S) * T_S;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -T_S;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void vertic_inter(t_map *map, t_point *p, double angle)
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


void find_down_right_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->y = floor(map->plr.y / T_S) * T_S + T_S;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = T_S;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_down_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->y = floor(map->plr.y / T_S) * T_S + T_S;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = T_S;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_right_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->y = floor(map->plr.y / T_S) * T_S;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -T_S;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;

	p->y = floor(map->plr.y / T_S) * T_S;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -T_S;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / T_S == (int)(p->x / T_S) && p->y / T_S == (int)(p->y / T_S))
			if (check_2_walls(map, p, rad_to_deg(angle)) == SUCCESS)
				break ;
		p->x += x_stp;
		p->y += y_stp;
	}
}

void horiz_inter(t_map *map, t_point *p, double angle)
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