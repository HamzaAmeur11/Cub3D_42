/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:09:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/29 17:42:21 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define FAILDE -1

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl.h"

typedef struct t_map
{
	char	**map;
	int		fl;
	int		ce;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_map;



//__________________Parsing____

int		error_args(int ac);
int		parse_map(t_map *map, char *file_name);



//__________________Utils____
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
void	ft_bzero(char *str, int size);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);



#endif