/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeekim <jeekim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:29 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 15:47:30 by jeekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all	s_all;

	ft_init(&s_all);
	parse_map(argc, argv, &s_all);
	set_texture_img(&s_all);
	loop_hook(&s_all);
	return (0);
}
