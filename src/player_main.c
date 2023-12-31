/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:48:42 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:35:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_cos(t_all *p_all, t_point_db *p_mv)
{
	return (p_all->player.x
		+ (int)(p_mv->y) * cos(p_all->player.rotation_angle - p_mv->x));
}

static double	ft_sin(t_all *p_all, t_point_db *p_mv)
{
	return (p_all->player.y
		+ (int)(p_mv->y) * sin(p_all->player.rotation_angle - p_mv->x));
}

static void	update_player2(t_all *p_all, t_point_db	*p_new_player)
{
	t_point_db	old_player;

	set_point_db(&old_player, p_all->player.x, p_all->player.y);
	if (!hit_wall((*p_new_player).x, (*p_new_player).y, p_all)
		&& !check_edge(p_all, old_player, *p_new_player))
	{
		p_all->player.x = (*p_new_player).x;
		p_all->player.y = (*p_new_player).y;
	}
}

void	update_player(t_all *p_all)
{
	t_point_db	dir;
	t_point_db	new_player;
	t_point_db	mv;

	set_point_db(&dir, 0, 0);
	set_point_db(&mv, 0, (int)(dir.x * p_all->player.walk_speed));
	dir.x = if_true_change_val(p_all->key.down, -1, dir.x);
	dir.x = if_true_change_val(p_all->key.up, 1, dir.x);
	if (p_all->key.right)
	{
		dir.x = -1;
		mv.x = M_PI_2;
	}
	if (p_all->key.left)
	{
		dir.x = 1;
		mv.x = M_PI / 2.0;
	}
	dir.y = if_true_change_val(p_all->key.right_rotation, 1, dir.y);
	dir.y = if_true_change_val(p_all->key.left_rotation, -1, dir.y);
	p_all->player.rotation_angle += dir.y * p_all->player.turn_speed;
	set_point_db(&mv, mv.x, (int)(dir.x * p_all->player.walk_speed));
	set_point_db(&new_player, ft_cos(p_all, &mv), ft_sin(p_all, &mv));
	update_player2(p_all, &new_player);
}

void	draw_player(t_all *p_all)
{
	int			x;
	int			y;
	t_point_db	p;

	set_point_db(&p, p_all->player.x, p_all->player.y);
	locate_for_mini(&x, &y, p);
	update_player(p_all);
	draw_ray(p_all);
}
