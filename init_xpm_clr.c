/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:23:24 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/31 21:41:45 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

char	*init_xpms(char *str)
{
	int	i;

	i = 2;
	while (str[i] != 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (ft_strdup(str + i));
}

int	init_rgb(char *str, int *r, int *g, int *b)
{
	char	**tmp;
	int		i;

	i = 1;
	while (str[i] != 0 && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	tmp = ft_split(str + i, ',');
	i = 0;
	while (tmp[i] != NULL)
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

int	init_colors(char *str)
{
	int	r;
	int	g;
	int	b;
	int	clr;

	clr = 0;
	if (init_rgb(str, &r, &g, &b) != EXIT_SUCCESS)
		return (FAILDE);
	clr = (r << 16) | clr;
	clr = (g << 8) | clr;
	clr = b | clr;
	return (clr);
}

int	init_xpm_clr(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (file[i] != NULL && (file[i][0] != '1' || file[i][0] != ' '))
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
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_resulotion(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i] != NULL)
		i++;
	map->height = i;
	while (map->map[i - 1][j] != '\0')
		j++;
	map->width = j;
}
