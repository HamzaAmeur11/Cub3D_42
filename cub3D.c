/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/13 22:09:05 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"





bool is_player(t_map *map, float i, float j)
{
	float x;
	float y;
	float px;
	float py;
	
	px = map->plr.x / 32;
	py = map->plr.y / 32;
	x = i / 32;
	y = j / 32;
	return ((x-px)*(x-px) + (y-py)*(y-py) <= 0.16 * 0.16);
}



void put_square(t_map *map, int start_x, int start_y, int clr)
{
	int i = start_x;
	int j = start_y;

	while (i < start_x + 32 - 1)
	{
		j = start_y;
		while (j < start_y + 32 - 1)
		{
			
			if (is_player(map, i, j))
				mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j++, 0xFF0000);
			else
				mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j++, clr);
		}
		i++;
	}
	// put_line(map);
}

int is_upper_char(char c)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void put_char(t_map *map, char c, int i, int j)
{
	if (c == '0' || is_upper_char(c) == EXIT_SUCCESS)
		put_square(map, i * TILE_SIZE, j * TILE_SIZE, 0x0000FF);
	else if (c == ' ' || c == '1')
		put_square(map, i * TILE_SIZE, j * TILE_SIZE, 0x00FF00);
}

void put_wall(t_map *map)
{
	int i = -1;
	int j = -1;

	while (map->map[++i] != NULL)
	{
		j = -1;
		while (map->map[i][++j] != 0)
			put_char(map, map->map[i][j], j, i);
	}
}

float val_abs(float a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

// void put_line(t_map *map)
// {
// 	printf("ALPHA = %f\n", map->plr.alpha);
// 	float x_m = map->plr.x + cos(map->plr.alpha) * 30;
// 	float b = map->plr.y - tan(map->plr.alpha) * map->plr.x;
// 	float x;
// 	float z;
// 	float y;
// 	if (map->plr.x < x_m)
// 		x = map->plr.x,z = x_m;
// 	else
// 		x = x_m, z = map->plr.x;
// 	if (map->plr.x == x_m)
// 	{
// 		y = tan(map->plr.alpha) * x + b;
// 		while (y < map->height)
// 		{
// 			mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x * 32, y * 32, 0xFF0000);
// 			y += 0.0001;
// 		}
// 	}
// 	while (x < z)
// 	{
// 		y = tan(map->plr.alpha) * x + b;
// 		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x * 32, y * 32, 0xFF0000);
// 		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x * 32 - 1, y * 32, 0xFF0000);
// 		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x * 32, y * 32 - 1, 0xFF0000);
// 		x += 0.0001;
// 	}
// }

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
	printf("mx = %f && my = %f\n", m.x, m.y);
	printf("nx = %f && ny = %f\n", n.x, n.y);
	float dx = m.x - n.x;
	float dy = m.y - n.y;
	int i = -1;
	float x = n.x, y = n.y;
	int steps;
	if (val_abs(dx) > val_abs(dy))
		steps = val_abs(dx);
	else
		steps = val_abs(dy);
	printf("dx : %f && dy = %f && steps = %d\n", dx, dy, steps);
	float x_inc = (float)dx / (float)steps;
	float y_inc = (float)dy / (float)steps;
	printf("x_inc : %f && y_inc = %f\n", x_inc, y_inc);
		printf("first x = %f && y = %f\n", x,y);
	while (++i < steps * TILE_SIZE && (x != m.x || x_inc == 0) && (y != m.y || y_inc == 0))
	{
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x, y, 0xFF0F0F);
		x += x_inc;
		y += y_inc;
	}
}

int	dest(t_map *map, int error)
{
	ft_free(map->map);
	mlx_destroy_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	exit(error);
}


int	moves(int keycode, t_map *map)
{
	if (keycode == UP_KEY)
		map->plr.walk = +1;
	else if (keycode == DOWN_KEY)
		map->plr.walk = -1;
	else if (keycode == RIGHT_KEY)
		map->plr.turn = +1;
	else if (keycode == LEFT_KEY)
		map->plr.turn = -1;
	else if (keycode == ESC_KEY)
		dest(map, 1);
	//update data
	printf("--->key code %d\n", keycode);
	if (map->plr.turn != 0)
	{
		map->plr.beta += map->plr.turn * map->plr.rot_speed * 2;
		map->plr.alpha = rad_to_deg(map->plr.beta);
		printf("alpha = %f\n", map->plr.alpha);
	}
	if (map->plr.turn != 0)
	{
		map->plr.x += map->plr.mov_speed * map->plr.walk * 32;
	}
	mlx_clear_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	put_wall(map);
	send_rays(map);
	map->plr.turn = 0;
	map->plr.walk = 0;
	return (EXIT_SUCCESS);
}


