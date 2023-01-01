/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:46:46 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 00:01:26 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_pos(t_plr *plr, int x, int y, char c)
{
	plr->x = (x + 0.5) * T_S;
	plr->y = (y + 0.5) * T_S;
	plr->x_m = x;
	plr->y_m = y;
	plr->turn = 0;
	plr->walk = 0;
	plr->side = 0;
	plr->mov_speed = SPEED;
	plr->rot_speed = ROOOT;
	init_angle(plr, c);
}

int	map_elements(char c)
{
	static int	i;

	if (c == '1' || c == '0' || c == ' ')
		return (SUCCESS);
	if ((c == 'S' || c == 'E' || c == 'W' || c == 'N') && i == 0)
		return (i++, SUCCESS);
	return (FAILURE);
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
			if (map_elements(file[i][j]) == FAILURE)
				return (check->map = FAILDE, ft_putstr_fd((char *)
						"Char incorr!!!\n", 2), FAILURE);
			j++;
		}
		i++;
	}
	check->map = SUCCESS;
	return (SUCCESS);
}

char	*init_str(char *map_x, int size)
{
	char	*ret;
	int		i;

	i = -1;
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

char	**alloc_map(char **fl, int f, int i, int j)
{
	char	**map;
	int		x;

	x = 0;
	map = (char **)malloc(sizeof(char *) * (i - f + 1));
	if (!map)
		return (NULL);
	i = f;
	while (fl[i] != NULL)
		map[x++] = init_str(fl[i++], j);
	map[x] = NULL;
	return (map);
}
