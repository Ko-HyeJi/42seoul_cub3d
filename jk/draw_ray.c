#include "cub3d.h"

void	draw_line(t_all *p_all, double dx, double dy)
{
	double	ray_x;
	double	ray_y;
	double	max_val;
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	ray_x = p_all->player.x;
	ray_y = p_all->player.y;
	max_val = fmax(fabs(dx), fabs(dy));
	if (max_val == 0)
		return ;
	x = 0;
	y = 0;
	dx /= max_val;
	dy /= max_val;
	while (1)
	{
		set_point(&p1, ray_x, ray_y);
		set_point(&p2, ray_x + dx, ray_y + dy);
		if (!hit_wall(p2.x, p2.y, p_all) && !check_edge(p_all, p1, p2))
		{
			locate_for_mini(&x, &y, p1);
			p_all->img.data[WINDOW_WID * y + x] = RED;
		}
		else
			break ;
		ray_x += dx;
		ray_y += dy;
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
	draw_line(p_all, p_all->ray.xhit_wall - p_all->player.x, p_all->ray.yhit_wall - p_all->player.y);
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
