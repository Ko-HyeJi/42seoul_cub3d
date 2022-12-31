/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:48:54 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 15:50:42 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_point_db(t_point_db *p_point, double x, double y)
{
	p_point->x = x;
	p_point->y = y;
}

void	set_point_i(t_point_i *p_point, int x, int y)
{
	p_point->x = x;
	p_point->y = y;
}
