/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm_clr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:32:15 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/31 21:46:40 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_check(t_check *check)
{
	check->no = CHECK;
	check->so = CHECK;
	check->we = CHECK;
	check->ea = CHECK;
	check->map = CHECK;
	check->fl = CHECK;
	check->ce = CHECK;
}

void	check_colors(char *file, int *check)
{
	int	i;

	i = 1;
	while (file[i] != 0 && ((file[i] >= 9 && file[i] <= 13) || file[i] == ' '))
		i++;
	if (file[i] == 0)
	{
		*check = FAILDE;
		return ;
	}
	while (file[i] != 0 && ((file[i] >= '0'
				&& file[i] <= '9') || file[i] == ','))
		i++;
	while (file[i] != 0 && ((file[i] >= 9 && file[i] <= 13) || file[i] == ' '))
		i++;
	if (file[i] != 0)
		*check = FAILDE;
	else
		*check = EXIT_SUCCESS;
}

void	check_xpms(char *file, int *check)
{
	int	i;
	int	j;

	i = 2;
	j = -1;
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

int	check_check(t_check *check)
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

int	check_rgb_and_xpms(char **file, t_check *check)
{
	int	i;

	i = 0;
	while (file[i] != NULL && (file[i][0] != '1' || file[i][0] != ' '))
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
