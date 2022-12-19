#include "cub3d.h"

double normalize_angle(double ang)
{
	if (ang >= 0)
	{
		while (ang >= TWO_PI)
			ang -= TWO_PI;
	}
	else
	{
		while (ang <= 0)
			ang += TWO_PI;
	}
	return ang;
}

void ray_init(t_ray *p_ray, double ang)
{
	p_ray->ray_angle = normalize_angle(ang);
	p_ray->xhit_wall = 0;
	p_ray->yhit_wall = 0;
	p_ray->distance = 0;

	p_ray->vert_hit = false;

	p_ray->ray_faces_down = p_ray->ray_angle > 0 && p_ray->ray_angle < PI;
	p_ray->ray_faces_up = !(p_ray->ray_faces_down);
	p_ray->ray_faces_right = p_ray->ray_angle < 0.5 * PI || p_ray->ray_angle > 1.5 *  PI;
	p_ray->ray_faces_left = !(p_ray->ray_faces_right);
}//t_ray 구조체 초기화

void calc_distance(t_all *p_all, t_temp_ray *hv)
{
	if (hv->found_wallHit)
		hv->distance = distance_btw_points(p_all->player.x, p_all->player.y
										, hv->xhit_wall, hv->yhit_wall);
	else
		hv->distance = __DBL_MAX__;//써두되나...
}
//벽 찾았으면 거리 계산함
//못찾았으면 double 자료형 최대값 지정.(수평경계좌표와 수직경계좌표를 비교할때 항상 선택받지 못하도록 하기 위해) 

double distance_btw_points(double xa, double ya, double xb, double yb)
{
	return (sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb)));
}

void calc_ray(t_all *p_all, t_temp_ray *hv)
{
	double	xnext_touch;
	double	ynext_touch;

	xnext_touch = hv->xintercept;
	ynext_touch = hv->yintercept;

	while (xnext_touch >= 0 && xnext_touch <= WINDOW_WID
		&& ynext_touch >= 0 && ynext_touch <= WINDOW_HEI)
	{
		if (hit_wall(xnext_touch, ynext_touch - (p_all->ray.ray_faces_up), p_all))
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
}//실질적으로 벽 위치 찾는다
//calc_horz_ray(), calc_vert_ray()에서 intercept, step이 정해지고,
//여기선 그 값들을 이용해서 계산한다
//calc_distance()는 거리를 계산해준다
void calc_horz_ray(t_all *p_all, t_temp_ray *p_horz)
{
	p_horz->found_wallHit = false;
	p_horz->xhit_wall = 0;
	p_horz->yhit_wall = 0;

	p_horz->yintercept = floor(p_all->player.y / p_all->map.row_tile_size) * p_all->map.row_tile_size;//
	if (p_all->ray.ray_faces_down)
		p_horz->yintercept += p_all->map.row_tile_size;
	else
		p_horz->yintercept += 0;

	p_horz->xintercept = p_all->player.x
						+ (p_horz->yintercept - p_all->player.y) / tan(p_all->ray.ray_angle);

	p_horz->ystep = p_all->map.row_tile_size;
	if (p_all->ray.ray_faces_up)
		p_horz->ystep *= -1;
	else
		p_horz->ystep *= 1;

	p_horz->xstep = p_all->map.col_tile_size / tan(p_all->ray.ray_angle);
	if (p_all->ray.ray_faces_left && p_horz->xstep > 0)
		p_horz->xstep *= -1;
	else
		p_horz->xstep *= 1;
	if (p_all->ray.ray_faces_right && p_horz->xstep < 0)
		p_horz->xstep *= -1;
	else
		p_horz->xstep *= 1;
	
	calc_ray(p_all, p_horz);
}//수평 계산

void calc_vert_ray(t_all *p_all, t_temp_ray *p_vert)
{
	p_vert->found_wallHit = false;
	p_vert->xhit_wall = 0;
	p_vert->yhit_wall = 0;

	p_vert->xintercept = floor(p_all->player.x / p_all->map.col_tile_size) * p_all->map.col_tile_size;
	if (p_all->ray.ray_faces_right)
		p_vert->xintercept += p_all->map.col_tile_size;
	else
		p_vert->xintercept += 0;

	p_vert->yintercept = p_all->player.y
						+ (p_vert->xintercept - p_all->player.x) * tan(p_all->ray.ray_angle);

	p_vert->xstep = p_all->map.col_tile_size;
	if (p_all->ray.ray_faces_left)
		p_vert->xstep *= -1;
	else
		p_vert->xstep *= 1;

	p_vert->ystep = p_all->map.row_tile_size * tan(p_all->ray.ray_angle);
	if (p_all->ray.ray_faces_up && p_vert->ystep > 0)
		p_vert->ystep *= -1;
	else
		p_vert->ystep *= 1;
	if (p_all->ray.ray_faces_down && p_vert->ystep < 0)
		p_vert->ystep *= -1;
	else
		p_vert->ystep *= 1;
	
	calc_ray(p_all, p_vert);
}

void set_point(t_point *p_point, double x, double y)
{
	p_point->x = x;
	p_point->y = y;
}

void draw_line(t_all *p_all, double dx, double dy)
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
		if (!hit_wall(ray_x + dx, ray_y + dy, p_all))
		{
			locate_for_mini(&x, &y, p1, p_all);
			p_all->img.data[WINDOW_WID * y + x] = RED;
		}
		else
			break;
		ray_y += dy;
		ray_x += dx;
	}
}

void draw_one_ray(t_all *p_all, double ang, int i)
{
	t_temp_ray horz;
	t_temp_ray vert;

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
//각각 광선에 대한 정보는 이 함수에 와서야 결정된다.

void draw_ray(t_all *p_all)
{
	double	angle;
	double	max_angle;
	int		i;

	angle = p_all->player.rotation_angle - (RAY_RANGE / 2.0);
	max_angle = p_all->player.rotation_angle + (RAY_RANGE / 2.0);
	i = 0;

	while (i < RAY_COUNT)
	{
		draw_one_ray(p_all, angle, i);
		angle += RAY_RANGE / RAY_COUNT;
		i++;
	}
}
//원래 광선 동시에 2개 그렸는데, 왼쪽부터 하나씩 그려주는걸로 수정