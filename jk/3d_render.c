#include "cub3d.h"


void init_img_data(t_all* p_all) 
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEI)
	{
		x = 0;
		while (x < WINDOW_WID)
		{
			p_all->img.data[WINDOW_WID * y + x] = 0;
			x++;
		}
		y++;
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
		while (x < WALL_STRIP_WIDTH)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
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
		while (x < WALL_STRIP_WIDTH)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
			x++;
		}
		y++;
	}
}

void    render_3d_wall(t_all *p_all, int ray_num)
{
	double	correct_distance;
	double  distance_project_plane;
	double  projected_wall_height;

	correct_distance = p_all->ray.distance * cos(p_all->ray.ray_angle - p_all->player.rotation_angle);
	distance_project_plane = (WINDOW_WID / 2) / tan(FOV_ANGLE / 2);
	projected_wall_height = (p_all->map.row_tile_size / correct_distance) * distance_project_plane;//?

	int wall_strip_hei;
	wall_strip_hei = (int)projected_wall_height;

	int wall_top_pixel;
	wall_top_pixel = (WINDOW_HEI / 2) - (wall_strip_hei / 2) - p_all->player.updown_sight;
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	else
		;
	int wall_bottom_pixel;
	wall_bottom_pixel = (WINDOW_HEI / 2) + (wall_strip_hei / 2) - p_all->player.updown_sight;//?
	if (wall_bottom_pixel > WINDOW_HEI)
		wall_bottom_pixel = WINDOW_HEI;
	else
		;
	
	int color;
	if (p_all->ray.vert_hit)
		color = WHITE;
	else
		color = GREY;
	
	int x;
	int y;
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		x = 0;
		while (x < WALL_STRIP_WIDTH)
		{
			if (!p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)])
				p_all->img.data[WINDOW_WID * y + (x + ray_num * WALL_STRIP_WIDTH)] = color;
				//현재위치픽셀 색이 초기설정색이면 색을 덧입히기
			x++;
		}
		y++;
	}
	draw_ceiling(p_all, ray_num, wall_top_pixel, SKY);
	draw_floor(p_all, ray_num, wall_bottom_pixel, GROUND);
}//ray_num의 순번을 잘 넘겨주기 위해 draw_ray() 수정함
//화면~player 거리
//y축 기준으로 wall_top_pixel~wall_bottom_pixel 그려줌.
