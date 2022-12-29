/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:29:16 by hyko              #+#    #+#             */
/*   Updated: 2022/12/29 18:31:01 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_location_and_direction(
	t_all *p_all, unsigned long long i, unsigned long long j)
{
	p_all->player.x
		= (double)(WINDOW_WID / p_all->map.col) * ((double)(j) + 0.5);
	p_all->player.y
		= (double)(WINDOW_HEI / p_all->map.row) * ((double)(i) + 0.5);
	if (p_all->map.dp_map[i][j] == 'N')
		p_all->player.rotation_angle = 270;
	else if (p_all->map.dp_map[i][j] == 'S')
		p_all->player.rotation_angle = 90;
	else if (p_all->map.dp_map[i][j] == 'E')
		p_all->player.rotation_angle = 0;
	else if (p_all->map.dp_map[i][j] == 'W')
		p_all->player.rotation_angle = 180;
}

static void	check_border(char **map, int row, int col)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == row - 1 || j == 0 || j == col - 1)
				&& ft_strchr("0NSEW", map[i][j]))
				display_err_msg_and_exit("Invalid Map");
			j++;
		}
		i++;
	}
}

static int	find_player(t_all *p_all, int i, int j)
{
	if (ft_strchr("NSEW", p_all->map.dp_map[i][j]))
	{
		set_player_location_and_direction(p_all, i, j);
		return (1);
	}
	return (0);
}

static void	is_map_blocked(t_all *p_all, int i, int j)
{
	if (ft_strchr("0NSEW", p_all->map.dp_map[i][j]))
	{
		if (ft_strchr(" \n", p_all->map.dp_map[i - 1][j])
			|| ft_strchr(" \n", p_all->map.dp_map[i + 1][j])
			|| ft_strchr(" \n", p_all->map.dp_map[i][j - 1])
			|| ft_strchr(" \n", p_all->map.dp_map[i][j + 1]))
			display_err_msg_and_exit("Invalid Map");
	}
}

void	is_vaild_map(t_all *p_all)
{
	unsigned long long	i;
	unsigned long long	j;
	unsigned long long	player;

	i = 0;
	j = 0;
	player = 0;
	while (i < p_all->map.row)
	{
		j = 0;
		while (p_all->map.dp_map[i][j])
		{
			player += find_player(p_all, i, j);
			check_border(p_all->map.dp_map, p_all->map.row, p_all->map.col);
			is_map_blocked(p_all, i, j);
			j++;
		}
		i++;
	}
	if (player != 1)
		display_err_msg_and_exit("Invalid Player");
}
