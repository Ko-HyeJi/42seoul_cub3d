#include "cub3d.h"

void locate_for_mini(int *xp, int *yp, t_point_db p)
{
	*xp = (int)(MINI_SCALE * p.x);
	*yp = (int)(MINI_SCALE * p.y);
}

bool	check_edge(t_all *p_all, t_point_db p1, t_point_db p2)
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
