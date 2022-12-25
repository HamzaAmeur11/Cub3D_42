/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:00 by hameur            #+#    #+#             */
/*   Updated: 2022/12/25 17:23:57 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"



int check_2_walls(t_map *map, t_point *f, long angle)
{
	if (angle > 0 && angle < 90)
		if (map->map[(int)((f->y - 1) / TILE_SIZE)][(int)((f->x + 1) / TILE_SIZE)] == '1'  || 
			map->map[(int)((f->y + 1) / TILE_SIZE)][(int)((f->x - 1) / TILE_SIZE)] == '1')
				return (EXIT_SUCCESS);
	if (angle > 90 && angle < 180)
		if (map->map[(int)((f->y - 1) / TILE_SIZE)][(int)((f->x - 1) / TILE_SIZE)] == '1'  || 
			map->map[(int)((f->y + 1) / TILE_SIZE)][(int)((f->x + 1) / TILE_SIZE)] == '1')
				return (EXIT_SUCCESS);
	if ( angle > 180 && angle < 270)
		if (map->map[(int)((f->y - 1) / TILE_SIZE)][(int)((f->x + 1) / TILE_SIZE)] == '1'  || 
			map->map[(int)((f->y + 1) / TILE_SIZE)][(int)((f->x - 1) / TILE_SIZE)] == '1')
				return (EXIT_SUCCESS);
	if ( angle > 270 && angle < 360)
		if (map->map[(int)((f->y - 1) / TILE_SIZE)][(int)((f->x - 1) / TILE_SIZE)] == '1'  || 
			map->map[(int)((f->y + 1) / TILE_SIZE)][(int)((f->x + 1) / TILE_SIZE)] == '1')
				return (EXIT_SUCCESS);
	return(FAILDE);
}


// void find_last_point_v(t_map *map, t_point *f, long x_inc, long angle)
// {
// 	// printf("last p : x_inc = %ld && y_inc = %ld\n", x_inc, y_inc);
// 	double x,y;
// 	if (map->dir.down)
// 		y = 0.0000001;
// 	if (!map->dir.down)
// 		y = -0.0000001;
// 	if (map->dir.right)
// 		x = 0.0000001;
// 	if (!map->dir.right)
// 		x = -0.0000001;
// 	while (f->x >= 0 && f->y >= 0 && f->x <= map->width * TILE_SIZE && f->y <= map->height * TILE_SIZE)
// 	{
// 		// printf("f->x = %f && f->y = %f\n", f->x, f->y);
// 		// printf("map[%f][%f]", f->y / TILE_SIZE, f->x / TILE_SIZE);
// 		// printf("  %c\n", map->map[(int)(f->y / TILE_SIZE)][(int)(f->x / TILE_SIZE)]);
// 		if (map->map[(int)((f->y + y) / TILE_SIZE)][(int)((f->x + x) / TILE_SIZE)] == '1')
// 			return ;
// 		if ((f->x + x) / TILE_SIZE == (int)((f->x + x) / TILE_SIZE) && (f->y + y) / TILE_SIZE == (int)((f->y + y) / TILE_SIZE))
// 			if (check_2_walls(map, f, angle) == EXIT_SUCCESS)
// 				{printf("zeeeebiiiiii\n");return ;}
// 		f->x += x_inc;
// 		f->y = map->plr.y + ((f->x - map->plr.x) * tan(deg_to_rad(angle)));
// 		if (angle == 0 || angle == 180)
// 			f->y = map->plr.y;
// 	}
// }

// void find_last_point_h(t_map *map, t_point *f, long angle, long y_inc)
// {
// 	double x,y;
// 	int m_x,m_y;
// 	if (map->dir.down)
// 		y = 0.0000001;
// 	if (!map->dir.down)
// 		y = -0.0000001;
// 	if (map->dir.right)
// 		x = 0.0000001;
// 	if (!map->dir.right)
// 		x = -0.0000001;
// 	while (f->x >= 0 && f->y >= 0 && f->x <= map->width * TILE_SIZE && f->y <= map->height * TILE_SIZE)
// 	{
// 		m_y = floor((f->y + y) / TILE_SIZE);
// 		m_x = floor((f->x + x) / TILE_SIZE);
// 		if (map->map[m_y][m_x] == '1')
// 			return ;
// 		if ((f->x + x) / TILE_SIZE == m_x && (f->y + y) / TILE_SIZE == m_y)
// 			if (check_2_walls(map, f, angle) == EXIT_SUCCESS)
// 				{printf("zeeeebiiiiii\n");return ;}
// 		f->y += y_inc;
// 		f->x = map->plr.x + ((f->y - map->plr.y) / tan(deg_to_rad(angle)));
// 		if (angle == 90 || angle == 270)
// 			f->x = map->plr.x;
// 	}
// }

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

void put_line(t_map *map, t_point n, t_point m, int clr)
{
	//find the point of interaction with the wall M(x_1 , y_1)
	// printf("\n=====put map=====\n");
	// printf("start : x = %f && y = %f\n", m.x, m.y);
	// printf("end   : x = %f && y = %f\n", n.x, n.y);
	double dx = m.x - n.x;
	double dy = m.y - n.y;
	int i = -1;
	double x = n.x, y = n.y;
	int steps;
	if (val_abs(dx) > val_abs(dy))
		steps = val_abs(dx);
	else
		steps = val_abs(dy);
	
	// printf("dx : %f && dy = %f && steps = %d\n", dx, dy, steps);
	double x_inc = (double)dx / (double)steps;
	double y_inc = (double)dy / (double)steps;
	if (x_inc > 0 && n.x > m.x)
		x_inc *= -1;
	if (y_inc > 0 && n.y > m.y)
		y_inc *= -1;
	// printf("x_inc : %f && y_inc = %f\n", x_inc, y_inc);
	// printf("first x = %f && y = %f\n", x,y);
	while (++i < steps)
	{
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x, y, clr);
		x += x_inc;
		y += y_inc;
	}
}



int check_if_wall(t_map *map, double x, double y)
{
	int	x_pos;
	int	y_pos;

	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);
	// if (!(x >= 0 && x < map->width * TILE_SIZE && y >= 0 && y < map->height * TILE_SIZE))
	// 	printf("tttssttt\n");
	if (x >= 0 && x < map->width * TILE_SIZE && y >= 0 && y < map->height * TILE_SIZE) 
		if (map->map[y_pos][x_pos] && !(map->map[y_pos][x_pos] == '1'))
			return (FAILDE);
	return (EXIT_SUCCESS);

}


void find_down_right_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_down_left_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp < 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}
void find_up_right_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_left_v(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->x = floor(map->plr.x / TILE_SIZE) * TILE_SIZE;
	p->y = map->plr.y + (p->x - map->plr.x) * tan(angle);
	x_stp = -TILE_SIZE;
	y_stp = x_stp * tan(angle);
	if (y_stp > 0)
		y_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void vertic_inter(t_map *map, t_point *p, double angle)
{
	// printf("----------ver :\nangle = %f\n", angle);

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
	// printf("angle = %f\n", rad_to_deg(angle));

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_down_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y + 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_right_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	// printf("angle = %f\n", rad_to_deg(angle));

	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 0.0001, p->y - 0.0001) == FAILDE)
	{
		if (p->x / TILE_SIZE == (int)(p->x / TILE_SIZE) && p->y / TILE_SIZE == (int)(p->y / TILE_SIZE))
			if (check_2_walls(map, p, rad_to_deg(angle)) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");break ;}
		p->x += x_stp;
		p->y += y_stp;
	}
}

void horiz_inter(t_map *map, t_point *p, double angle)
{	
	// printf("----------hor :\nangle = %f\n",angle);
	if (rad_to_deg(angle) >= 0 && rad_to_deg(angle) <= 90)
		find_down_right_h(map, p, angle);
	else if (rad_to_deg(angle) > 90 && rad_to_deg(angle) <= 180)
		find_down_left_h(map, p, angle);
	else if (rad_to_deg(angle) > 180 && rad_to_deg(angle) <= 270)
		find_up_left_h(map, p, angle);
	else if (rad_to_deg(angle) > 270 && rad_to_deg(angle) <= 360)
		find_up_right_h(map, p, angle);
}