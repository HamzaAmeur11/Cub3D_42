/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:09:41 by megrisse          #+#    #+#             */
/*   Updated: 2023/01/01 01:49:43 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FAILDE -1
# define SUCCESS 0
# define FAILURE 1
# define CHECK -2
// DIRECTION-----------------------------------//
# define NORTH 10
# define SOUTH 11
# define WEST 12
# define EAST 13
// KEYS-----------------------------------//
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define ESC_KEY 53
# define W 13
# define S 1
# define A 0
# define D 2
// MOVES-----------------------------------//
# define SPEED 7
# define ROOOT 5
// SIZES-----------------------------------//
# define T_S 32
# define X_SIZE 1000
# define Y_SIZE 450
// FOV-----------------------------------//
//      60.0 deg = 1.0471975512 rad      //
# define FOV_D 60.0
# define FOV_R 1.0471975512
//HEADERS-----------------------------------//
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "gnl.h"
//STRUCTS-----------------------------------//

typedef struct t_bool
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_bool;

typedef struct t_wall
{
	double	wall_height;
	double	down_wall;
	double	top_wall;
}	t_wall;

typedef struct t_point
{
	bool	pos;
	double	x;
	double	y;

}	t_point;

typedef struct t_plr
{
	t_point	p;
	double	x;
	double	y;
	int		x_m;
	int		y_m;
	double	alpha;
	double	beta;
	int		turn;
	int		walk;
	int		side;
	double	mov_speed;
	double	rot_speed;
}	t_plr;
//turn : -1 if alpha left && +1 if alpha right
//walk : -1 if back && +1 if fronte
//side : -1 if left && +1 if right

typedef struct t_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
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
	t_wall	wall;
	int		offsetx;
	int		offsety;
	int		fl;
	int		ce;
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	double	ray_angle;
	t_point	inter_p[X_SIZE];
	double	inter[X_SIZE];
	double	ray_angl[X_SIZE];
}	t_map;

typedef struct t_check
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		map;
	int		fl;
	int		ce;
}	t_check;

//__________________Parsing____
int		check_map_walls(t_map *maps, char **file);
char	**init_map(char **file);
int		vertical_check(char **map);
int		horizontale_check(char **map);
int		init_player_pos(t_map *map);
char	**alloc_map(char **fl, int s, int i, int j);
char	*init_str(char *map_x, int size);
int		check_map_elmnt(char	**file, t_check *check);
int		map_elements(char c);
void	init_pos(t_plr *plr, int x, int y, char c);
void	init_angle(t_plr *plr, char c);
int		error_args(int ac);
int		parse_map(t_map *map, char *file_name);
void	ft_resulotion(t_map *map);
int		check_file(t_map *map, char **file);
int		init_xpm_clr(t_map *map, char **file);
int		init_colors(char *str);
int		init_rgb(char *str, int *r, int *g, int *b);
char	*init_xpms(char *str);
void	init_check(t_check *check);
int		check_rgb_and_xpms(char **file, t_check *check);
int		check_check(t_check *check);
void	check_xpms(char *file, int *check);
void	check_colors(char *file, int *check);
char	**init_file(char *file_name);
int		check_extens(char *str);
int		error_args(int ac);
int		is_upper_char(char c);

//HOOKS-----------------------------------//

void	my_hooks(t_map *map);
double	distence(t_point p, t_point q);
void	edit_pos_side(t_map *map);
void	edit_pos_walk(t_map *map);
void	put_texture(t_map *map, int i, int *j, t_wall *wall);
void	init_texture(t_map *map, int i, t_img *tmp);

int		check_if_wall(t_map *map, double x, double y);
int		check_2_walls(t_map *map, t_point *f, long angle);
void	get_texture(t_map *map);
int		is_upper_char(char c);
void	send_rays(t_map *map);
void	put_char(t_map *map, char c, int i, int j);
void	put_wall(t_map *map);
void	vertic_inter(t_map *map, t_point *p, double angle);
void	horiz_inter(t_map *map, t_point *p, double angle);
double	normalize_rad(double angle);
double	normalize_deg(double angle);
double	rad_to_deg(double rad);
double	deg_to_rad(double deg);

//__________________Utils____
int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_free(char **str);

#endif
