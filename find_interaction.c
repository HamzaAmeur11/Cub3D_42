/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:00 by hameur            #+#    #+#             */
/*   Updated: 2022/12/24 22:50:05 by hameur           ###   ########.fr       */
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


void find_last_point_v(t_map *map, t_point *f, long x_inc, long angle)
{
	// printf("last p : x_inc = %ld && y_inc = %ld\n", x_inc, y_inc);
	double x,y;
	if (map->dir.down)
		y = 0.0000001;
	if (!map->dir.down)
		y = -0.0000001;
	if (map->dir.right)
		x = 0.0000001;
	if (!map->dir.right)
		x = -0.0000001;
	while (f->x >= 0 && f->y >= 0 && f->x <= map->width * TILE_SIZE && f->y <= map->height * TILE_SIZE)
	{
		// printf("f->x = %f && f->y = %f\n", f->x, f->y);
		// printf("map[%f][%f]", f->y / TILE_SIZE, f->x / TILE_SIZE);
		// printf("  %c\n", map->map[(int)(f->y / TILE_SIZE)][(int)(f->x / TILE_SIZE)]);
		if (map->map[(int)((f->y + y) / TILE_SIZE)][(int)((f->x + x) / TILE_SIZE)] == '1')
			return ;
		if ((f->x + x) / TILE_SIZE == (int)((f->x + x) / TILE_SIZE) && (f->y + y) / TILE_SIZE == (int)((f->y + y) / TILE_SIZE))
			if (check_2_walls(map, f, angle) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");return ;}
		f->x += x_inc;
		f->y = map->plr.y + ((f->x - map->plr.x) * tan(deg_to_rad(angle)));
		if (angle == 0 || angle == 180)
			f->y = map->plr.y;
	}
}

void find_last_point_h(t_map *map, t_point *f, long angle, long y_inc)
{
	double x,y;
	int m_x,m_y;
	if (map->dir.down)
		y = 0.0000001;
	if (!map->dir.down)
		y = -0.0000001;
	if (map->dir.right)
		x = 0.0000001;
	if (!map->dir.right)
		x = -0.0000001;
	while (f->x >= 0 && f->y >= 0 && f->x <= map->width * TILE_SIZE && f->y <= map->height * TILE_SIZE)
	{
		m_y = floor((f->y + y) / TILE_SIZE);
		m_x = floor((f->x + x) / TILE_SIZE);
		if (map->map[m_y][m_x] == '1')
			return ;
		if ((f->x + x) / TILE_SIZE == m_x && (f->y + y) / TILE_SIZE == m_y)
			if (check_2_walls(map, f, angle) == EXIT_SUCCESS)
				{printf("zeeeebiiiiii\n");return ;}
		f->y += y_inc;
		f->x = map->plr.x + ((f->y - map->plr.y) / tan(deg_to_rad(angle)));
		if (angle == 90 || angle == 270)
			f->x = map->plr.x;
	}
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

void init_direction(t_bool *dir, double beta)
{
	dir->down = beta > 0 && beta <= M_PI;
	dir->up = !dir->down;
	dir->right = beta > 1.5 * M_PI || beta <= M_PI / 2;
	dir->left = !dir->right;
	// printf("down = %d , up = %d , right = %d , leff= %d\n", dir->down, dir->up, dir->right, dir->left);
}

void v_init_first_point(t_map *map, t_point *f, t_bool *dir, double angle)
{
	f->x = (int)(map->plr.x / TILE_SIZE) * TILE_SIZE;
	if (dir->right)
		f->x += TILE_SIZE;
	f->y = map->plr.y + ((f->x - map->plr.x) * tan(deg_to_rad(angle)));
	if (angle == 0 || angle == 180)
		f->y = map->plr.y;
	// if (dir->up)
	// 	f->y--;
	// if (dir->left)
	// 	f->x--;
	// if (!dir->up)
	// 	f->y++;
	// if (!dir->left)
	// 	f->x++;
	// printf("f->x = %f && f->y = %f\n", f->x, f->y);
}

void vertic_inter(t_map *map, t_point *p, double angle)
{
	t_point f;
	long x_stp;
	long y_stp;

	// printf("\n\n======vertical========\n\n");
	// printf("px = %f && py = %f       X = %i Y = %i\n", map->plr.x, map->plr.y, (int)map->plr.x / TILE_SIZE, (int)map->plr.y / TILE_SIZE);
	init_direction(&map->dir, deg_to_rad(angle));
	v_init_first_point(map, &f, &map->dir, angle);
	x_stp = TILE_SIZE;
	y_stp = TILE_SIZE * tan(deg_to_rad(angle));
	if (y_stp < 0)
		y_stp *= -1;
	
	//check_90 && 270 cases;
	if (angle == 90 || angle == 270)
		{p->x = -1, p->y = -1; return ;}
	if (angle == 0)
		find_last_point_v(map, &f, x_stp, angle);
	else if (angle == 180)
		find_last_point_v(map, &f, -x_stp, angle);
	else if (angle >= 0 && angle < 90)
		find_last_point_v(map, &f, x_stp, angle);
	else if (angle > 90 && angle < 180)
		find_last_point_v(map, &f, -x_stp, angle);
	else if (angle > 180 && angle < 270)
		find_last_point_v(map, &f, -x_stp, angle);
	else if (angle > 270 && angle < 360)
		find_last_point_v(map, &f, x_stp, angle);
	// if (dirction.up)
	// 	f.y++;
	// if (dirction.left)
	// 	f.x++;
	// if (!dirction.up)
	// 	f.y--;
	// if (!dirction.left)
	// 	f.x--;
	p->x = f.x;
	p->y = f.y;
	// printf("end x = %f && i = %d\n", f.x, (int)f.x / TILE_SIZE);
	// printf("end y = %f && j = %d\n", f.y, (int)f.y / TILE_SIZE);
}


void init_stps(t_map *map, t_bool *dirction, long *x_stp, long *y_stp)
{
	(void)map;
	if (dirction->up == 1 && *y_stp > 0)
		*y_stp *= -1;
	if (dirction->down == 1 && *y_stp < 0)
		*y_stp *= -1;
	if (dirction->left == 1 && *x_stp > 0)
		*x_stp *= -1; 
	if (dirction->right == 1 && *x_stp < 0)
		*x_stp *= -1; 
	// if (map->plr.alpha == 90 || map->plr.alpha == 270)
	// 	x_stp = 0;
	// if (map->plr.alpha == 0 || map->plr.alpha == 180)
	// 	y_stp = 0;
	
}

void h_init_first_point(t_map *map, t_point *f, t_bool *dir, double angle)
{
	f->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	if (dir->down)
		f->y += TILE_SIZE;
	f->x = map->plr.x + ((f->y - map->plr.y) / tan(deg_to_rad(angle)));
	if (angle == 90 || angle == 270)
		f->x = map->plr.x;
	// if (dir->up)
	// 	f->y--;
	// if (dir->left)
	// 	f->x--;
	// if (!dir->up)
	// 	f->y++;
	// if (!dir->left)
	// 	f->x++;
	// printf("first p_h f->x = %f && f->y = %f\n", f->x, f->y);

}

int check_if_wall(t_map *map, double x, double y)
{
	int	x_pos;
	int	y_pos;

	x_pos = floor(x / TILE_SIZE);
	y_pos = floor(y / TILE_SIZE);
	if (x >= 0 && x < map->width * TILE_SIZE && y >= 0 && y < map->height * TILE_SIZE) 
		if (map->map[y_pos][x_pos] && !(map->map[y_pos][x_pos] == '1'))
			return (FAILDE);
	return (EXIT_SUCCESS);

}

void find_down_right_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 1, p->y + 1) == FAILDE)
	{
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_down_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 1, p->y + 1) == FAILDE)
	{
		p->x += x_stp;
		p->y += y_stp;
	}
}
void find_up_right_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp < 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x + 1, p->y - 1) == FAILDE)
	{
		p->x += x_stp;
		p->y += y_stp;
	}
}

