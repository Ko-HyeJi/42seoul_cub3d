#include "cub3d.h"

static void display_map_elements(t_all* all)
{
	printf("texture NO: %p\n", all->map_info.no);
	printf("texture SO: %p\n", all->map_info.so);
	printf("texture WE: %p\n", all->map_info.we);
	printf("texture EA: %p\n", all->map_info.ea);
	printf("\n");
	printf("color F: %x\n", all->map_info.f);
	printf("color C: %x\n", all->map_info.c);
	printf("\n");
	printf("map\n row:%llu col:%llu\n", all->map.row, all->map.col);
	// for (int i = 0; i < (int)all->map.row; i++)
	// 	printf("%s", all->map.dp_map[i]);
	for (int i = 0; all->map.dp_map[i]; i++) {
		for (int j = 0; all->map.dp_map[i][j]; j++)
			printf("[%c] ", all->map.dp_map[i][j]);
		printf("\n");
	}
}

void	display_err_msg_and_exit(const char* err_msg)
{
	// free
	printf("ERROR\n");
	printf("%s\n", err_msg);
	exit (1);
}

void	get_row(char* filename, t_all* all)
{
	char	*tmp;
	int		fd;
	int		i;

	all->map.row = 0;
	all->map.col = 0;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		display_err_msg_and_exit("Invalid File");
	tmp = " ";
	while (tmp)
	{
		i = 0;
		tmp = get_next_line(fd);
		if (tmp)
		{
			while (tmp[i] == ' ')
				i++;
			if (tmp[i] == '1')
				all->map.row++; 
		}
		free(tmp);
	}
	close(fd);
}

static void	init_map_info(t_all* all)
{
	all->map_info.no = 0;
	all->map_info.so = 0;
	all->map_info.we = 0;
	all->map_info.ea = 0;
	all->map_info.f = 0;
	all->map_info.c = 0;
	all->map.dp_map = (char**)malloc(sizeof(char*) * (all->map.row + 1));
	all->map_info.info_cnt = 0;
	all->map_info.tile_cnt = 0;
}

static void	set_player_location_and_direction(t_all* all, unsigned long long i, unsigned long long j)
{
	// printf("bf player location: %f %f\n", all->player.x, all->player.y);
	all->player.x = (double)(WINDOW_WID / all->map.col) * ((double)(j) + 0.5);
	all->player.y = (double)(WINDOW_HEI / all->map.row) * ((double)(i) + 0.5);
	// printf("af player location: %f %f\n", all->player.x, all->player.y);
	
	// printf("bf player direction: %f\n", all->player.rotation_angle);
	//각도 보정이 필요...
	if (all->map.dp_map[i][j] == 'N')
		all->player.rotation_angle = 270;
	else if (all->map.dp_map[i][j] == 'S')
		all->player.rotation_angle = 90;
	else if (all->map.dp_map[i][j] == 'E')
		all->player.rotation_angle = 0;
	else if (all->map.dp_map[i][j] == 'W')
		all->player.rotation_angle = 180;
	// printf("af player direction: %f\n", all->player.rotation_angle);
}

static void	check_border(char** map, int row, int col)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == row - 1 || j == 0 || j == col - 1) && ft_strchr("0NSEW", map[i][j]))
				display_err_msg_and_exit("Invalid Map");
			j++;
		}
		i++;
	}
}

static void	is_vaild_map(t_all* all)
{
	unsigned long long	i;
	unsigned long long	j;
	unsigned long long	player;

	i = 0;
	j = 0;
	player = 0;
	while (i < all->map.row)
	{
		j = 0;
		while (all->map.dp_map[i][j])
		{
			if (ft_strchr("NSEW", all->map.dp_map[i][j])) {
				set_player_location_and_direction(all, i, j);
				player++;
			}
			check_border(all->map.dp_map, all->map.row, all->map.col);
			if (ft_strchr("0NSEW", all->map.dp_map[i][j]))
			{
				if (ft_strchr(" \n", all->map.dp_map[i - 1][j])
					|| ft_strchr(" \n", all->map.dp_map[i + 1][j])
					|| ft_strchr(" \n", all->map.dp_map[i][j - 1])
					|| ft_strchr(" \n", all->map.dp_map[i][j + 1]))
				{
					printf("[%llu][%llu]\n", i, j);	
					display_err_msg_and_exit("Invalid Map");
				}
			}
			j++;
		}
		i++;
	}
	if (player != 1)
		display_err_msg_and_exit("Invalid Player");
}

static void	fill_map(t_all* all)
{
	unsigned long long	i;
	unsigned long long	j;
	char* tmp;

	i = 0;
	while (i < all->map.row)
	{
		tmp = all->map.dp_map[i];
		all->map.dp_map[i] = (char*)malloc(sizeof(char) * (all->map.col + 1));
		j = 0;
		while (tmp[j] != '\n')
		{
			all->map.dp_map[i][j] = tmp[j];
			j++;
		}
		while (j < all->map.col)
		{
			all->map.dp_map[i][j] = ' ';
			j++;
		}
		all->map.dp_map[i][j] = '\0';
		free(tmp);
		i++;
	}
	all->map.dp_map[all->map.row] = NULL;
}

void	parse_map(int argc, char** argv, t_all* all)
{
	int		fd;
	char*	line;

	if (argc != 2)
		display_err_msg_and_exit("Invalid argument");
	is_cub_file(argv[1]);
	get_row(argv[1], all);
	init_map_info(all);

	fd = open(argv[1], O_RDONLY);
	line = " ";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			check_type(line, all);
	}
	free(line);
	close(fd);

	fill_map(all);
	is_vaild_map(all);
	
	all->map.row_tile_size = WINDOW_HEI / all->map.row;//타일 사이즈 설정해주고
	all->map.col_tile_size = WINDOW_WID / all->map.col;

	/* debug */
	display_map_elements(all);
}
