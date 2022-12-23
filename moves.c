/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:58:54 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/22 14:04:16 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	key_pressed(int key, t_map *map)
{
	printf("key =====> %f\n", map->key);
	printf("=============> %d\n", key);
	printf("before x ======> %f y ======> %f\n", map->plr.x, map->plr.y);
	if (key == W_KEY)
		map->plr.walk = -1;
	else if (key == S_KEY)
		map->plr.walk = 1;
	else if (key == A_KEY)
		map->plr.turn = -1;
	else if (key == D_KEY)
		map->plr.turn = 1;
	else if (key == ESC_KEY)
		ft_destroy(1, map);
	printf("turn ==> %d walk ==> %d\n", map->plr.turn, map->plr.walk);
	return (EXIT_SUCCESS);
}

int	key_released(int key, t_map *map)
{
	
	if (key == W_KEY)
		map->plr.walk = 0;
	else if (key == S_KEY)
		map->plr.walk = 0;
	else if (key == A_KEY)
		map->plr.turn = 0;
	else if (key == D_KEY)
		map->plr.turn = 0;
	printf("x ======> %f y ======> %f\n", map->plr.x, map->plr.y);
	printf("turn ==> %d walk ==> %d\n", map->plr.turn, map->plr.walk);
	return (EXIT_SUCCESS);
}

void	keys_handle(t_map *map)
{
	mlx_hook(map->mlx.wind, 17, 0, ft_destroy, map);
	mlx_hook(map->mlx.wind, 2, 0, key_pressed, map);
	mlx_hook(map->mlx.wind, 3, 0, key_released, map);
}

//	when player move to another cub //

void	move_player(t_map *map, float p_x, float p_y)
{
	int	i;
	int	x;

	i = floor(p_y);
	x = floor(p_x);
	// printf("i === %d x == %d", i, x);
	if (map->plr.turn == -1)
		map->plr.x -= map->plr.mov_speed;
	else if (map->plr.turn == 1)
		map->plr.x += map->plr.mov_speed;
	else if (map->plr.walk == -1)
		map->plr.y -= map->plr.mov_speed;
	else if (map->plr.walk == 1)
		map->plr.y += map->plr.mov_speed;
	// map->map[i][x] = '0';
}

// when player move to wall cub //

int	step_to_wall(t_map *map, t_plr plr)
{
	int	i;
	int	j;
	int	left;//
	int	right;//
	int	up;//
	int	down;//

	i = floor(plr.y);
	j = floor(plr.x);
	left = floor(plr.x - plr.mov_speed);//
	right = floor(plr.x + plr.mov_speed);//
	up = floor(plr.y - plr.mov_speed);//
	down = floor(plr.y + plr.mov_speed);//
	if (plr.turn == -1 && map->map[i][left] == '1')
		return (1);
	else if (map->plr.turn == 1 && map->map[i][right] == '1')
		return (1);
	else if (map->plr.walk == -1 && map->map[up][j] == '1')
		return (1);
	else if (map->plr.walk == 1 && map->map[down][j] == '1')
		return (1);
	else
		return (0);
}