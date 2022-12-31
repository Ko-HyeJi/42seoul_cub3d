/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:48:38 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:00:44 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_square(t_all *p_all, int x, int y, int color)
{
	int			j;
	int			k;
	t_point_db	p;

	set_point_db(&p, x, y);
	locate_for_mini(&x, &y, p);
	k = 0;
	while (k <= (int)(MINI_SCALE * p_all->map.row_tile_size))
	{
		j = 0;
		while (j <= (int)(MINI_SCALE * p_all->map.col_tile_size))
		{
			p_all->img.data[(int)(WINDOW_WID) *(y + k) + (x + j)] = color;
			j++;
		}
		k++;
	}
}

void	render_map(t_all *p_all)
{
	unsigned long long	j;
	unsigned long long	k;

	init_img_data(p_all);
	k = 0;
	while (k < p_all->map.row)
	{
		j = 0;
		while (j < p_all->map.col)
		{
			if (p_all->map.dp_map[k][j] == '1')
				fill_square(p_all,
					(int)(p_all->map.col_tile_size * j),
					(int)(p_all->map.row_tile_size * k), BLACK);
			else if (ft_strchr("0NSEW", p_all->map.dp_map[k][j]))
				fill_square(p_all,
					(int)(p_all->map.col_tile_size * j),
					(int)(p_all->map.row_tile_size * k), WHITE);
			j++;
		}
		k++;
	}
}
