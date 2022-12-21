#include "cub3d.h"

void locate_for_mini(int *xp, int *yp, t_point p, t_all *p_all)
{
	*xp = (int)((1 - MINI_SCALE) * p_all->map.col_tile_size * p_all->map.col + MINI_SCALE * p.x);
	*yp = (int)((1 - MINI_SCALE) * p_all->map.row_tile_size * p_all->map.row + MINI_SCALE * p.y);
}//화면 맨 아래, 맨 오른쪽에 위치할수있게설정.

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
	}//타일 하나 그림
}

void render_map(t_all *p_all)
{
	unsigned long long	j;
	unsigned long long	k;
	//미니맵과, 3d 동시에 그려주기.

	init_3d(p_all);
	k = 0;
	while (k < p_all->map.row)//미니맵 그리기
	{
		j = 0;
		while (j < p_all->map.col)
		{
			if (p_all->map.dp_map[k][j] == '1')
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), BLACK);
			else
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), WHITE);
			j++;
		}
		k++;
	}
}