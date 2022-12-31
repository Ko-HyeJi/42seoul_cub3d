/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:06 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:35:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_one_ray(t_all *p_all, double ang, int i)
{
	t_temp_ray	horz;
	t_temp_ray	vert;

	init_ray(&(p_all->ray), ang);
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
