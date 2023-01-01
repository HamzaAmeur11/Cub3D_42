/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:45:06 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/31 21:21:09 by megrisse         ###   ########.fr       */
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
			"./texture/north_texture.xpm", &map->north.w, &map->north.h);
	map->south.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			"./texture/south_texture.xpm", &map->south.w, &map->south.h);
	map->east.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			"./texture/east_texture.xpm", &map->east.w, &map->east.h);
	map->west.img = mlx_xpm_file_to_image(map->mlx_.mlx_ptr,
			"./texture/west_texture.xpm", &map->west.w, &map->west.h);
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
