#include "cub3d.h"

// void locate_for_mini(int *xp, int *yp, int x, int y, t_all *p_all)
void locate_for_mini(int *xp, int *yp, t_point p, t_all *p_all)
{
	*xp = (int)((1 - MINI_SCALE) * p_all->map.col_tile_size * p_all->map.col + MINI_SCALE * p.x);
	*yp = (int)((1 - MINI_SCALE) * p_all->map.row_tile_size * p_all->map.row + MINI_SCALE * p.y);
}
void fill_square(t_all *p_all, int x, int y, int color)
{
	int j;
	int k;
	t_point	p;

	set_point(&p, x, y);
	locate_for_mini(&x, &y, p, p_all);
	k = 0;
	while (k < (int)(MINI_SCALE * p_all->map.row_tile_size))
	{
		j = 0;
		while (j < (int)(MINI_SCALE * p_all->map.col_tile_size))
		{
			p_all->img.data[(int)(WINDOW_WID) * (y + k) + (x + j)] = color;
			j++;
		}
		k++;
	}
}

void render_map(t_all *p_all)
{
	unsigned long long	j;
	unsigned long long	k;
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEI)
	{
		x = 0;
		while (x < WINDOW_WID)
		{
			p_all->img.data[WINDOW_WID * y + x] = PINK;
			x++;
		}
		y++;
	}
	k = 0;
	while (k < p_all->map.row)
	{
		j = 0;
		while (j < p_all->map.col)
		{
			if (p_all->map.dp_map[k][j] == '1')
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), 0x000000);
			else
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), 0xffffff);
			j++;
		}
		k++;
	}
}