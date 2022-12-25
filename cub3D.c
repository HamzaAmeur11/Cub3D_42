/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/25 18:08:57 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	dest(t_map *map, int error)
{
	ft_free(map->map);
	mlx_destroy_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	exit(error);
}

double normalize_rad(double angle)
{
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle >= 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

double normalize_deg(double angle)
{
	if (angle < 0)
		angle = 360 + angle;
	if (angle >= 360)
		angle = angle - 360;
	return (angle);
}

void edit_pos_walk(t_map *map)
{
	double new_x;
	double new_y;

	new_x = map->plr.x + map->plr.walk * (map->plr.mov_speed) * cos(map->plr.beta);
	new_y = map->plr.y + map->plr.walk * (map->plr.mov_speed) * sin(map->plr.beta);
	if (map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return ;
	else
	{
		map->plr.x = new_x;	
		map->plr.y = new_y;	
	}
}

void edit_pos_side(t_map *map)
{
	double new_x;
	double new_y;

	new_x = map->plr.x + map->plr.side * (map->plr.mov_speed) * cos(((3 * M_PI) / 2) - map->plr.beta);
	new_y = map->plr.y + map->plr.side * (map->plr.mov_speed) * sin(((3 * M_PI) / 2) - map->plr.beta);
	if (map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return ;
	else
	{
		map->plr.x = new_x;	
		map->plr.y = new_y;	
	}
}

int	moves(int keycode, t_map *map)
{
	// printf("\n\n----------%d---------------str\n", keycode);
	if (keycode == W)
		map->plr.walk = +1;
	else if (keycode == S)
		map->plr.walk = -1;
	else if (keycode == A)
		map->plr.side = -1;
	else if (keycode == D)
		map->plr.side = +1;
	else if (keycode == RIGHT_KEY)
		map->plr.turn = +1;
	else if (keycode == LEFT_KEY)
		map->plr.turn = -1;
	else if (keycode == ESC_KEY)
		dest(map, 1);
	else
		return (0);
	//update data
	if (map->plr.turn != 0)
	{
		map->plr.alpha = normalize_deg(map->plr.alpha + (map->plr.turn * map->plr.rot_speed));
		map->plr.beta = normalize_rad(deg_to_rad(map->plr.alpha));
	}
	//   edit x and y     //
	if (map->plr.walk != 0)
		edit_pos_walk(map);
	if (map->plr.side != 0)
		edit_pos_side(map);
	mlx_clear_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	put_wall(map);
	send_rays(map);
	map->plr.turn = 0;
	map->plr.walk = 0;
	map->plr.side = 0;
	// printf("-------------------------end\n");
	return (EXIT_SUCCESS);
}


void	hook(t_map *map)
{
	mlx_hook(map->mlx_.win_ptr, 17, 0, dest, map);
	mlx_hook(map->mlx_.win_ptr, 2, 0, moves, map);
	mlx_loop(map->mlx_.mlx_ptr);
}



double distence(t_point p, t_point q)
{
	return (sqrt(((p.x - q.x) * (p.x - q.x)) + (p.y - q.y) * (p.y - q.y)));
}

void interaction_pt(t_map *map, t_point *p, double angle)
{
	t_point plr;
	plr.x = map->plr.x;
	plr.y = map->plr.y;
	t_point inter_h;
	t_point inter_v;
	// printf("rad = %f && deg = %f\n", angle, rad_to_deg(angle));
	horiz_inter(map, &inter_h, normalize_rad(angle));
	vertic_inter(map, &inter_v, normalize_rad(angle));
	// printf("end_hor : h_x = %f && h_y = %f\n", inter_h.x, inter_h.y);
	// printf("end_ver : v_x = %f && v_y = %f\n", inter_v.x, inter_v.y);
	// printf("dis vert %f\n", distence(plr, inter_v));
	// printf("dis hor %f\n", distence(plr, inter_h));
	// if ((inter_h.x == -1 && inter_h.y == -1) ||  inter_h.x > map->width * TILE_SIZE || inter_h.y > map->height * TILE_SIZE)
	// 	{/*printf("1V hor(%f , %f) >  verti (%f , %f)  ->", inter_h.x, inter_h.y, inter_v.x, inter_v.y);*/*p = inter_v;	return;}
	// if ((inter_v.x == -1 && inter_v.y == -1) /*||  inter_v.x > map->width * TILE_SIZE || inter_v.y > map->height * TILE_SIZE*/)
	// 	{/*printf("2H ver(%f , %f) > hori(%f , %f)   ->", inter_v.x, inter_v.y, inter_h.x, inter_h.y);*/*p = inter_h;	return;}
	if (distence(plr, inter_h) > distence(plr, inter_v))
		{/*printf("3V hor(%f , %f) >  verti (%f , %f)  ->\n", inter_h.x, inter_h.y, inter_v.x, inter_v.y);*/*p = inter_v;}
	else
		{/*printf("4H ver(%f , %f) > hori(%f , %f)   ->\n", inter_v.x, inter_v.y, inter_h.x, inter_h.y);*/*p = inter_h;}
			
}


void fct(t_map *map, double wall_height, int i)
{
	double top_wall;
	double down_wall;
	int j = -1;

	top_wall = (Y_SIZE / 2) - (wall_height / 2);
	if (top_wall < 0)
		top_wall = 0;
	down_wall = (Y_SIZE / 2) + (wall_height / 2);
	if (down_wall > Y_SIZE)
		down_wall = Y_SIZE;
	while (++j <= Y_SIZE)
	{
		if (j <= top_wall)
			mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->ce);
		else if (j < down_wall && j > top_wall)
			mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, 0x0);
		else if (j >= down_wall)
			mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->fl);
	}
		
}

void put_3d_map(t_map *map)
{
	
	double projec_d;
	double wall_height;
	double d_ray;
	int  i = -1;
	
	while(++i <= X_SIZE)
	{
		d_ray = map->inter[i] * cos(map->ray_angl[i] - map->plr.beta);
		projec_d = (X_SIZE / 2) / tan(FOV_R / 2);
		wall_height = (TILE_SIZE / d_ray) * projec_d;
		fct(map, wall_height, i);
	}
}

void send_rays(t_map *map)
{
	map->ray_angle = map->plr.beta - deg_to_rad(30);
	t_point n;
	map->plr.p.x = map->plr.x;
	map->plr.p.y = map->plr.y;
	printf("rad : %f && deg %f\n", map->plr.beta, map->plr.alpha);
	// interaction_pt(map, &n, map->plr.beta);
	// put_line(map, map->plr.p, n, 0xFF0000);
	int i = -1;
	while (++i < X_SIZE)
	{
		interaction_pt(map, &n, normalize_rad(map->ray_angle));
		map->inter[i] = distence(map->plr.p, n);
		map->ray_angl[i] = map->ray_angle;
		/*store x and y interaction*/

		put_line(map, map->plr.p, n, 0xFF0000);
		map->ray_angle += FOV_R / X_SIZE;
	}
	map->inter[i] = -10;
	put_3d_map(map);
}

int put_2d_map(t_map *map)
{
	map->mlx_.mlx_ptr = mlx_init();
	map->mlx_.win_ptr = mlx_new_window(map->mlx_.mlx_ptr, X_SIZE, Y_SIZE, (char *)"---Cub3D---");
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
	print_tmap(map);
	if (put_2d_map(&map) != EXIT_SUCCESS)
		return (FAILDE);
}