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

void ray_init(t_ray *p_ray, double ang)//t_all이 아니라 t_ray로
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
		//삼항 생략
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

void draw_line(t_all *p_all, double xa, double ya, double xb, double yb)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_val;
	int		x;
	int		y;

	ray_x = p_all->player.x;
	ray_y = p_all->player.y;
	dx = xa - xb;
	dy = ya - yb;
	max_val = fmax(fabs(dx), fabs(dy));
	x = 0;
	y = 0;
	dx /= max_val;
	dy /= max_val;
	while (1)
	{
		if (!hit_wall(ray_x, ray_y, p_all))
		{
			locate_for_mini(&x, &y, ray_x, ray_y, p_all);
			p_all->img.data[WINDOW_WID * y + x] = 0xFF0000;
		}
		else
			break;
		ray_x += dx;
		ray_y += dy;
	}
}//좌표 2개를 받아서 선을 그려준다
//도트 단위로 그려진다. 기울기는 항상 달라서 x좌표, y좌표 중 기준을 정해서 도트씩 그려야한다.
//(기준이 되는 쪽의 미분값이 1.)
//두 점의 x좌표와 y좌표 각각 차이를 긴쪽을 기준으로 하는게 광선을 좀 더 세밀하게 그릴수있다
//while문을 통해서 벽을 만날때까지 빨간색으로 그려준다.

void draw_one_ray(t_all *p_all, double ang)
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
	draw_line(p_all, p_all->player.x, p_all->player.y, p_all->ray.xhit_wall, p_all->ray.yhit_wall);
}//수평으로 닿는 좌표와 수직으로 닿는 좌표를 모두 구한 뒤 if문으로 거리 비교해서 짧은쪽의 데이터를
//ray 구조체에 저장해준다.
//이렇게 저장한 값들을 draw_line()을 사용해서 최종적으로 한개의 광선을 그린다.

void draw_ray(t_all *p_all)
{
	double angle;
	double max_angle;

	angle = p_all->player.rotation_angle;
	max_angle = p_all->player.rotation_angle + (RAY_RANGE / 2.0);

	while (angle <= max_angle)
	{
		draw_one_ray(p_all, angle);
		draw_one_ray(p_all, angle - (RAY_RANGE / 2.0));//min_angle
		angle += (RAY_RANGE / 2.0) / ((RAY_COUNT - 1) / 2.0);
	}
}
//player.rotation_angle 기준으로 양옆 RAY_RANGE/2 시야 범위
//만든 while문은 항상 2개이상의 광선을 그리게함.
//광선을 하나씩 그리도록 구현해도되지만, RAY_COUNT를 의도적으로 2개이상 지정해주는건
//안어려워서 그냥 이렇게..
//while문 한번이라도 적게 돌리는게 성능향상에 도움 될것같기도하대
