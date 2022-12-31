/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:48:44 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:35:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	if_true_change_val(bool true_false, int set_val, double ret)
{
	if (true_false == true)
		return (set_val);
	else
		return (ret);
}

void	locate_for_mini(int *xp, int *yp, t_point_db p)
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

	dx = (int)(p1.x / p_all->map.col_tile_size)
		- (int)(p2.x / p_all->map.col_tile_size);
	dy = (int)(p1.y / p_all->map.row_tile_size)
		- (int)(p2.y / p_all->map.row_tile_size);
	a = (int)(p1.x / p_all->map.col_tile_size);
	b = (int)(p1.y / p_all->map.row_tile_size);
	if ((dx == 1 && dy == 1) || (dx == 1 && dy == -1)
		|| (dx == -1 && dy == 1) || (dx == -1 && dy == -1))
		return (!ft_strchr("0NSEW", p_all->map.dp_map[b - dy][a])
			&& !ft_strchr("0NSEW", p_all->map.dp_map[b][a - dx]));
	return (false);
}

bool	hit_wall(double x, double y, t_all *p_all)
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
		ix = p_all->map.col - 1;
	if (iy >= (int)p_all->map.row)
		iy = p_all->map.row - 1;
	if (ix < 0)
		ix = 0;
	if (iy < 0)
		iy = 0;
	return (!(ft_strchr("0NSEW", p_all->map.dp_map[iy][ix])));
}
