#include "cub3d.h"

void ray_init(t_ray *p_ray, double ang)
{
	p_ray->ray_angle = normalize_fisheye(ang);
	p_ray->xhit_wall = 0;
	p_ray->yhit_wall = 0;
	p_ray->distance = 0;
	p_ray->vert_hit = false;
	p_ray->ray_faces_down = p_ray->ray_angle > 0 && p_ray->ray_angle < PI;
	p_ray->ray_faces_up = !(p_ray->ray_faces_down);
	p_ray->ray_faces_right = p_ray->ray_angle < 0.5 * PI || p_ray->ray_angle > 1.5 *  PI;
	p_ray->ray_faces_left = !(p_ray->ray_faces_right);
}