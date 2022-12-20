/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:36:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/19 15:22:48 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void ft_free(char **str)
{
	int i;

	i = -1;
	while(str[++i])
		free(str[i]);
	free(str);
}

void init_pos(t_plr *plr, int x, int y, char c)
{
	plr->x = (x + 0.5) * TILE_SIZE;
	plr->y = (y + 0.5) * TILE_SIZE;
	plr->turn = 0;
	plr->walk = 0;
	plr->mov_speed = 0.1;
	plr->rot_speed = (2 * M_PI) / 180;
	if (c == 'N')
		plr->alpha = 270, plr->beta = (3 * M_PI) / 2;
	else if (c == 'W')
		plr->alpha = 180, plr->beta = M_PI;
	else if (c == 'E')
		plr->alpha = 0, plr->beta = 0;
	else if (c == 'S')
		plr->alpha = 90, plr->beta = M_PI / 2;
	
}

int	map_elements(char c)
{
	static int i;
	
	if (c == '1' || c == '0'  || c == ' ')
		return (EXIT_SUCCESS);
	if ((c == 'S' || c == 'E' || c == 'W' || c == 'N') && i == 0)//F in map bonus
		return (i++, EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_map_elmnt(char **file, t_check *check)
{
	int	i;
	int	j;

	i = 0;
	while (file[i] != NULL && file[i][0] != ' ' && file[i][0] != '1')
		i++;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (map_elements(file[i][j]) == EXIT_FAILURE)
				return (check->map = FAILDE, ft_putstr_fd((char *)"Char incorr!!!\n", 2), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	check->map = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

char *init_str(char *map_x, int size)
{
	char *ret;
	int		i = -1;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	while (map_x[++i] != 0 && i <= size)
		ret[i] = map_x[i];
	while (i < size)
		ret[i++] = ' ';
	ret[i] = 0;
	return (ret);
}

char **alloc_map(char **fl, int f, int i, int j)
{
	char **map;
	int	x = 0;
	map = (char **)malloc(sizeof(char *) * (i - f + 1));
	if (!map)
		return(NULL);
	i = f;
	while(fl[i] != NULL)
		map[x++] = init_str(fl[i++], j);
	map[x] = NULL;
	return (map);
}

char **init_map(char **file)
{
	int i = 0;
	int j = 0;
	int first = 0;;
	while (file[i] != NULL && file[i][0] != ' ' && file[i][0] != '1')
		i++;
	first = i;
	while(file[i] != NULL)
	{
		if (ft_strlen(file[i]) > j)
			j = ft_strlen(file[i]);
		i++;
	}
	return (alloc_map(file, first, i, j));
}

int horizontale_check(char **map)
{
	int i = 0;
	int j = 0;

	while (map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != 0)
		{
			if (map[i][j] == ' ' && map[i + 1] != NULL && (map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
				return (EXIT_FAILURE);
			if (map[i][j] == '0' && (map[i + 1] == NULL || map[i + 1][j] == ' ' || i == 0))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int vertical_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && (map[i][j + 1] != ' ' && map[i][j + 1] != '1' && map[i][j + 1] != '\0'))
				return (EXIT_FAILURE);
			if (map[i][j] == '0' && (map[i][j + 1] == ' ' || map[i][j + 1] == '\0' || j == 0))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void init_player_pos(t_map *map)
{
	int i = 0, j = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != 0)
		{
			if (is_upper_char(map->map[i][j]) == EXIT_SUCCESS)
				init_pos(&map->plr, j, i, map->map[i][j]);
			j++;
		}
		i++;
	}
}

int	check_map_walls(t_map *maps, char **file)
{
	char **map;

	map = NULL;
	map = init_map(file);
	if (vertical_check(map) != EXIT_SUCCESS)// ----
		return (ft_free(map), EXIT_FAILURE);
	if (horizontale_check(map) != EXIT_SUCCESS)//  |||
		return (ft_free(map), EXIT_FAILURE);
	maps->map = map;
	init_player_pos(maps);
	return (EXIT_SUCCESS);
}