#include "cub3d.h"

void	is_cub_file(const char* filename)
{
	size_t len = ft_strlen(filename);
	if (len < 5)
		display_err_msg_and_exit("Invalid file extension");
	if (ft_strncmp(&filename[len - 4], ".cub", 4))
		display_err_msg_and_exit("Invalid file extension");
}

static void	is_valid_texture(char* path, int type, t_all* all)
{
	int img_width = 64; //나중에 헤더에 정의
	int img_height = 64;

	int e_flag;
	void* tmp;

	while(*path == ' ')
		path++;
	if (path[ft_strlen(path) - 1] == '\n') //개행 지우기
		path[ft_strlen(path) - 1] = '\0';
	tmp = mlx_xpm_file_to_image(all->mlx, path, &img_width, &img_height);
	if (!tmp)
		display_err_msg_and_exit("Invalid image file");

	e_flag = 1;
	if (type == NO && !all->map_info.v_texture[NO] && e_flag--)
		all->map_info.v_texture[NO] = tmp;
	else if (type == SO && !all->map_info.v_texture[SO] && e_flag--)
		all->map_info.v_texture[SO] = tmp;
	else if (type == WE && !all->map_info.v_texture[WE] && e_flag--)
		all->map_info.v_texture[WE] = tmp;
	else if (type == EA && !all->map_info.v_texture[EA] && e_flag--)
		all->map_info.v_texture[EA] = tmp;
	
	if (e_flag)
		display_err_msg_and_exit("Duplicate Elements");
}

static void	free_double_pointer(char** arr)
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

static void	is_valid_color(char* color, int type, t_all* all)
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
		all->map_info.f = result;
	else if (type == C)
		all->map_info.c = result;
	free_double_pointer(tmp);
}

static void	is_valid_tile(char* line, t_all* all)
{
	int 	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" \n01NSEW", line[i]))
			display_err_msg_and_exit("Invalid map");
		i++;
	}
	all->map.dp_map[all->map_info.tile_cnt] = line;
	if (all->map.col < (ft_strlen(line) - 1))
		all->map.col = ft_strlen(line) - 1;
	all->map_info.tile_cnt++;
}

void	check_type(char* line, t_all *all)
{
	while (*line == ' ')
		line++;
	if (line[0] == '\n' && (all->map_info.tile_cnt == 0 || all->map_info.tile_cnt == (int)all->map.row))
		return ;
	if (all->map_info.info_cnt < 6)
	{
		if (line[0] == 'N' && line[1] == 'O')
			is_valid_texture(line += 2, NO, all);
		else if (line[0] == 'S' && line[1] == 'O') 
			is_valid_texture(line += 2, SO, all);
		else if (line[0] == 'W' && line[1] == 'E')
			is_valid_texture(line += 2, WE, all);
		else if (line[0] == 'E' && line[1] == 'A')
			is_valid_texture(line += 2, EA, all);
		else if (line[0] == 'F')
			is_valid_color(line += 1, F, all);
		else if (line[0] == 'C')
			is_valid_color(line += 1, C, all);
		else
			display_err_msg_and_exit("Invalid element in map file");		
		all->map_info.info_cnt++;
		return ;
	}
	if (all->map_info.info_cnt == 6 && (line[0] == '1' || line[0] == '\n'))
		is_valid_tile(line, all);
	else if (all->map_info.info_cnt == 6 && line[0] == '\0')
		return ;
	else
		display_err_msg_and_exit("Invalid element in map file");
}
