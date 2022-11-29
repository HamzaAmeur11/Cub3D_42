/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:07 by hameur            #+#    #+#             */
/*   Updated: 2022/11/29 17:43:04 by hameur           ###   ########.fr       */
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

int	parse_map(t_map *map, char *file_name)
{
	char **file;
	(void)map;
	if (check_extens(file_name) != EXIT_SUCCESS)
		return (error_args(FAILDE), FAILDE);
	file = NULL;
	file = init_file(file_name);//protect NULL IN file to the next fct
	
	return (0);
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