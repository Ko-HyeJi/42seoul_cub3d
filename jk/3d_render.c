#include "cub3d.h"

typedef struct s_3d
{
	double	correct_distance;
	double	distance_plane;
	int		projected_height;
	int		top;
	int		correct_top;
	int		bottom;
	int		correct_bottom;
	int		height;
	int		width;
}				t_3d;

int	ternaries_func(int problem, int t, int f)
{
	if (problem == 1)
		return (t);
	return (f);
}

void	init_3D(t_all *all, t_3d *v)
{
	if (all->ray.distance == 0)
		all->ray.distance = 0.1;
	v->correct_distance = all->ray.distance
		* cos(all->ray.ray_angle - all->player.rotation_angle);
	v->distance_plane = (WINDOW_WID / 2) / tan(FOV_ANGLE / 2);
	v->projected_height = (int)((all->map.col_tile_size / v->correct_distance)
			* v->distance_plane);
	v->top = (WINDOW_HEI / 2)
		- (v->projected_height / 2) - all->player.updown_sight;
	v->correct_top = ternaries_func(v->top < 0, 1, v->top);
	v->bottom = (WINDOW_HEI / 2)
		+ (v->projected_height / 2) - all->player.updown_sight;
	v->correct_bottom = ternaries_func(v->bottom > WINDOW_HEI,
			WINDOW_HEI, v->bottom);
	v->height = v->bottom - v->top;
}

int	set_wall_direction(t_all* all)
{
	if (all->ray.vert_hit)
	{
		if (all->ray.ray_faces_right)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (all->ray.ray_faces_up)
			return (NO);
		else
			return (SO);
	}
}

void	draw_ceiling(t_all *p_all, int ray_num, int wall_top_pixel, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < wall_top_pixel)
	{
		x = 0;
		while (x < WALL_STRIP_WIDTH)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
			x++;
		}
		y++;
	}
}

void	draw_floor(t_all *p_all, int ray_num, int wall_bottom_pixel, int color)
{
	int	x;
	int	y;

	y = wall_bottom_pixel;
	while (y < WINDOW_HEI)
	{
		x = 0;
		while (x < WALL_STRIP_WIDTH)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
			x++;
		}
		y++;
	}
}

int	set_wall_color(t_all *all, t_3d *v, int r)
{
	int	col;
	int	direction;
	int	row;

	direction = set_wall_direction(all);
	if (direction == WE || direction == EA)
		col = ((int)all->ray.yhit_wall % (int)(all->map.col_tile_size)) * (TEXTURE_WIDTH / (int)(all->map.col_tile_size));
	else
		col = (int)all->ray.xhit_wall % (int)(all->map.col_tile_size) * (TEXTURE_WIDTH / (int)(all->map.col_tile_size));
	row = (((v->correct_top - v->top + r) * TEXTURE_HEIGHT) / v->height);

	return (all->map_info.i_texture[direction][(int)TEXTURE_WIDTH * row + col]);
}

void	render_3d_wall(t_all* all, int i)
{
	t_3d	v;
	int		r;
	int		x;
	int		y;

	init_3D(all, &v);
	r = 0;
	y = v.correct_top - 1;
	while (++y < v.correct_bottom)
	{
		x = -1;
		while (++x < WALL_STRIP_WIDTH)
			if (!all->img.data[WINDOW_WID * y + (x + i * WALL_STRIP_WIDTH)])
				all->img.data[WINDOW_WID * y	+ (x + i * WALL_STRIP_WIDTH)] = set_wall_color(all, &v, r);
		r++;
	}
	draw_ceiling(all, i, v.correct_top, all->map_info.c);
	draw_floor(all, i, v.correct_bottom, all->map_info.f);
}
