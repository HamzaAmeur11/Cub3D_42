/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:04:07 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 01:01:24 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	dest(t_map *map, int error)
{
	ft_free(map->map);
	mlx_destroy_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	exit(error);
}

int	moves(t_map *map)
{
	if (map->plr.turn != 0)
	{
		map->plr.alpha = normalize_deg(map->plr.alpha
				+ (map->plr.turn * map->plr.rot_speed));
		map->plr.beta = normalize_rad(deg_to_rad(map->plr.alpha));
	}
	if (map->plr.walk != 0)
		edit_pos_walk(map);
	if (map->plr.side != 0)
		edit_pos_side(map);
	mlx_clear_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	send_rays(map);
	return (SUCCESS);
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == W)
		map->plr.walk = +1;
	if (keycode == S)
		map->plr.walk = -1;
	if (keycode == A)
		map->plr.side = -1;
	if (keycode == D)
		map->plr.side = +1;
	if (keycode == RIGHT_KEY)
		map->plr.turn = +1;
	if (keycode == LEFT_KEY)
		map->plr.turn = -1;
	if (keycode == ESC_KEY)
		dest(map, 1);
	return (SUCCESS);
}

int	key_realesed(int keycode, t_map *map)
{
	if (keycode == W)
		map->plr.walk = 0;
	else if (keycode == S)
		map->plr.walk = 0;
	else if (keycode == A)
		map->plr.side = 0;
	else if (keycode == D)
		map->plr.side = 0;
	else if (keycode == RIGHT_KEY)
		map->plr.turn = 0;
	else if (keycode == LEFT_KEY)
		map->plr.turn = 0;
	return (SUCCESS);
}

void	my_hooks(t_map *map)
{
	mlx_hook(map->mlx_.win_ptr, 17, 0, dest, map);
	mlx_hook(map->mlx_.win_ptr, 2, 0, key_press, map);
	mlx_hook(map->mlx_.win_ptr, 3, 0, key_realesed, map);
	mlx_loop_hook(map->mlx_.mlx_ptr, moves, map);
	mlx_loop(map->mlx_.mlx_ptr);
}
