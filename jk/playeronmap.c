#include "cub3d.h"

void init_player(t_all *p_all)
{
	p_all->player.x = WINDOW_WID / 2;
	p_all->player.y = WINDOW_HEI / 2;
	p_all->player.rotation_angle = PI / 2;
	p_all->player.walk_speed = 1;
	p_all->player.turn_speed = 4 * (PI / 180);
}

bool hit_wall(double x, double y, t_all *p_all)
{
	int	ix;
	int	iy;

	if (x < 0 || x > WINDOW_WID || y < 0 || y > WINDOW_HEI)
	{
		return (true);
	}
	ix = floor(x / p_all->map.col_tile_size);
	iy = floor(y / p_all->map.row_tile_size);
	return (p_all->map.dp_map[iy][ix] != '0');
}

void update_player(t_all *p_all)
{
	double turnDirection;
	double walkDirection;
	double newPlayerX;
	double newPlayerY;

	turnDirection = 0;
	walkDirection = 0;
	if (p_all->key.down)
		walkDirection = -1;
	if (p_all->key.up)
		walkDirection = 1;
	if (p_all->key.right)
		turnDirection = 1;
	if (p_all->key.left)
		turnDirection = -1;

	p_all->player.rotation_angle += turnDirection * p_all->player.turn_speed;
	int moveStep;
	moveStep = walkDirection * p_all->player.walk_speed;
	newPlayerX = p_all->player.x + moveStep * cos(p_all->player.rotation_angle);
	newPlayerY = p_all->player.y + moveStep * sin(p_all->player.rotation_angle);

	if (!hit_wall(newPlayerX, newPlayerY, p_all))
	{
		p_all->player.x = newPlayerX;
		p_all->player.y = newPlayerY;
	}
}

void draw_player(t_all *p_all)
{
	p_all->img.data = (int *)mlx_get_data_addr(p_all->img.img, &(p_all->img.bpp), 
										&(p_all->img.size_line), &(p_all->img.endian));

	int	x;
	int	y;

	locate_for_mini(&x, &y, p_all->player.x, p_all->player.y, p_all);
	update_player(p_all);
	int	row;
	row = (-(MINI_SCALE * p_all->map.row_tile_size) / 10);
	while (row <= (MINI_SCALE * p_all->map.row_tile_size / 10))
	{
		int	col;
		col = (-(MINI_SCALE * p_all->map.col_tile_size) / 10);
		while (col <= (MINI_SCALE * p_all->map.col_tile_size / 10))
		{
			p_all->img.data[WINDOW_WID * (y + row) + (x + col)] = 0x0000FF;
			col++;
		}
		row++;
	}
	draw_ray(p_all);
}

void render_player(t_all *p_all)
{
	draw_player(p_all);
}