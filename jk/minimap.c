#include "cub3d.h"

void locate_for_mini(int *xp, int *yp, t_point p)
{
	*xp = (int)(MINI_SCALE * p.x);
	*yp = (int)(MINI_SCALE * p.y);
}//미니맵 위치 좌상단으로 변경

void fill_square(t_all *p_all, int x, int y, int color)
{
	int j;
	int k;
	t_point	p;

	set_point(&p, x, y);
	locate_for_mini(&x, &y, p);
	k = 0;
	while (k <= (int)(MINI_SCALE * p_all->map.row_tile_size))
	{
		j = 0;
		while (j <= (int)(MINI_SCALE * p_all->map.col_tile_size))
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

	init_img_data(p_all);
	k = 0;
	while (k < p_all->map.row)//미니맵 그리기
	{
		j = 0;
		while (j < p_all->map.col)
		{
			if (p_all->map.dp_map[k][j] == '1')
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), BLACK);
			else if (ft_strchr("0NSEW",p_all->map.dp_map[k][j]))
				fill_square(p_all, (int)(p_all->map.col_tile_size * j), (int)(p_all->map.row_tile_size * k), WHITE);
			else
				;
			j++;
		}
		k++;
	}
}

