/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:09:41 by megrisse          #+#    #+#             */
/*   Updated: 2022/12/29 17:24:18 by megrisse         ###   ########.fr       */
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

#define LEFT_KEY 123
#define RIGHT_KEY 124
#define DOWN_KEY 125
#define UP_KEY 126
#define ESC_KEY 53

#define W 13
#define S 1
#define A 0
#define D 2

#define SPEED 10
#define ROOOT 5

#define TILE_SIZE 32
#define X_SIZE 1200
#define Y_SIZE 720
#define FOV_D 60.0
#define FOV_R (FOV_D * M_PI) / 180
#define VAR 4


#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "gnl.h"




typedef struct t_bool
{
	bool up;
	bool down;
	bool left;
	bool right;
}	t_bool;

typedef struct t_point
{
	bool	pos;
	double 	x;
	double 	y;
}	t_point;

typedef struct t_plr
{
	t_point p;
	double x;
	double y;
	double alpha;
	double beta;
	int 	turn;  // -1 if alpha left && +1 if alpha right
	int 	walk;	// -1 if back && +1 if fronte
	int		side;
	double mov_speed;
	double rot_speed;
}	t_plr;


typedef struct t_mlx
{
	void *mlx_ptr;
	void *win_ptr;
}	t_mlx;

typedef struct t_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		sl;
	int		end;
	int		w;
	int		h;
}		t_img;

typedef struct t_map
{
	char	**map;
	t_bool	dir;
	t_plr	plr;
	t_mlx	mlx_;
	t_img	south;
	t_img	west;
	t_img	north;
	t_img	east;
	int		offsetx;
	int		offsety;
	int		fl;
	int		ce;
	int		height;    // y_max / TILE
	int		width;    //  x_max / TILE
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	double	ray_angle;
	t_point	inter_p[X_SIZE];
	double inter[X_SIZE];
	double ray_angl[X_SIZE];
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




double normalize_rad(double angle);



void    get_texture(t_map *map);
bool is_player(t_map *map, double i, double j);
void put_square(t_map *map, int start_x, int start_y, int clr);
int is_upper_char(char c);
void send_rays(t_map *map);
void put_char(t_map *map, char c, int i, int j);
void put_wall(t_map *map);


double rad_to_deg(double rad);
double deg_to_rad(double deg);
void init_direction(t_bool *dir, double beta);
void vertic_inter(t_map *map, t_point *p, double angle);
void init_stps(t_map *map, t_bool *dirction, long *x_stp, long *y_stp);
void horiz_inter(t_map *map, t_point *p, double angle);
void put_line(t_map *map, t_point n, t_point m, int clr);

void put_3d_map(t_map *map);
void init_stps(t_map *map, t_bool *dirction, long *x_stp, long *y_stp);

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