void	hook(t_map *map)
{
	mlx_hook(map->mlx_.win_ptr, 17, 0, dest, map);
	mlx_hook(map->mlx_.win_ptr, 2, 0, moves, map);
	mlx_loop(map->mlx_.mlx_ptr);
}

// void vertic_inter(t_map *map, t_point *p)
// {
	
// }
void horiz_inter(t_map *map, t_point *p)
{
	t_point f;
	long x_stp;
	long y_stp;

	//p twsal *32
	printf("px = %f && py = %f       X = %i Y = %i\n", map->plr.x, map->plr.y, (int)map->plr.x / 32, (int)map->plr.y / 32);
	f.y = (int)(map->plr.y / 32) * 32;//*n
	f.x = map->plr.x + ((map->plr.y - f.y) / tan(map->plr.beta));//*n
	if (map->plr.alpha == 90 || map->plr.alpha == 270)
		f.x = map->plr.x;
	printf("fx = %f && i = %d\n", f.x, (int)f.x / 32);
	printf("fy = %f && j = %d\n", f.y, (int)f.y / 32);
	y_stp = TILE_SIZE;
	x_stp = y_stp / tan(map->plr.beta);
	if (map->plr.alpha == 90 || map->plr.alpha == 270)
		x_stp = 0;
	printf("x_stp = %ld && y_stp = %ld\n", x_stp, y_stp);
	while (1)
	{
		
		printf("char[%d][%d]\n",(int)f.y / 32,(int)f.x / 32);
		if (map->map[(int)f.y / 32][(int)f.x / 32] == '1')
			break ;
		f.x += x_stp; 
		f.y += y_stp; 
	}
	p->x = f.x;
	p->y = f.y;
	printf("end x = %f && i = %d\n", f.x, (int)f.x / 32);
	printf("end y = %f && j = %d\n", f.y, (int)f.y / 32);
}

void interaction_pt(t_map *map, t_point *p)
{
	t_point inter_h;
	// t_point inter_v;
	horiz_inter(map, &inter_h);
	// vertic_inter(map, &inter_v);
	p->x = inter_h.x;
	p->y = inter_h.y;
}

void send_rays(t_map *map)
{
	t_point m,n;
	m.x = map->plr.x;
	m.y = map->plr.y;
	// n.y = 33;
	// n.x = 48;
	// if (map->plr.alpha == 0)
	// {
	// 	printf("map---------1\n");
	// 	n.x = map->width * 32;
	// 	n.y = map->plr.y * 32;			
	// }
	// else if (map->plr.alpha == 180)
	// {
	// 	printf("map---------2\n");
	// 	n.x = 0;
	// 	n.y = map->plr.y * 32;
	// }
	// else if (map->plr.alpha == 90)
	// {
	// 	printf("map---------3\n");
	// 	n.x = map->plr.x * 32;
	// 	n.y = 0;
	// }
	// else if (map->plr.alpha == 270)
	// {
	// 	printf("map---------4\n");
	// 	n.x = map->plr.x * 32;
	// 	n.y = map->height * 32;
	// }
	// else
		interaction_pt(map, &n);
	
	// printf("point inter : x ; %f y ; %f\n", n.x, n.y);
	put_line(map, m, n);
}

int put_2d_map(t_map *map)
{
	map->mlx_.mlx_ptr = mlx_init();
	map->mlx_.win_ptr = mlx_new_window(map->mlx_.mlx_ptr, TILE_SIZE * map->width, TILE_SIZE * map->height, "---Cub3D---");
	put_wall(map);
	send_rays(map);
	hook(map);
	return (0);
}

int main(int ac, char **av)
{
	t_map map;
	
	if (ac != 2)
		return(error_args(ac));
	if (parse_map(&map, av[1]) != EXIT_SUCCESS)
		return (FAILDE);
	ft_resulotion(&map);
	// print_tmap(map);
	if (put_2d_map(&map) != EXIT_SUCCESS)
		return (FAILDE);
}