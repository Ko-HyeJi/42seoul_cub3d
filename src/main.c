/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 15:47:29 by jeekim            #+#    #+#             */
/*   Updated: 2022/12/31 16:35:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all	all;

	ft_init(&all);
	parse_map(argc, argv, &all);
	set_texture_img(&all);
	loop_hook(&all);
	return (0);
}
