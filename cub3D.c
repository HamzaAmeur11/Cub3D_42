/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/18 14:48:36 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	error_args(int ac)
{
	if (ac < 0)
	{
		ft_putstr_fd((char *)"The file must end in ` *.cub `\n", 2);
		return(FAILDE);
	}
	else if (ac == 1)
	{
		ft_putstr_fd((char *)"Didn't send any arg\n", 2);
		return (EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd((char *)"You send many args !!!\n", 2);
		return (EXIT_FAILURE + EXIT_FAILURE);
	}
}

int	check_extens(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		return (FAILDE);
	while (str[i] != 0 && str[i] != '.')
		i++;
	if (str[i] == 0)
		return (FAILDE);
	if (ft_strncmp(str + i, (char *)".cub", 5) != EXIT_SUCCESS)
		return (FAILDE);
	return (EXIT_SUCCESS);
}



char **init_file(char *file_name)
{ 
	char	*temp;
	int		fd;
	char	*gnl;

	temp = NULL;
	fd = open(file_name, O_RDWR);
	gnl = get_next_line(fd);
	if (gnl == NULL)
		return (NULL);
	while (gnl != NULL)
	{
		temp = ft_strjoin(temp, gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (ft_split(temp, '\n'));
}

void check_colors(char *file, int *check)
{
	int i = 1;
	while (file[i] != 0 && ((file[i] >= 9 && file[i] <= 13) || file[i] == ' '))
		i++;
	if (file[i] == 0)
	{
		*check = FAILDE;
		return ;
	}
	while (file[i] != 0 && ((file[i] >= '0' && file[i] <= '9') || file[i] == ','))
		i++;
	while (file[i] != 0 && ((file[i] >= 9 && file[i] <= 13) || file[i] == ' '))
		i++;
	if (file[i] != 0)
		*check = FAILDE;
	else
		*check = EXIT_SUCCESS;
}

void check_xpms(char *file, int *check)
{
	int i = 2;
	int j = -1;
	while (file[i] != 0 && ((file[i] >= 9 && file[i] <= 13) || file[i] == ' '))
		i++;
	while (file[i] != 0)
	{
		if (file[i] == '.')
			j = i;
		i++;
	}
	if (j == -1)
		*check = FAILDE;
	else if (ft_strncmp((char *)".xpm", file + j, 4) != EXIT_SUCCESS)
		*check = FAILDE;	
	else
		*check = EXIT_SUCCESS;
}

int check_check(t_check *check)
{
	if (check->no != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !\n", 2), EXIT_FAILURE);
	if (check->so != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !!\n", 2), EXIT_FAILURE);
	if (check->we != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !!!\n", 2), EXIT_FAILURE);
	if (check->ea != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !!!!\n", 2), EXIT_FAILURE);
	if (check->fl != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !!!!!\n", 2), EXIT_FAILURE);
	if (check->ce != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)
			"Syntaxe error in map !!!!!!\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check_rgb_and_xpms(char **file, t_check *check)
{
	int	i = 0;
	while (file[i] != NULL && (file[i][0] != '1' || file[i][0] !=  ' '))
	{
		if (!ft_strncmp((char *)"C", file[i], 1) && check->ce == CHECK)
			check_colors(file[i], &check->ce);
		else if (!ft_strncmp((char *)"F", file[i], 1) && check->fl == CHECK)
			check_colors(file[i], &check->fl);
		else if (!ft_strncmp((char *)"NO", file[i], 2) && check->no == CHECK)
			check_xpms(file[i], &check->no);
		else if (!ft_strncmp((char *)"SO", file[i], 2) && check->so == CHECK)
			check_xpms(file[i], &check->so);
		else if (!ft_strncmp((char *)"WE", file[i], 2) && check->we == CHECK)
			check_xpms(file[i], &check->we);
		else if (!ft_strncmp((char *)"EA", file[i], 2) && check->ea == CHECK)
			check_xpms(file[i], &check->ea);
		else
			break ;
		i++;
	}
	if (check_check(check) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void init_check(t_check *check)
{
	check->no = CHECK;
	check->so = CHECK;
	check->we = CHECK;
	check->ea = CHECK;
	check->map = CHECK;
	check->fl = CHECK;
	check->ce = CHECK;
}

char *init_xpms(char *str)
{
	int i = 2;
	while (str[i] != 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (ft_strdup(str + i));
}

int init_rgb(char *str, int *r, int *g, int *b)
{
	char **tmp;
	int i;

	i = 1;
	while (str[i] != 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	tmp = ft_split(str + i, ',');
	i = 0;
	while(tmp[i] != NULL)
		i++;
	if (i != 3)
		return (FAILDE);
	*r = ft_atoi(tmp[0]);
	*g = ft_atoi(tmp[1]);
	*b = ft_atoi(tmp[2]);
	if (*r > 255 || *g > 255 || *b > 255)
		return (FAILDE);
	return (ft_free(tmp), EXIT_SUCCESS);
}

int init_colors(char *str)
{
	int	r;
	int	g;
	int	b;
	int	clr;

	clr = 0;
	if (init_rgb(str, &r, &g, &b) != EXIT_SUCCESS)
		return (FAILDE);
	//		| 0 | R | G | B |   color integer
    //    	+---+---+---+---+
	clr = (r << 16) | clr;
	clr = (g << 8) | clr;
	clr = b | clr;
	return (clr);
}

int init_xpm_clr(t_map *map, char **file)
{
	int	i = 0;
	while (file[i] != NULL && (file[i][0] != '1' || file[i][0] !=  ' '))
	{
		if (!ft_strncmp((char *)"C", file[i], 1))
			map->ce = init_colors(file[i]);
		else if (!ft_strncmp((char *)"F", file[i], 1))
			map->fl = init_colors(file[i]);
		else if (!ft_strncmp((char *)"NO", file[i], 2))
			map->no = init_xpms(file[i]);
		else if (!ft_strncmp((char *)"SO", file[i], 2))
			map->so = init_xpms(file[i]);
		else if (!ft_strncmp((char *)"WE", file[i], 2))
			map->we = init_xpms(file[i]);
		else if (!ft_strncmp((char *)"EA", file[i], 2))
			map->ea = init_xpms(file[i]);
		i++;
	}
	if (map->ce < EXIT_SUCCESS || map->fl < EXIT_SUCCESS)
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check_file(t_map *map, char **file)
{
	t_check check;
	
	init_check(&check);
	if (check_rgb_and_xpms(file, &check) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_map_elmnt(file, &check) != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Sntx Error Map\n", 2), EXIT_FAILURE);
	if (check_map_walls(map, file) != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Wall Error Map\n", 2), EXIT_FAILURE);
	if (init_xpm_clr(map, file) != EXIT_SUCCESS)
		return (ft_free(map->map), ft_putstr_fd((char *)"RGB Error\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


int	parse_map(t_map *map, char *file_name)
{
	char **file;
	(void)map;
	if (check_extens(file_name) != EXIT_SUCCESS)
		return (error_args(FAILDE), FAILDE);
	file = NULL;
	file = init_file(file_name);
	if (file == NULL)//protect NULL IN file to the next fct
		return (ft_putstr_fd((char *)"Empty File !!!\n", 2) ,EXIT_FAILURE);
	if (check_file(map, file) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void print_tmap(t_map map)
{
	printf("fl = %d|\n", map.fl);
	printf("ce = %d|\n", map.ce);
	printf("walk = %d\n", map.plr.walk);
	printf("turn = %d\n", map.plr.turn);
	printf("plyer x = %f|\n", map.plr.x);
	printf("plyer y = %f|\n", map.plr.y);
	printf("height = %d|\n", map.height);
	printf("width = %d|\n", map.width);
	printf("no = %s|\n", map.no);
	printf("so = %s|\n", map.so);
	printf("we = %s|\n", map.we);
	printf("ea = %s|\n", map.ea);
	int i = -1;
	while (map.map[++i])
		printf("-%s|\n", map.map[i]);
}

void	ft_resulotion(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(map->map[i] != NULL)
		i++;
	map->height = i;
	while(map->map[i - 1][j] != '\0')
		j++;
	map->width = j;
}

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool is_player(t_map *map, float i, float j)
{
	float x;
	float y;
	float px;
	float py;

	px = map->plr.x + 0.5;
	py = map->plr.y + 0.5;
	x = i / MINI_SIZE;
	y = j / MINI_SIZE;
	return ((x-px)*(x-px) + (y-py)*(y-py) <= 0.2 * 0.2);
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
	mlx_put_image_to_window(map.mlx, map.wind, map.img, 0, 0);
}

int	ft_destroy(int key, t_map *map)
{
	mlx_destroy_image(map->mlx, map->img);
	mlx_destroy_window(map->mlx, map->wind);
	ft_free(map->map);
	exit (key);
}

int	key_pressed(int key, t_map *map)
{
	printf("=============> %d\n", key);
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
	left = floor(plr.x - plr.mov_speed);
	right = floor(plr.x + plr.mov_speed);
	up = floor(plr.y - plr.mov_speed);
	down = floor(plr.y + plr.mov_speed);
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

void	draw_minimap(t_map map)
{
	draw_walls(map);
	draw_player(map, map.plr.x * MINI_SIZE, map.plr.y * MINI_SIZE, 0xFF0000);
	mlx_put_image_to_window(map.mlx, map.wind, map.img, 0, 0);
}


void	keys_handle(t_map *map)
{
	mlx_hook(map->wind, 17, 0, ft_destroy, map);
	mlx_hook(map->wind, 2, 0, key_pressed, map);
	mlx_hook(map->wind, 3, 0, key_released, map);
}

void refresh(t_map *map)
{
	mlx_destroy_image(map->mlx, map->img);
	map->img = mlx_new_image(map->mlx, map->width * MINI_SIZE, map->height * MINI_SIZE);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel, &map->line_length, &map->endian);
}

void	game_time(t_map *map)
{
	// printf("x == %f y == %f\n", map->plr.x, map->plr.y);
	if (step_to_wall(map, map->plr) == EXIT_SUCCESS)
	move_player(map, map->plr.x, map->plr.y);
}

int	game(t_map *map)
{
	refresh(map);
	game_time(map);
	draw_minimap(*map);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_map 	map;
	int		i;
	int		j;
	
	if (ac != 2)
		return(error_args(ac));
	if (parse_map(&map, av[1]) != EXIT_SUCCESS)
		return (FAILDE);
	i = 0;
	int	y = 0;
	int x;
	ft_resulotion(&map);
	map.mlx = mlx_init();
	if (!map.mlx)
		return (0);
	map.wind = mlx_new_window(map.mlx, map.width * 32, map.height * 32, "Cub3D_42");
	map.img = mlx_new_image(map.mlx, map.width * MINI_SIZE, map.height * MINI_SIZE);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	init_player_pos(&map);
	draw_minimap(map);
	keys_handle(&map);
	mlx_loop_hook(map.mlx, game, &map);
	print_tmap(map);
	mlx_loop(map.mlx);
}