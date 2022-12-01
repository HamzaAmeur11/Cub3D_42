/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/12/01 20:11:29 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	error_args(int ac)
{
	if (ac < 0)
	{
		write(2, (char *)"The file must end in ` *.cub `\n", 32);
		return(FAILDE);
	}
	else if (ac == 1)
	{
		write(2, (char *)"Didn't send any arg\n", 21);
		return (EXIT_FAILURE);
	}
	else
	{
		write(2, (char *)"You send many args !!!\n", 24);
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
		return (ft_putstr_fd((char *)"Syntaxe error in map !\n", 2), EXIT_FAILURE);
	if (check->so != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Syntaxe error in map !!\n", 2), EXIT_FAILURE);
	if (check->we != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Syntaxe error in map !!!\n", 2), EXIT_FAILURE);
	if (check->ea != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Syntaxe error in map !!!!\n", 2), EXIT_FAILURE);
	if (check->fl != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Syntaxe error in map !!!!!\n", 2), EXIT_FAILURE);
	if (check->ce != EXIT_SUCCESS)
		return (ft_putstr_fd((char *)"Syntaxe error in map !!!!!!\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check_rgb_and_xpms(char **file, t_check *check)
{
	int	i = 0;
	while (file[i] != NULL && (file[i][0] != '1' || file[i][0] !=  ' '))
	{
		printf("[%s]\n", file[i]);
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

int check_file(char **file)
{
	t_check check;
	
	init_check(&check);
	if (check_rgb_and_xpms(file, &check) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	//Hnaaaaa khdemha
	return (EXIT_SUCCESS);
}

// void init_map(t_map *map, char **file)
// {
// }

int	parse_map(t_map *map, char *file_name)
{
	char **file;
	(void)map;
	if (check_extens(file_name) != EXIT_SUCCESS)
		return (error_args(FAILDE), FAILDE);
	file = NULL;
	file = init_file(file_name);
	if (file == NULL)//protect NULL IN file to the next fct
		return (EXIT_FAILURE);
	if (check_file(file) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	// init_map(map, file);
	int i = 0;
	while (file[i] != NULL)
		printf("--->%s\n", file[i++]);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_map map;
	
	if (ac != 2)
		return(error_args(ac));
	if (parse_map(&map, av[1]) != EXIT_SUCCESS)
		return (FAILDE);
	printf("%s aller >>>\n", av[1]);
}