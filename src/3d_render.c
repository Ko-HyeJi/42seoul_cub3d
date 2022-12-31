/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:47:58 by hyko              #+#    #+#             */
/*   Updated: 2022/12/30 21:10:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_wall_direction(t_all *p_all)
{
	if (p_all->ray.vert_hit)
	{
		if (p_all->ray.ray_faces_right)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (p_all->ray.ray_faces_up)
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
		while (x < WALL_STRIP)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP)]
					= color;
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
		while (x < WALL_STRIP)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP)]
					= color;
			x++;
		}
		y++;
	}
}

int	set_wall_color(t_all *p_all, int r)
{
	int	col;
	int	row;
	int	direction;

	direction = set_wall_direction(p_all);
	if (direction == WE || direction == EA)
		col = ((int)(p_all->ray.yhit_wall) % (int)(p_all->map.row_tile_size))
			* (64 / p_all->map.row_tile_size);
	else
		col = ((int)(p_all->ray.xhit_wall) % (int)(p_all->map.col_tile_size))
			* (64 / p_all->map.col_tile_size);
	row = (((p_all->v.correct_top - p_all->v.top + r)
				* TEXTURE_SIZE) / p_all->v.height);
	return (p_all->map_info.i_texture[direction][64 * row + col]);
}

void	render_3d_wall(t_all *p_all, int i)
{
	int		r;
	int		y;

	init_3d(p_all);
	r = 0;
	y = p_all->v.correct_top - 1;
	while (++y < p_all->v.correct_bottom)
	{
		if (!p_all->img.data[WINDOW_WID * y + i])
			p_all->img.data[WINDOW_WID * y + i] = set_wall_color(p_all, r);
		r++;
	}
	draw_ceiling(p_all, i, p_all->v.correct_top, p_all->map_info.c);
	draw_floor(p_all, i, p_all->v.correct_bottom, p_all->map_info.f);
}
