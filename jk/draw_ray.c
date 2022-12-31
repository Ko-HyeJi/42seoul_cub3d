/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:06 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 15:47:07 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_all *p_all, double dx, double dy)
{
	t_point_db	xy_ray;
	t_point_db	delta;
	t_point_db	p2;
	t_point_i	xy_row;
	double		max_val;

	set_point_db(&xy_ray, p_all->player.x, p_all->player.y);
	set_point_i(&xy_row, 0, 0);
	max_val = fmax(fabs(dx), fabs(dy));
	if (max_val == 0)
		return ;
	set_point_db(&delta, dx / max_val, dy / max_val);
	while (1)
	{
		set_point_db(&p2, xy_ray.x + delta.x, xy_ray.y + delta.y);
		if (!hit_wall(p2.x, p2.y, p_all) && !check_edge(p_all, xy_ray, p2))
		{
			locate_for_mini(&(xy_row.x), &(xy_row.y), xy_ray);
			p_all->img.data[WINDOW_WID * (xy_row.y) + (xy_row.x)] = RED;
		}
		else
			break ;
		set_point_db(&xy_ray, xy_ray.x + delta.x, xy_ray.y + delta.y);
	}
}

void	draw_one_ray(t_all *p_all, double ang, int i)
{
	t_temp_ray	horz;
	t_temp_ray	vert;

	ray_init(&(p_all->ray), ang);
	calc_horz_ray(p_all, &horz);
	calc_vert_ray(p_all, &vert);
	if (vert.distance < horz.distance)
	{
		p_all->ray.xhit_wall = vert.xhit_wall;
		p_all->ray.yhit_wall = vert.yhit_wall;
		p_all->ray.distance = vert.distance;
		p_all->ray.vert_hit = true;
	}
	else
	{
		p_all->ray.xhit_wall = horz.xhit_wall;
		p_all->ray.yhit_wall = horz.yhit_wall;
		p_all->ray.distance = horz.distance;
		p_all->ray.vert_hit = false;
	}
	draw_line(p_all,
		p_all->ray.xhit_wall - p_all->player.x,
		p_all->ray.yhit_wall - p_all->player.y);
	render_3d_wall(p_all, i);
}

void	draw_ray(t_all *p_all)
{
	double	angle;
	double	max_angle;
	int		i;

	angle = p_all->player.rotation_angle - (p_all->player.fov_angle / 2.0);
	max_angle = p_all->player.rotation_angle + (p_all->player.fov_angle / 2.0);
	i = 0;
	while (i < RAY_COUNT)
	{
		draw_one_ray(p_all, angle, i);
		angle += p_all->player.fov_angle / RAY_COUNT;
		i++;
	}
}
