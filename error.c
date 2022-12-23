/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:36:21 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/19 20:42:46 by megrisse         ###   ########.fr       */
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

void ft_free(char **str)
{
	int i;

	i = 0;
	while(str[i] != NULL)
		free(str[i++]);
	free(str);
}

int	ft_destroy(int key, t_map *map)
{
	ft_free(map->map);
	mlx_destroy_image(map->mlx.mlx, map->mlx.img);
	mlx_destroy_window(map->mlx.mlx, map->mlx.wind);
	exit (key);
}