void find_up_left_h(t_map *map, t_point *p, double angle)
{
	double x_stp;
	double y_stp;
	
	p->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	p->x = map->plr.x + (p->y - map->plr.y) / tan(angle);
	y_stp = -TILE_SIZE;
	x_stp = y_stp / tan(angle);
	if (x_stp > 0)
		x_stp *= -1;
	while (check_if_wall(map, p->x - 1, p->y - 1) == FAILDE)
	{
		p->x += x_stp;
		p->y += y_stp;
	}
}

void horiz_inter(t_map *map, t_point *p, double angle)
{
	t_point f;
	
	if (rad_to_deg(angle) > 0 && rad_to_deg(angle) <= 90)
		find_down_right_h(map, p, angle);
	else if (rad_to_deg(angle) > 90 && rad_to_deg(angle) <= 180)
		find_down_left_h(map, p, angle);
	else if (rad_to_deg(angle) > 180 && rad_to_deg(angle) <= 270)
		find_up_right_h(map, p, angle);
	else if (rad_to_deg(angle) > 270 && rad_to_deg(angle) <= 360)
		find_up_left_h(map, p, angle);















	
	//init first point -> init |x_stp| and |y_stp| -->check 4 cases inside
	// printf("\n\n======hori========\n\n");
	// printf("px = %f && py = %f       X = %i Y = %i\n", map->plr.x, map->plr.y, (int)map->plr.x / TILE_SIZE, (int)map->plr.y / TILE_SIZE);
	// init_direction(&map->dir, deg_to_rad(angle));
	// h_init_first_point(map, &f, &map->dir, angle);
	// y_stp = TILE_SIZE;
	// x_stp = TILE_SIZE / tan(deg_to_rad(angle));
	// if (x_stp < 0)
	// 	x_stp *= -1;
	// //check_0 && 180 cases;
	// if (angle == 0 || angle== 180)
	// 	{p->x = -1, p->y = -1; return ;}
	// if (angle == 90)
	// 	find_last_point_h(map, &f, angle, y_stp);
	// else if (angle == 270)
	// 	find_last_point_h(map, &f, angle, -y_stp);
	// else if (angle >= 0 && angle < 90)
	// 	find_last_point_h(map, &f, angle, y_stp);
	// else if (angle >= 90 && angle < 180)
	// 	find_last_point_h(map, &f, angle, y_stp);
	// else if (angle >= 180 && angle < 270)
	// 	find_last_point_h(map, &f, angle, -y_stp);
	// else if (angle >= 270 && angle < 360)
	// 	find_last_point_h(map, &f, angle, -y_stp);
	// if (dirction.up)
	// 	f.y++;
	// if (dirction.left)
	// 	f.x++;
	// if (!dirction.up)
	// 	f.y--;
	// if (!dirction.left)
	// 	f.x--;
	// p->x = f.x;
	// p->y = f.y;
	// printf("end x = %f  < %f && i = %d\n", f.x, (double)map->width * TILE_SIZE , (int)f.x / TILE_SIZE);
	// printf("end y = %f  < %f && j = %d\n", f.y, (double)map->height * TILE_SIZE, (int)f.y / TILE_SIZE);
}