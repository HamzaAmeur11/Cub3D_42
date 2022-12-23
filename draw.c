/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:38:42 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/23 14:40:01 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_car(t_map map, int x, int y, int color)
{
	int	i;
	int	j;

	i = y + 1;
	while(i < y + MINI_SIZE)
	{
		j = x + 1;
		while (j < x + MINI_SIZE)
		{
			my_mlx_pixel_put(&map, j, i, color);
			j++;
		}
		i++;
	}
}

void draw_walls(t_map map)
{
	int	y;
	int	x;
	int	i;
	int	j;

	y = 0;
	while (map.map[y] != NULL)
	{
		x = 0;
		while (map.map[y][x] != '\0')
		{
			i = y;
			j = x;
			if (map.map[y][x] == '1')
				draw_car(map, j * MINI_SIZE, i * MINI_SIZE, 0x808080);
			else if (map.map[y][x] == '0')
				draw_car(map, j * MINI_SIZE, i * MINI_SIZE, 0xFFFFFF);
			else if (map.map[y][x] == 'W')
				draw_car(map, j * MINI_SIZE, i * MINI_SIZE, 0xFFFFFF);
			else if (map.map[y][x] == ' ')
				draw_car(map, j * MINI_SIZE, y * MINI_SIZE, 0x008000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map.mlx.mlx, map.mlx.wind, map.mlx.img, 0, 0);
}

void	draw_player(t_map map, float x, float y, int color)
{
	float	i;
	float	j;

	i = y + 1;
	while(i < y + MINI_SIZE)
	{
		j = x + 1;
		while (j < x + MINI_SIZE)
		{
			if (is_player(&map, j, i)/* && map.plr.x == j && map.plr.y == i*/)
				my_mlx_pixel_put(&map, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_map map)
{
	draw_walls(map);
	draw_player(map, map.plr.x * MINI_SIZE, map.plr.y * MINI_SIZE, 0xFF0000);
	mlx_put_image_to_window(map.mlx.mlx, map.mlx.wind, map.mlx.img, 0, 0);
}