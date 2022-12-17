/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:00 by hameur            #+#    #+#             */
/*   Updated: 2022/12/17 22:32:41 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void find_last_point(t_map *map, t_point *f, long x_inc, long y_inc)
{
	// printf("last p : x_inc = %ld && y_inc = %ld\n", x_inc, y_inc);
	while (f->x >= 0 && f->y >= 0 && f->x <= map->width * TILE_SIZE && f->y <= map->height * TILE_SIZE)
	{
		// printf("last p :map[%d][%d]", (int)(f->y / TILE_SIZE), (int)(f->x / TILE_SIZE));
		// printf("  | %c |\n", map->map[(int)(f->y / TILE_SIZE)][(int)(f->x / TILE_SIZE)]);
		if (map->map[(int)(f->y / TILE_SIZE)][(int)(f->x / TILE_SIZE)] == '1')
			return ;
		f->x += x_inc;
		f->y += y_inc;
	}
}

float val_abs(float a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

int	check_v(float x)
{
	int i = (int)x;
	float c = x - i;
	if (c >= 1 / 2)
		return (i + 1);
	return (i);
}

void put_line(t_map *map, t_point n, t_point m)
{
	//find the point of interaction with the wall M(x_1 , y_1)
	// printf("\n=====put map=====\n");
	// printf("start : x = %f && y = %f\n", m.x, m.y);
	// printf("end   : x = %f && y = %f\n", n.x, n.y);
	float dx = m.x - n.x;
	float dy = m.y - n.y;
	int i = -1;
	float x = n.x, y = n.y;
	int steps;
	if (val_abs(dx) > val_abs(dy))
		steps = val_abs(dx);
	else
		steps = val_abs(dy);
	
	// printf("dx : %f && dy = %f && steps = %d\n", dx, dy, steps);
	float x_inc = (float)dx / (float)steps;
	float y_inc = (float)dy / (float)steps;
	if (x_inc > 0 && n.x > m.x)
		x_inc *= -1;
	if (y_inc > 0 && n.y > m.y)
		y_inc *= -1;
	// printf("x_inc : %f && y_inc = %f\n", x_inc, y_inc);
	// printf("first x = %f && y = %f\n", x,y);
	while (++i < steps)
	{
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x, y, 0xFF0F0F);
		x += x_inc;
		y += y_inc;
	}
}

void init_direction(t_bool *dir, float beta)
{
	dir->down = beta > 0 && beta <= M_PI;
	dir->up = !dir->down;
	dir->right = beta > 1.5 * M_PI || beta <= M_PI / 2;
	dir->left = !dir->right;
	// printf("down = %d , up = %d , right = %d , leff= %d\n", dir->down, dir->up, dir->right, dir->left);
}

void v_init_first_point(t_map *map, t_point *f, t_bool *dir)
{
	f->x = (int)(map->plr.x / TILE_SIZE) * TILE_SIZE;
	if (dir->right)
		f->x += TILE_SIZE;
	f->y = map->plr.y + ((f->x - map->plr.x) * tan(map->plr.beta));
	if (map->plr.alpha == 0 || map->plr.alpha == 180)
		f->y = map->plr.y;
	// printf("f->x = %f && f->y = %f\n", f->x, f->y);
}

void vertic_inter(t_map *map, t_point *p)
{
	t_point f;
	t_bool dirction;
	long x_stp;
	long y_stp;

	// printf("\n\n======vertical========\n\n");
	// printf("px = %f && py = %f       X = %i Y = %i\n", map->plr.x, map->plr.y, (int)map->plr.x / TILE_SIZE, (int)map->plr.y / TILE_SIZE);
	init_direction(&dirction, map->plr.beta);
	v_init_first_point(map, &f, &dirction);
	x_stp = TILE_SIZE;
	y_stp = TILE_SIZE * tan(map->plr.beta);
	if (y_stp < 0)
		y_stp *= -1;
	if (dirction.up)
		f.y--;
	if (dirction.left)
		f.x--;
	//check_90 && 270 cases;
	if (map->plr.alpha == 90 || map->plr.alpha == 270)
		{p->x = MAXFLOAT, p->y = MAXFLOAT; return ;}
	if (map->plr.alpha == 0)
		find_last_point(map, &f, x_stp, 0);
	else if (map->plr.alpha == 180)
		find_last_point(map, &f, -x_stp, 0);
	else if (map->plr.alpha >= 0 && map->plr.alpha < 90)
		find_last_point(map, &f, x_stp, y_stp);
	else if (map->plr.alpha > 90 && map->plr.alpha < 180)
		find_last_point(map, &f, -x_stp, y_stp);
	else if (map->plr.alpha > 180 && map->plr.alpha < 270)
		find_last_point(map, &f, -x_stp, -y_stp);
	else if (map->plr.alpha > 270 && map->plr.alpha < 360)
		find_last_point(map, &f, x_stp, -y_stp);
	p->x = f.x;
	p->y = f.y;






	// init_direction(&dirction, map->plr.beta);
	// f.x = (int)(map->plr.x / TILE_SIZE) * TILE_SIZE;//*n
	// if (dirction.right == 1)
	// 	f.x += TILE_SIZE;
	// f.y = map->plr.y + ((map->plr.x - f.x) * tan(map->plr.beta));//*n
	// if (map->plr.alpha == 90 || map->plr.alpha == 270)
	// 	f.y = map->plr.y;
	// // printf("fx = %f && i = %d\n", f.x, (int)f.x / TILE_SIZE);
	// // printf("fy = %f && j = %d\n", f.y, (int)f.y / TILE_SIZE);
	// if (map->plr.alpha == 90 || map->plr.alpha == 270)
	// 	{p->x = -1, p->y =-1; return;}
	// if (dirction.left == 1)
	// 	f.x--;
	
	// x_stp = TILE_SIZE;
	// y_stp = x_stp * tan(map->plr.beta);
	// init_stps(map, &dirction, &x_stp, &y_stp);
	// // if (map->plr.alpha == 90 || map->plr.alpha == 270)
	// // 	y_stp = 0;
	// // printf("x_stp = %ld && y_stp = %ld\n", x_stp, y_stp);
	// while (f.x >= 0 && f.x <= map->width * TILE_SIZE && f.y >= 0 && f.y <= map->height * TILE_SIZE)
	// {
	// 	// printf("char[%d][%d]\n",(int)(f.y / TILE_SIZE),(int)(f.x / TILE_SIZE));
	// 	if (map->map[(int)(f.y / TILE_SIZE)][(int)(f.x / TILE_SIZE)] == '1')
	// 		break ;
	// 	f.x += x_stp; 
	// 	f.y += y_stp; 
	// }
	// p->x = f.x;
	// p->y = f.y;
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

void h_init_first_point(t_map *map, t_point *f, t_bool *dir)
{
	f->y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;
	if (dir->down)
		f->y += TILE_SIZE;
	f->x = map->plr.x + ((f->y - map->plr.y) / tan(map->plr.beta));
	if (map->plr.alpha == 90 || map->plr.alpha == 270)
		f->x = map->plr.x;
	// printf("f->x = %f && f->y = %f\n", f->x, f->y);

}



void horiz_inter(t_map *map, t_point *p)
{
	t_point f;
	t_bool dirction;
	long x_stp;
	long y_stp;
	
	//init first point -> init |x_stp| and |y_stp| -->check 4 cases inside
	// printf("\n\n======hori========\n\n");
	// printf("px = %f && py = %f       X = %i Y = %i\n", map->plr.x, map->plr.y, (int)map->plr.x / TILE_SIZE, (int)map->plr.y / TILE_SIZE);
	init_direction(&dirction, map->plr.beta);
	h_init_first_point(map, &f, &dirction);
	y_stp = TILE_SIZE;
	x_stp = TILE_SIZE / tan(map->plr.beta);
	if (x_stp < 0)
		x_stp *= -1;
	//check_0 && 180 cases;
	if (dirction.up)
		f.y--;
	if (dirction.left)
		f.x--;
	if (map->plr.alpha == 0 || map->plr.alpha == 180)
		{p->x = MAXFLOAT, p->y = MAXFLOAT; return ;}
	if (map->plr.alpha == 90)
		find_last_point(map, &f, 0, y_stp);
	else if (map->plr.alpha == 270)
		find_last_point(map, &f, 0, -y_stp);
	else if (map->plr.alpha >= 0 && map->plr.alpha < 90)
		find_last_point(map, &f, x_stp, y_stp);
	else if (map->plr.alpha >= 90 && map->plr.alpha < 180)
		find_last_point(map, &f, -x_stp, y_stp);
	else if (map->plr.alpha >= 180 && map->plr.alpha < 270)
		find_last_point(map, &f, -x_stp, -y_stp);
	else if (map->plr.alpha >= 270 && map->plr.alpha < 360)
		find_last_point(map, &f, x_stp, -y_stp);
	p->x = f.x;
	p->y = f.y;

	
	// f.y = floor(map->plr.y / TILE_SIZE) * TILE_SIZE;//*n
	// if (dirction.down == 0)
	// 	f.y += TILE_SIZE; 
	// f.x = map->plr.x + ((f.y - map->plr.y) / tan(map->plr.beta));//*n
	// if (dirction.down == 0)
	// 	f.y--;
	// if (map->plr.alpha == 90 || map->plr.alpha == 270)
	// 	f.x = map->plr.x;
	// if (map->plr.alpha == 0 || map->plr.alpha == 180)
	// 	{p->x = -1, p->y =-1; return;}
	// y_stp = TILE_SIZE;
	// x_stp = TILE_SIZE / tan(map->plr.beta);
	// init_stps(map, &dirction, &x_stp, &y_stp);
	// while (f.x >= 0  && f.y >= 0)
	// {
	// 	if (map->map[(int)(f.y / TILE_SIZE)][(int)(f.x / TILE_SIZE)] == '1')
	// 		break ;
	// 	f.x += x_stp; 
	// 	f.y += y_stp;
	// 	if (f.x > map->width * TILE_SIZE || f.y > map->height * TILE_SIZE)
	// 	{printf("wa l9lawi khdem\n"); break;}
	// }
	// p->x = f.x;
	// p->y = f.y;
	
// 	printf("end x = %f  < %f && i = %d\n", f.x, (float)map->width * TILE_SIZE , (int)f.x / TILE_SIZE);
// 	printf("end y = %f  < %f && j = %d\n", f.y, (float)map->height * TILE_SIZE, (int)f.y / TILE_SIZE);
}