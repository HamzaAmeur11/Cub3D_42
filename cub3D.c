/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/31 02:47:37 by megrisse         ###   ########.fr       */
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

int    up_2_wall(t_map *map, double x, double y, double angle)
{
    if (angle >= 0 && angle < 90)
        if (map->map[(int)(map->plr.y / TILE_SIZE)][(int)(map->plr.x / TILE_SIZE) + 1] == '1' && 
            map->map[(int)(map->plr.y / TILE_SIZE) + 1][(int)(map->plr.x / TILE_SIZE)] == '1' && 
			map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE) - 1] == '1' && 
            map->map[(int)(y / TILE_SIZE) - 1][(int)(x / TILE_SIZE)] == '1')
                return (EXIT_FAILURE);
    if (angle >= 90 && angle < 180)
        if (map->map[(int)(map->plr.y / TILE_SIZE)][(int)(map->plr.x / TILE_SIZE) - 1] == '1' && 
            map->map[(int)(map->plr.y / TILE_SIZE) + 1][(int)(map->plr.x / TILE_SIZE)] == '1' &&
			map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE) + 1] == '1' && 
            map->map[(int)(y / TILE_SIZE) - 1][(int)(x / TILE_SIZE)] == '1')
                return (EXIT_FAILURE);
    if (angle >= 180 && angle < 270)
        if (map->map[(int)(map->plr.y / TILE_SIZE) - 1][(int)(map->plr.x / TILE_SIZE)] == '1' && 
            map->map[(int)(map->plr.y / TILE_SIZE)][(int)(map->plr.x / TILE_SIZE) - 1] == '1' &&
			map->map[(int)(y / TILE_SIZE) + 1][(int)(x / TILE_SIZE)] == '1' && 
            map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE) + 1] == '1')
                return (EXIT_FAILURE);
    if (angle >= 270 && angle < 360)
        if (map->map[(int)(map->plr.y / TILE_SIZE)][(int)(map->plr.x / TILE_SIZE) + 1] == '1' && 
            map->map[(int)(map->plr.y / TILE_SIZE) - 1][(int)(map->plr.x / TILE_SIZE)] == '1' &&
			map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE) - 1] == '1' && 
            map->map[(int)(y / TILE_SIZE) + 1][(int)(x / TILE_SIZE)] == '1')
                return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

