/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:36:53 by hyko              #+#    #+#             */
/*   Updated: 2022/12/29 18:33:00 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_valid_texture(char *path, int type, t_all *p_all)
{
	int img_width = 64; //나중에 헤더에 정의
	int img_height = 64;

	int e_flag;
	void* tmp;

	while(*path == ' ')
		path++;
	if (path[ft_strlen(path) - 1] == '\n') //개행 지우기
		path[ft_strlen(path) - 1] = '\0';
	tmp = mlx_xpm_file_to_image(p_all->mlx, path, &img_width, &img_height);
	if (!tmp)
		display_err_msg_and_exit("Invalid image file");

	e_flag = 1;
	if (type == NO && !p_all->map_info.v_texture[NO] && e_flag--)
		p_all->map_info.v_texture[NO] = tmp;
	else if (type == SO && !p_all->map_info.v_texture[SO] && e_flag--)
		p_all->map_info.v_texture[SO] = tmp;
	else if (type == WE && !p_all->map_info.v_texture[WE] && e_flag--)
		p_all->map_info.v_texture[WE] = tmp;
	else if (type == EA && !p_all->map_info.v_texture[EA] && e_flag--)
		p_all->map_info.v_texture[EA] = tmp;
	
	if (e_flag)
		display_err_msg_and_exit("Duplicate Elements");
}

static void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	is_valid_color(char *color, int type, t_all *p_all)
{
	char**	tmp;
	int		rgb[3];
	int		result;
	int		i;

	tmp = ft_split(color, ',');
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3) 
	{
		free_double_pointer(tmp);
		display_err_msg_and_exit("Invalid color information");
	}
	result = 0;
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(tmp[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			display_err_msg_and_exit("Invalid color information");
		result <<= 8;
		result += rgb[i];
		i++;
	}
	if (type == F)
		p_all->map_info.f = result;
	else if (type == C)
		p_all->map_info.c = result;
	free_double_pointer(tmp);
}

static void	is_valid_tile(char *line, t_all *p_all)
{
	int 	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" \n01NSEW", line[i]))
			display_err_msg_and_exit("Invalid map");
		i++;
	}
	p_all->map.dp_map[p_all->map_info.tile_cnt] = line;
	if (p_all->map.col < (ft_strlen(line) - 1))
		p_all->map.col = ft_strlen(line) - 1;
	p_all->map_info.tile_cnt++;
}

void	check_type(char *line, t_all *p_all)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' && (p_all->map_info.tile_cnt == 0 || p_all->map_info.tile_cnt == (int)p_all->map.row))
		return ;
	if (p_all->map_info.info_cnt < 6)
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
		p_all->map_info.info_cnt++;
		return ;
	}
	if (p_all->map_info.info_cnt == 6 && (line[i] == '1' || line[i] == '\n'))
		is_valid_tile(line, p_all);
	else if (p_all->map_info.info_cnt == 6 && line[i] == '\0')
		return ;
	else
		display_err_msg_and_exit("Invalid element in map file");
}
