/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:17:47 by hyko              #+#    #+#             */
/*   Updated: 2022/12/29 20:53:06 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_valid_texture(char *path, int type, t_all *p_all)
{
	int		err_flag;
	void	*tmp;
	int		img_size;

	img_size = TEXTURE_SIZE;
	while (*path == ' ')
		path++;
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	tmp = mlx_xpm_file_to_image(p_all->mlx, path, &img_size, &img_size);
	if (!tmp)
		display_err_msg_and_exit("Invalid image file");
	err_flag = 1;
	if (type == NO && !p_all->map_info.v_texture[NO] && err_flag--)
		p_all->map_info.v_texture[NO] = tmp;
	else if (type == SO && !p_all->map_info.v_texture[SO] && err_flag--)
		p_all->map_info.v_texture[SO] = tmp;
	else if (type == WE && !p_all->map_info.v_texture[WE] && err_flag--)
		p_all->map_info.v_texture[WE] = tmp;
	else if (type == EA && !p_all->map_info.v_texture[EA] && err_flag--)
		p_all->map_info.v_texture[EA] = tmp;
	if (err_flag)
		display_err_msg_and_exit("Duplicate Elements");
}

void	free_double_pointer(char **arr)
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

static int	set_color(char **tmp)
{
	int		rgb[3];
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(tmp[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_double_pointer(tmp);
			display_err_msg_and_exit("Invalid color information");
		}
		result <<= 8;
		result += rgb[i];
		i++;
	}
	return (result);
}

void	is_valid_color(char *color, int type, t_all *p_all)
{
	char	**tmp;
	int		i;
	int		result;

	tmp = ft_split(color, ',');
	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
	{
		free_double_pointer(tmp);
		display_err_msg_and_exit("Invalid color information");
	}
	result = set_color(tmp);
	if (type == F)
		p_all->map_info.f = result;
	else if (type == C)
		p_all->map_info.c = result;
	free_double_pointer(tmp);
}

void	is_valid_tile(char *line, t_all *p_all)
{
	int	i;

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
