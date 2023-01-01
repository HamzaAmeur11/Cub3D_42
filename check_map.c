/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:36:41 by megrisse          #+#    #+#             */
/*   Updated: 2023/01/01 00:07:48 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

char	**init_map(char **file)
{
	int	i;
	int	j;
	int	first;

	i = 0;
	j = 0;
	first = 0;
	while (file[i] != NULL && file[i][0] != ' ' && file[i][0] != '1')
		i++;
	first = i;
	while (file[i] != NULL)
	{
		if (ft_strlen(file[i]) > j)
			j = ft_strlen(file[i]);
		i++;
	}
	return (alloc_map(file, first, i, j));
}

int	horizontale_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if (map[i][j] == ' ' && map[i + 1] != NULL
				&& (map[i + 1][j] != ' ' && map[i + 1][j] != '1'))
				return (FAILURE);
			if ((map[i][j] == '0' || is_upper_char(map[i][j]) == SUCCESS)
				&& (map[i + 1] == NULL || map[i + 1][j] == ' ' || i == 0))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	vertical_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && map[i][j + 1] != '1'
				&& map[i][j + 1] != ' ' && map[i][j + 1] != 0)
				return (FAILURE);
			if ((map[i][j] == '0' || is_upper_char(map[i][j]) == SUCCESS)
				&& (map[i][j + 1] == ' ' || map[i][j + 1] == '\0' || j == 0))
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	init_player_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != 0)
		{
			if (is_upper_char(map->map[i][j]) == SUCCESS)
				return (init_pos(&map->plr, j, i, map->map[i][j]),
					SUCCESS);
			j++;
		}
		i++;
	}
	return (FAILDE);
}

int	check_map_walls(t_map *maps, char **file)
{
	char	**map;

	map = NULL;
	map = init_map(file);
	if (vertical_check(map) != SUCCESS)
		return (ft_free(map), FAILURE);
	if (horizontale_check(map) != SUCCESS)
		return (ft_free(map), FAILURE);
	maps->map = map;
	if (init_player_pos(maps) != SUCCESS)
		return (ft_free(map), FAILURE);
	return (SUCCESS);
}