void edit_pos_walk(t_map *map)
{
	double new_x;
	double new_y;

	new_x = map->plr.x + map->plr.walk * (map->plr.mov_speed) * cos(map->plr.beta);
	new_y = map->plr.y + map->plr.walk * (map->plr.mov_speed) * sin(map->plr.beta);
	if (map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return ;
	else if (up_2_wall(map, new_x, new_y, map->plr.alpha) != EXIT_SUCCESS && map->plr.walk > 0)
		{printf("pppppppppp\n");return ;}
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
	// else
	// 	return (0);
	if (map->plr.turn != 0)
	{
		map->plr.alpha = normalize_deg(map->plr.alpha + (map->plr.turn * map->plr.rot_speed));
		map->plr.beta = normalize_rad(deg_to_rad(map->plr.alpha));
	}
	if (map->plr.walk != 0)
		edit_pos_walk(map);
	if (map->plr.side != 0)
		edit_pos_side(map);
	mlx_clear_window(map->mlx_.mlx_ptr, map->mlx_.win_ptr);
	// put_wall(map);
	send_rays(map);
	map->plr.turn = 0;
	map->plr.walk = 0;
	map->plr.side = 0;
	// put_3d_map(map);
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}

int	hook(t_map *map)
{
	mlx_hook(map->mlx_.win_ptr, 17, 0, dest, map);
	mlx_hook(map->mlx_.win_ptr, 2, 0, moves, map);
	// mlx_hook(map->mlx_.mlx_ptr, 3, 0, key_realesed, map);
	return (EXIT_SUCCESS);
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
	horiz_inter(map, &inter_h, normalize_rad(angle));
	vertic_inter(map, &inter_v, normalize_rad(angle));
	if (distence(plr, inter_h) > distence(plr, inter_v))
		*p = inter_v;
	else
		*p = inter_h;
			
}

void init_texture(t_map *map, int i, int **tmp)
{
	if (map->ray_angl[i] >= 0 && map->ray_angl[i] < M_PI / 2 && map->inter_p[i].pos)
		*tmp = map->west.addr;
	else if (map->ray_angl[i] >= 0 && map->ray_angl[i] < M_PI / 2 && !map->inter_p[i].pos)
		*tmp = map->north.addr;
	else if (map->ray_angl[i] >= M_PI / 2 && map->ray_angl[i] < M_PI && map->inter_p[i].pos)
		*tmp = map->east.addr;
	else if (map->ray_angl[i] >= M_PI / 2 && map->ray_angl[i] < M_PI && !map->inter_p[i].pos)
		*tmp = map->north.addr;
	else if (map->ray_angl[i] >= M_PI && map->ray_angl[i] < (3 * M_PI) / 2 && map->inter_p[i].pos)
		*tmp = map->east.addr;
	else if (map->ray_angl[i] >= M_PI && map->ray_angl[i] < (3 * M_PI) / 2 && !map->inter_p[i].pos)
		*tmp = map->south.addr;
	else if (map->ray_angl[i] >= (3 * M_PI) / 2 && map->ray_angl[i] < 2 * M_PI && map->inter_p[i].pos)
		*tmp = map->west.addr;
	else if (map->ray_angl[i] >= (3 * M_PI) / 2 && map->ray_angl[i] < 2 * M_PI && !map->inter_p[i].pos)
		*tmp = map->south.addr;
}

void	put_texture(t_map *map, int i, int *j, double walltop, double down, double top)
{
	int	color;
	int	*tmp = map->north.addr;
	int	dis;
	int	wallstrip;
	
	wallstrip = (int)walltop;
	if (map->inter_p[i].pos)//vertical
		map->offsetx = (int)map->inter_p[i].y % TILE_SIZE;
	else if (!map->inter_p[i].pos)//hor
		map->offsetx = (int)map->inter_p[i].x % TILE_SIZE;
	init_texture(map, i, &tmp);
	while ((*j)++ > top && (*j) < down)
	{
		dis = (*j) + ((wallstrip / 2) - (Y_SIZE / 2));
		map->offsety = dis * ((float)map->south.h / wallstrip);
		color = tmp[(map->south.w * map->offsety) + map->offsetx];
		mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, *j, color);
	}
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
    while (++j <= top_wall)
        mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->ce);
	put_texture(map, i, &j, wall_height, down_wall, top_wall);
    while (j++ < Y_SIZE)
        mlx_pixel_put(map->mlx_.mlx_ptr, map->mlx_.win_ptr, i, j, map->fl);
    
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

void put_3d_map_(t_map *map,int i, double ray_angle, double distence)
{
	double projec_d;
	double wall_height;
	double d_ray;

		d_ray = distence * cos(ray_angle - map->plr.beta);
		projec_d = (X_SIZE / 2) / tan(FOV_R / 2);
		wall_height = (TILE_SIZE / d_ray) * projec_d;
		fct(map, wall_height, i);
}

void send_rays(t_map *map)
{
	map->ray_angle = map->plr.beta - deg_to_rad(30);
	t_point n;
	map->plr.p.x = map->plr.x;
	map->plr.p.y = map->plr.y;
	// put_line(map, map->plr.p, n, 0xFF0000);
	int i = -1;
	while (++i < X_SIZE)
	{
		interaction_pt(map, &n, normalize_rad(map->ray_angle));
		map->inter[i] = distence(map->plr.p, n);
		// put_line(map, map->plr.p, n, 0xFF0000);
		map->ray_angl[i] = normalize_rad(map->ray_angle);
		map->inter_p[i].x = n.x;
		map->inter_p[i].y = n.y;
		map->inter_p[i].pos = n.pos;
		put_3d_map_(map, i, map->ray_angle, distence(map->plr.p, n));
		map->ray_angle += FOV_R / X_SIZE;
	}
}

int put_2d_map(t_map *map)
{
	// put_wall(map);
	send_rays(map);
	return (0);
}

int main(int ac, char **av)
{
	t_map map;

	if (ac != 2)
		return(error_args(ac));
	if (parse_map(&map, av[1]) != EXIT_SUCCESS)
		return (FAILDE);
	map.mlx_.mlx_ptr = mlx_init();
	map.mlx_.win_ptr = mlx_new_window(map.mlx_.mlx_ptr, X_SIZE, Y_SIZE, (char *)"---Cub3D---");
	get_texture(&map);
	ft_resulotion(&map);
	print_tmap(map);
	if (put_2d_map(&map) != EXIT_SUCCESS)
		return (FAILDE);
	// put_3d_map(&map);
	mlx_loop_hook(map.mlx_.mlx_ptr, hook, &map);
	mlx_loop(map.mlx_.mlx_ptr);
}