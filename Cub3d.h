/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:09:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/08 20:28:45 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define FAILDE -1
#define CHECK -2

#define NORTH 10
#define SOUTH 11
#define WEST 12
#define EAST 13

#define TILE_SIZE 32

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "gnl.h"

typedef struct t_plr
{
	float x;
	float y;
	int drc;
}	t_plr;

typedef struct t_mlx
{
	void *mlx_ptr;
	void *win_ptr;
}	t_mlx;

typedef struct t_map
{
	char	**map;
	t_plr	plr;
	t_mlx	mlx_;
	int		fl;
	int		ce;
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_map;

typedef struct t_check
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	map;
	int	fl;
	int	ce;
}	t_check;



//__________________Parsing____

int		error_args(int ac);
int		parse_map(t_map *map, char *file_name);
int		check_map_elmnt(char	**file, t_check *check);
int		check_map_walls(t_map *maps, char **file);
char	**alloc_map(char **fl, int s, int i, int j);
char	**init_map(char **file);
void	ft_resulotion(t_map *map);
void print_tmap(t_map map);
int	parse_map(t_map *map, char *file_name);
int check_file(t_map *map, char **file);
int init_xpm_clr(t_map *map, char **file);
int init_colors(char *str);
int init_rgb(char *str, int *r, int *g, int *b);
char *init_xpms(char *str);
void init_check(t_check *check);
int check_rgb_and_xpms(char **file, t_check *check);
int check_check(t_check *check);
void check_xpms(char *file, int *check);
void check_colors(char *file, int *check);
char **init_file(char *file_name);
int	check_extens(char *str);
int	error_args(int ac);
int is_upper_char(char c);





//__________________Utils____
int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(char *str, int size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_free(char **str);





#endif