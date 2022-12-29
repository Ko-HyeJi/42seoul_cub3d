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
	p_all->map.dp_map = (char **)malloc(sizeof(char *) * (p_all->map.row + 1));
	p_all->map_info.info_cnt = 0;
	p_all->map_info.tile_cnt = 0;
}
