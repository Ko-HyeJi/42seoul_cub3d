#include "cub3d.h"

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
