/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:11:33 by hyko              #+#    #+#             */
/*   Updated: 2022/12/30 21:11:34 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_init(t_ray *p_ray, double ang)
{
	p_ray->ray_angle = normalize_fisheye(ang);
	p_ray->xhit_wall = 0;
	p_ray->yhit_wall = 0;
	p_ray->distance = 0;
	p_ray->vert_hit = false;
	p_ray->ray_faces_down = (p_ray->ray_angle > 0 && p_ray->ray_angle < M_PI);
	p_ray->ray_faces_up = !(p_ray->ray_faces_down);
	p_ray->ray_faces_right
		= (p_ray->ray_angle < 0.5 * M_PI || p_ray->ray_angle > 1.5 * M_PI);
	p_ray->ray_faces_left = !(p_ray->ray_faces_right);
}

void	init_map(t_all *p_all)
{
	p_all->map.row = 0;
	p_all->map.col = 0;
	p_all->map.dp_map = 0;
}

void	init_map_info(t_all *p_all)
{
	p_all->map_info.v_texture[NO] = 0;
	p_all->map_info.v_texture[SO] = 0;
	p_all->map_info.v_texture[WE] = 0;
	p_all->map_info.v_texture[EA] = 0;
	p_all->map_info.i_texture[NO] = 0;
	p_all->map_info.i_texture[SO] = 0;
	p_all->map_info.i_texture[WE] = 0;
	p_all->map_info.i_texture[EA] = 0;
	p_all->map_info.f = 0;
	p_all->map_info.c = 0;
	p_all->map_info.info_cnt = 0;
	p_all->map_info.tile_cnt = 0;
	p_all->map.dp_map = (char **)malloc(sizeof(char *) * (p_all->map.row + 1));
}

void	init_3d(t_all *p_all)
{
	if (p_all->ray.distance == 0)
		p_all->ray.distance = 0.1;
	p_all->v.correct_distance = p_all->ray.distance
		* cos(p_all->ray.ray_angle - p_all->player.rotation_angle);
	p_all->v.distance_plane
		= (WINDOW_WID / 2) / tan(p_all->player.fov_angle / 2);
	p_all->v.projected_height
		= (int)(((p_all->map.col_tile_size + p_all->map.row_tile_size) / 2
				/ p_all->v.correct_distance) * p_all->v.distance_plane);
	p_all->v.top = (WINDOW_HEI / 2) - (p_all->v.projected_height / 2);
	p_all->v.bottom = (WINDOW_HEI / 2) + (p_all->v.projected_height / 2);
	if (p_all->v.top < 0)
		p_all->v.correct_top = 1;
	else
		p_all->v.correct_top = p_all->v.top;
	if (p_all->v.bottom > WINDOW_HEI)
		p_all->v.correct_bottom = WINDOW_HEI;
	else
		p_all->v.correct_bottom = p_all->v.bottom;
	p_all->v.height = p_all->v.bottom - p_all->v.top;
}
