/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:20 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:27:10 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_press(int keycode, t_all *p_all)
{
	if (keycode == K_W)
		p_all->key.up = true;
	else if (keycode == K_S)
		p_all->key.down = true;
	else if (keycode == K_A)
		p_all->key.left = true;
	else if (keycode == K_D)
		p_all->key.right = true;
	else if (keycode == K_RIGHT)
		p_all->key.right_rotation = true;
	else if (keycode == K_LEFT)
		p_all->key.left_rotation = true;
	else if (keycode == K_ESC)
		exit (0);
	return (0);
}

int	key_release(int keycode, t_all *p_all)
{
	if (keycode == K_W)
		p_all->key.up = false;
	else if (keycode == K_S)
		p_all->key.down = false;
	else if (keycode == K_A)
		p_all->key.left = false;
	else if (keycode == K_D)
		p_all->key.right = false;
	else if (keycode == K_RIGHT)
		p_all->key.right_rotation = false;
	else if (keycode == K_LEFT)
		p_all->key.left_rotation = false;
	else if (keycode == K_ESC)
		exit (0);
	return (0);
}

int	mouse(void)
{
	exit(0);
}
