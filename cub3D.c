/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/17 22:37:50 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"





bool is_player(t_map *map, float i, float j)
{
	float x;
	float y;
	float px;
	float py;
	
	px = map->plr.x / TILE_SIZE;
	py = map->plr.y / TILE_SIZE;
	x = i / TILE_SIZE;
	y = j / TILE_SIZE;
	return ((x-px)*(x-px) + (y-py)*(y-py) <= 0.16 * 0.16);
}



void put_square(t_map *map, int start_x, int start_y, int clr)
{
	int i = start_x;
	int j = start_y;

	while (i < start_x + TILE_SIZE - 1)
	{
		j = start_y;
		while (j < start_y + TILE_SIZE - 1)
		{
			
			if (is_player(map, i, j))
				mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j++, 0xFF0000);
			else
				mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j++, clr);
		}
		i++;
	}
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

int	dest(t_map *map, int error)
{
	ft_free(map->map);
	mlx_destroy_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	exit(error);
}

float normalize_angle(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	if (angle > 360)
		angle = angle - 360;
	return (angle);
}

int	moves(int keycode, t_map *map)
{
	// printf("\n\n-------------------------str\n");
	if (keycode == UP_KEY)
		map->plr.walk = +1;
	else if (keycode == DOWN_KEY)
		map->plr.walk = -1;
	if (keycode == RIGHT_KEY)
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
		// map->plr.beta += (map->plr.turn * map->plr.rot_speed);
		// printf("beta -  0 < %f < %f\n", map->plr.beta, 2 * M_PI);
		// map->plr.beta = normalize_angle(map->plr.beta);
		// map->plr.alpha = rad_to_deg(map->plr.beta);
		// printf("before alpha = %f\n", map->plr.alpha);
		map->plr.alpha = normalize_angle(map->plr.alpha + (map->plr.turn * 2));
		// printf("after alpha = %f\n", map->plr.alpha);
		map->plr.beta = deg_to_rad(map->plr.alpha);
		// printf("beta + 0 < %f < %f\n", map->plr.beta, 2 * M_PI);
		
	}
	//   edit x and y     //
	//if (map->plr.walk != 0)
	mlx_clear_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	put_wall(map);
	send_rays(map);
	map->plr.turn = 0;
	map->plr.walk = 0;
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

void interaction_pt(t_map *map, t_point *p)
{
	t_point plr;
	plr.x = map->plr.x;
	plr.y = map->plr.y;
	t_point inter_h;
	t_point inter_v;
	horiz_inter(map, &inter_h);
	vertic_inter(map, &inter_v);
	// printf("dis vert %f\n", distence(plr, inter_v));
	// printf("dis hor %f\n", distence(plr, inter_h));
	// if (inter_h.x == -1 && inter_h.y == -1)
	// 	{*p = inter_v;	return;}
	// if (inter_v.x == -1 && inter_v.y == -1)
	// 	{*p = inter_h;	return;}
		
	if (distence(plr, inter_h) > distence(plr, inter_v))
		{*p = inter_v;}
	else
		{*p = inter_h;}
			
}

void send_rays(t_map *map)
{
	t_point m,n;
	m.x = map->plr.x;
	m.y = map->plr.y;
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