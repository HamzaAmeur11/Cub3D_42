/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 22:36:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/03 18:35:34 by hameur           ###   ########.fr       */
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

int	map_elements(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == ' ')
		return (EXIT_SUCCESS);
	if (c == 'S' || c == 'E' || c == 'W' || c == 'F')//f in map bonus
		return (EXIT_SUCCESS);
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
				return (check->map = FAILDE, EXIT_FAILURE);
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
			if (map[i][j] == '0' && (map[i + 1] == NULL || map[i + 1][j] == ' '))
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
			if (map[i][j] == '0' && (map[i][j + 1] == ' ' || map[i][j + 1] == '\0'))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
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
	return (maps->map = map, EXIT_SUCCESS);
}