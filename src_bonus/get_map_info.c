/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:53 by hyko              #+#    #+#             */
/*   Updated: 2022/12/30 21:12:04 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_type(char *line, t_all *p_all, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
		is_valid_texture(line += (i + 2), NO, p_all);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		is_valid_texture(line += (i + 2), SO, p_all);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		is_valid_texture(line += (i + 2), WE, p_all);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		is_valid_texture(line += (i + 2), EA, p_all);
	else if (line[i] == 'F')
		is_valid_color(line += (i + 1), F, p_all);
	else if (line[i] == 'C')
		is_valid_color(line += (i + 1), C, p_all);
	else
		display_err_msg_and_exit("Invalid element in map file");
}

void	get_map_info(char *line, t_all *p_all)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' && (p_all->map_info.tile_cnt == 0
			|| p_all->map_info.tile_cnt == (int)p_all->map.row))
	{
		free(line);
		return ;
	}
	if (p_all->map_info.info_cnt < 6)
	{
		check_type(line, p_all, i);
		p_all->map_info.info_cnt++;
		free(line);
		return ;
	}
	if (p_all->map_info.info_cnt == 6 && (line[i] == '1' || line[i] == '\n'))
		is_valid_tile(line, p_all);
	else if (p_all->map_info.info_cnt == 6 && line[i] == '\0')
		return ;
	else
		display_err_msg_and_exit("Invalid element in map file");
}
