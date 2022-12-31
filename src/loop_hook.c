/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:27 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:00:08 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_loop_hook(t_all *p_all)
{
	update_player(p_all);
	render_map(p_all);
	draw_player(p_all);
	mlx_put_image_to_window(p_all->mlx, p_all->win, p_all->img.img, 0, 0);
	return (0);
}

void	loop_hook(t_all *p_all)
{
	mlx_hook(p_all->win, X_EVENT_KEY_PRESS, 0, &key_press, p_all);
	mlx_hook(p_all->win, X_EVENT_KEY_RELEASE, 0, &key_release, p_all);
	mlx_hook(p_all->win, X_EVENT_WINDOW_DESTROY, 0, &mouse, 0);
	mlx_loop_hook(p_all->mlx, &ft_loop_hook, p_all);
	mlx_loop(p_all->mlx);
}
