#include "cub3d.h"

double distance_btw_points(double xa, double ya, double xb, double yb)
{
	return (sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb)));
}

void calc_distance(t_all *p_all, t_temp_ray *hv)
{
	if (hv->found_wallHit)
		hv->distance = distance_btw_points(p_all->player.x, p_all->player.y
										, hv->xhit_wall, hv->yhit_wall);
	else
		hv->distance = __DBL_MAX__;
}

void calc_ray(t_all *p_all, t_temp_ray *hv, int a, int b)
{
	double	xnext_touch;
	double	ynext_touch;

	xnext_touch = hv->xintercept;
	ynext_touch = hv->yintercept;

	while (xnext_touch >= 0 && xnext_touch <= WINDOW_WID
		&& ynext_touch >= 0 && ynext_touch <= WINDOW_HEI)
	{
		if (hit_wall(xnext_touch - a, ynext_touch - b, p_all))
		{
			hv->found_wallHit = true;
			hv->xhit_wall = xnext_touch;
			hv->yhit_wall = ynext_touch;
			break;
		}
		else
		{
			xnext_touch += hv->xstep;
			ynext_touch += hv->ystep;
		}
	}
	calc_distance(p_all, hv);
}

void calc_horz_ray(t_all *p_all, t_temp_ray *p_horz)
{
	p_horz->found_wallHit = false;
	p_horz->xhit_wall = 0;
	p_horz->yhit_wall = 0;

	p_horz->yintercept = floor(p_all->player.y / p_all->map.row_tile_size) * p_all->map.row_tile_size;
	if (p_all->ray.ray_faces_down)
		p_horz->yintercept += p_all->map.row_tile_size;
	else
		;

	p_horz->xintercept = p_all->player.x
						+ (p_horz->yintercept - p_all->player.y) / tan(p_all->ray.ray_angle);

	p_horz->ystep = p_all->map.row_tile_size;
	if (p_all->ray.ray_faces_up)
		p_horz->ystep *= -1;
	else
		p_horz->ystep *= 1;

	p_horz->xstep = p_all->map.row_tile_size / tan(p_all->ray.ray_angle);
	if (p_all->ray.ray_faces_left && p_horz->xstep > 0)
		p_horz->xstep *= -1;
	else
		p_horz->xstep *= 1;
	if (p_all->ray.ray_faces_right && p_horz->xstep < 0)
		p_horz->xstep *= -1;
	else
		p_horz->xstep *= 1;
	
	calc_ray(p_all, p_horz, 0, p_all->ray.ray_faces_up);
}

void calc_vert_ray(t_all *p_all, t_temp_ray *p_vert)
{
	p_vert->found_wallHit = false;
	p_vert->xhit_wall = 0;
	p_vert->yhit_wall = 0;

	p_vert->xintercept = floor(p_all->player.x / p_all->map.col_tile_size) * p_all->map.col_tile_size;
	if (p_all->ray.ray_faces_right)
		p_vert->xintercept += p_all->map.col_tile_size;
	else
		;

	p_vert->yintercept = p_all->player.y
						+ (p_vert->xintercept - p_all->player.x) * tan(p_all->ray.ray_angle);

	p_vert->xstep = p_all->map.col_tile_size;
	if (p_all->ray.ray_faces_left)
		p_vert->xstep *= -1;
	else
		p_vert->xstep *= 1;

	p_vert->ystep = p_all->map.col_tile_size * tan(p_all->ray.ray_angle);
	if (p_all->ray.ray_faces_up && p_vert->ystep > 0)
		p_vert->ystep *= -1;
	else
		p_vert->ystep *= 1;
	if (p_all->ray.ray_faces_down && p_vert->ystep < 0)
		p_vert->ystep *= -1;
	else
		p_vert->ystep *= 1;
	
	calc_ray(p_all, p_vert, p_all->ray.ray_faces_left, 0);
}