/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 00:57:30 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	interaction_pt(t_map *map, t_point *p, double angle)
{
	t_point	plr;
	t_point	inter_h;
	t_point	inter_v;

	plr.x = map->plr.x;
	plr.y = map->plr.y;
	horiz_inter(map, &inter_h, normalize_rad(angle));
	vertic_inter(map, &inter_v, normalize_rad(angle));
	if (distence(plr, inter_h) > distence(plr, inter_v))
		*p = inter_v;
	else
		*p = inter_h;
}

void	put_put(t_map *map, t_wall *wall, int i)
{
	int	j;

	j = -1;
	wall->top_wall = (Y_SIZE / 2) - (wall->wall_height / 2);
	if (wall->top_wall < 0)
		wall->top_wall = 0;
	wall->down_wall = (Y_SIZE / 2) + (wall->wall_height / 2);
	if (wall->down_wall > Y_SIZE)
		wall->down_wall = Y_SIZE;
	while (++j <= wall->top_wall)
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->ce);
	put_texture(map, i, &j, wall);
	while (j++ < Y_SIZE)
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->fl);
}

void	put_3d_map_(t_map *map, int i, double ray_angle, double distence)
{
	double	projec_plan;
	double	d_ray;

	d_ray = distence * cos(ray_angle - map->plr.beta);
	projec_plan = (X_SIZE / 2) / tan(FOV_R / 2);
	map->wall.wall_height = (T_S / d_ray) * projec_plan;
	put_put(map, &map->wall, i);
}

void	send_rays(t_map *map)
{
	t_point	n;
	int		i;

	i = -1;
	map->ray_angle = map->plr.beta - deg_to_rad(30);
	map->plr.p.x = map->plr.x;
	map->plr.p.y = map->plr.y;
	while (++i < X_SIZE)
	{
		interaction_pt(map, &n, normalize_rad(map->ray_angle));
		map->inter[i] = distence(map->plr.p, n);
		map->ray_angl[i] = normalize_rad(map->ray_angle);
		map->inter_p[i].x = n.x;
		map->inter_p[i].y = n.y;
		map->inter_p[i].pos = n.pos;
		put_3d_map_(map, i, map->ray_angle, distence(map->plr.p, n));
		map->ray_angle += FOV_R / X_SIZE;
	}
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (error_args(ac));
	if (parse_map(&map, av[1]) != SUCCESS)
		return (FAILDE);
	map.mlx_.mlx_ptr = mlx_init();
	map.mlx_.win_ptr = mlx_new_window(map.mlx_.mlx_ptr, X_SIZE,
			Y_SIZE, (char *)"---Cub3D---");
	get_texture(&map);
	ft_resulotion(&map);
	send_rays(&map);
	my_hooks(&map);
}
