/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:09:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/18 14:43:19 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define FAILDE -1
#define CHECK -2

#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl.h"

#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define W_KEY 13
#define LEFT_KEY 123
#define RIGHT_KEY 124 
#define ESC_KEY 53
#define MINI_SIZE 12

typedef struct t_plr
{
	float	x;
	float	y;
	float	alpha;
	int		turn;  // -1 if left && +1 if right
	int		walk;	// -1 if back && +1 if fronte
	float	mov_speed;
	float	rot_speed;
}	t_plr;

typedef struct t_map
{
	char	**map;
	int		fl;
	int		ce;
	int		height;
	int		width;
	t_plr	plr;
	void	*addr;//
	void	*mlx;//
	void	*wind;
	void	*img;
	int		bits_per_pixel;//
	int		line_length;//
	int		endian;//
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
void	init_player_pos(t_map *map);
void	init_pos(t_plr *plr, int x, int y, char c);

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