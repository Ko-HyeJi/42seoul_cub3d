#include "cub3d.h"

bool	check_edge(t_all *p_all, t_point p1, t_point p2)
{
	int	dx;
	int	dy;
	int	a;
	int	b;

	dx = (int)(p1.x / p_all->map.col_tile_size) - (int)(p2.x / p_all->map.col_tile_size);
	dy = (int)(p1.y / p_all->map.row_tile_size) - (int)(p2.y / p_all->map.row_tile_size);
	a = (int)(p1.x / p_all->map.col_tile_size);
	b = (int)(p1.y / p_all->map.row_tile_size);
	if ((dx == 1 && dy == 1) || (dx == 1 && dy == -1) || (dx == -1 && dy == 1) || (dx == -1 && dy == -1))
		return (!ft_strchr("0NSEW", p_all->map.dp_map[b - dy][a])
			&& !ft_strchr("0NSEW", p_all->map.dp_map[b][a - dx]));
	return (false);
}

bool hit_wall(double x, double y, t_all *p_all)
{
	int	ix;
	int	iy;

	if (x < 0 || x >= WINDOW_WID || y < 0 || y >= WINDOW_HEI)
	{
		return (true);
	}
	ix = (int)floor(x / p_all->map.col_tile_size);
	iy = (int)floor(y / p_all->map.row_tile_size);
	if (ix >= (int)p_all->map.col)
		ix--;
	if (iy >= (int)p_all->map.row)
		iy--;
	
	return (!(ft_strchr("0NSEW", p_all->map.dp_map[iy][ix]))); //player 좌표도 벽이 아닌걸로 처리해줘야함 (hyko)
}

void update_player(t_all *p_all)
{
	double turnDirection;
	double walkDirection;
	double newPlayerX;
	double newPlayerY;
	double	move_side;
	t_point	p1;
	t_point	p2;

	turnDirection = 0;
	walkDirection = 0;
	move_side = 0;
	if (p_all->key.down)
		walkDirection = -1;
	if (p_all->key.up)
		walkDirection = 1;
	if (p_all->key.right)
	{
		walkDirection = -1;
		move_side = HALF_PI;
	}
	if (p_all->key.left)
	{
		walkDirection = 1;
		move_side = PI / 2.0;
	}
	if (p_all->key.right_rotation)
		turnDirection = 1;
	if (p_all->key.left_rotation)
		turnDirection = -1;

	p_all->player.rotation_angle += turnDirection * p_all->player.turn_speed;
	int moveStep;
	moveStep = walkDirection * p_all->player.walk_speed;
	newPlayerX = p_all->player.x + moveStep * cos(p_all->player.rotation_angle - move_side);
	newPlayerY = p_all->player.y + moveStep * sin(p_all->player.rotation_angle - move_side);
	set_point(&p1, p_all->player.x, p_all->player.y);
	set_point(&p2, newPlayerX, newPlayerY);
	if (!hit_wall(newPlayerX, newPlayerY, p_all) && !check_edge(p_all, p1, p2))
	{
		p_all->player.x = newPlayerX;
		p_all->player.y = newPlayerY;
	}
}

void draw_player(t_all *p_all)
{
	int		x;
	int		y;
	t_point	p;

	set_point(&p, p_all->player.x, p_all->player.y);
	locate_for_mini(&x, &y, p);
	update_player(p_all);
	int	row;
	row = (-(MINI_SCALE * p_all->map.row_tile_size) / 10);
	while (row <= (MINI_SCALE * p_all->map.row_tile_size / 10))
	{
		int	col;
		col = (-(MINI_SCALE * p_all->map.col_tile_size) / 10);
		while (col <= (MINI_SCALE * p_all->map.col_tile_size / 10))
		{
			p_all->img.data[WINDOW_WID * (y + row) + (x + col)] = BLUE;
			col++;
		}
		row++;
	}
	draw_ray(p_all);
}
