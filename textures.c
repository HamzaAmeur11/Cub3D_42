/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:45:06 by megrisse          #+#    #+#             */
/*   Updated: 2023/01/01 01:54:46 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_exit(void)
{
	printf("TEXTURE ERROR !!\n");
	exit(1);
}

int	check_texture(t_map *map, int key)
{
	if (key == 0)
	{
		if (!map->north.img || !map->south.img
			|| !map->east.img || !map->west.img)
			ft_exit();
	}
	else if (key == 1)
	{
		if (!map->north.addr || !map->south.addr
			|| !map->east.addr || !map->west.addr)
			ft_exit();
	}
	return (EXIT_SUCCESS);
}

void	get_texture(t_map *map)
{
	map->north.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			map->no, &map->north.w, &map->north.h);
	map->south.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			map->so, &map->south.w, &map->south.h);
	map->east.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			map->ea, &map->east.w, &map->east.h);
	map->west.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			map->we, &map->west.w, &map->west.h);
	check_texture(map, 0);
	map->north.addr = (int *)mlx_get_data_addr(map->north.img,
			&map->north.bpp, &map->north.sl, &map->north.end);
	map->south.addr = (int *)mlx_get_data_addr(map->south.img,
			&map->south.bpp, &map->south.sl, &map->south.end);
	map->east.addr = (int *)mlx_get_data_addr(map->east.img,
			&map->east.bpp, &map->east.sl, &map->east.end);
	map->west.addr = (int *)mlx_get_data_addr(map->west.img,
			&map->west.bpp, &map->west.sl, &map->west.end);
	check_texture(map, 1);
}

//pos = VER
//!pos = HOR

void	init_texture(t_map *map, int i, t_img *tmp)
{
	bool	h_or_v;
	double	angle;

	h_or_v = map->inter_p[i].pos;
	angle = map->ray_angl[i];
	if (angle >= 0 && angle < M_PI / 2 && h_or_v)
		*tmp = map->west;
	else if (angle >= 0 && angle < M_PI / 2 && !h_or_v)
		*tmp = map->north;
	else if (angle >= M_PI / 2 && angle < M_PI && h_or_v)
		*tmp = map->east;
	else if (angle >= M_PI / 2 && angle < M_PI && !h_or_v)
		*tmp = map->north;
	else if (angle >= M_PI && angle < (3 * M_PI) / 2 && h_or_v)
		*tmp = map->east;
	else if (angle >= M_PI && angle < (3 * M_PI) / 2 && !h_or_v)
		*tmp = map->south;
	else if (angle >= (3 * M_PI) / 2 && angle < 2 * M_PI && h_or_v)
		*tmp = map->west;
	else if (angle >= (3 * M_PI) / 2 && angle < 2 * M_PI && !h_or_v)
		*tmp = map->south;
}

void	put_texture(t_map *map, int i, int *j, t_wall *wall)
{
	t_img	tmp;
	int		color;
	int		dis;
	int		wallstrip;

	tmp = map->north;
	wallstrip = (int)wall->wall_height;
	if (map->inter_p[i].pos)
		map->offsetx = (int)map->inter_p[i].y % T_S;
	else if (!map->inter_p[i].pos)
		map->offsetx = (int)map->inter_p[i].x % T_S;
	init_texture(map, i, &tmp);
	while ((*j)++ > wall->top_wall && (*j) < wall->down_wall)
	{
		dis = (*j) + ((wallstrip / 2) - (Y_SIZE / 2));
		map->offsety = dis * ((float)tmp.h / wallstrip);
		color = tmp.addr[(tmp.w * map->offsety) + map->offsetx];
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, *j, color);
	}
}
