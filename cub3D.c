/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/23 14:39:44 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
	printf("key =======> %f\n", map.key);
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

bool is_player(t_map *map, float i, float j)
{
	float x;
	float y;
	float px;
	float py;

	px = map->plr.x + map->key;
	py = map->plr.y + map->key;
	x = i / MINI_SIZE;
	y = j / MINI_SIZE;
	return ((x-px)*(x-px) + (y-py)*(y-py) <= 0.3 * 0.3);
}

void refresh(t_map *map)
{
	mlx_destroy_image(map->mlx.mlx, map->mlx.img);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->width * MINI_SIZE, map->height * MINI_SIZE);
	map->mlx.addr = mlx_get_data_addr(map->mlx.img, &map->mlx.bits_per_pixel, &map->mlx.line_length, &map->mlx.endian);
}

void	check_moves(t_map *map)
{
	if (step_to_wall(map, map->plr) == EXIT_SUCCESS)
		move_player(map, map->plr.x, map->plr.y);
}

int	game(t_map *map)
{
	refresh(map);
	check_moves(map);
	draw_minimap(*map);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_map 	map;

	
	if (ac != 2)
		return(error_args(ac));
	if (parse_map(&map, av[1]) != EXIT_SUCCESS)
		return (FAILDE);
	ft_resulotion(&map);
	map.mlx.mlx = mlx_init();
	if (!map.mlx.mlx)
		return (0);
	init_player_pos(&map);
	map.mlx.wind = mlx_new_window(map.mlx.mlx, map.width * 32, map.height * 32, "Cub3D_42");
	map.mlx.img = mlx_new_image(map.mlx.mlx, map.width * MINI_SIZE, map.height * MINI_SIZE);
	map.mlx.addr = mlx_get_data_addr(map.mlx.img, &map.mlx.bits_per_pixel, &map.mlx.line_length, &map.mlx.endian);
	draw_minimap(map);
	keys_handle(&map);
	map.key = 0.5;
	mlx_loop_hook(map.mlx.mlx, game, &map);
	print_tmap(map);
	map.key = 0;
	mlx_loop(map.mlx.mlx);
}