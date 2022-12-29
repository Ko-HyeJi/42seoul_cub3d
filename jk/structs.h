/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:56:49 by hyko              #+#    #+#             */
/*   Updated: 2022/12/29 20:34:41 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_img
{
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
	int		*data;
}				t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;
	double	fov_angle;
}				t_player;

typedef struct s_key
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	right_rotation;
	bool	left_rotation;
}				t_key;

typedef struct s_temp_ray
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		found_wall_hit;
	double	xhit_wall;
	double	yhit_wall;
	double	distance;
}				t_temp_ray;

typedef struct s_ray
{
	double	ray_angle;
	double	xhit_wall;
	double	yhit_wall;
	double	distance;
	bool	vert_hit;
	bool	ray_faces_down;
	bool	ray_faces_up;
	bool	ray_faces_right;
	bool	ray_faces_left;
}				t_ray;

typedef struct s_map
{
	unsigned long long	row;
	unsigned long long	col;
	char				**dp_map;
	double				row_tile_size;
	double				col_tile_size;
}				t_map;

typedef struct s_point_db
{
	double	x;
	double	y;
}				t_point_db;

typedef struct s_point_i
{
	int	x;
	int	y;
}				t_point_i;

typedef struct s_map_info
{
	void	*v_texture[4];
	int		*i_texture[4];
	int		f;
	int		c;
	char	**tile;
	int		info_cnt;
	int		tile_cnt;
}				t_map_info;

typedef enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	TILE,
}				t_type;

typedef struct s_all
{
	t_img		img;
	t_player	player;
	t_key		key;
	t_ray		ray;
	t_map		map;
	void		*mlx;
	void		*win;
	t_map_info	map_info;
}				t_all;

#endif
