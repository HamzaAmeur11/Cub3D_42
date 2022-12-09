/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/09 21:02:12 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"





bool is_player(t_map *map, float i, float j)
{
	float x;
	float y;
	float px;
	float py;
	
	px = map->plr.x;
	py = map->plr.y;
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
		put_square(map, i * 32, j * 32, 0x0000FF);
	else if (c == ' ' || c == '1')
		put_square(map, i * 32, j * 32, 0x00FF00);
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

void put_line(t_map *map)
{
	printf("ALPHA = %f\n", map->plr.alpha);
	float x_m = map->plr.x + cos(map->plr.alpha) * 30;
	float y_m = map->plr.y + sin(map->plr.alpha) * 30;
	float dx = val_abs(map->plr.x - x_m);
	float dy = val_abs(map->plr.y - y_m);
	float x;
	float y;
	if (map->plr.x < x_m)
		x = map->plr.x;
	else
		x = x_m;
	while (x < dx)
	{
		y = map->plr.y + (dy * (x - map->plr.x) / dx);
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, x * 32, y * 32, 0xFF0000);
		x += 0.01;
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
	if (map->plr.turn != 0)
		map->plr.alpha = map->plr.turn * map->plr.rot_speed;
	if (map->plr.walk != 0)
	put_wall(map);
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

int put_2d_map(t_map *map)
{
	map->mlx_.mlx_ptr = mlx_init();
	map->mlx_.win_ptr = mlx_new_window(map->mlx_.mlx_ptr, 32 * map->width, 32 * map->height, "---Cub3D---");
	put_wall(map);
	put_line(map);
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