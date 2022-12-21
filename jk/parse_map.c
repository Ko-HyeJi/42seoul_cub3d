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
	for (int i = 0; i < (int)all->map.row; i++)
		printf("%s", all->map.dp_map[i]);
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
	all->map.dp_map = (char**)malloc(sizeof(char*) * all->map.row);
	all->map_info.info_cnt = 0;
	all->map_info.tile_cnt = 0;
}

static void	is_vaild_map(char** map, int row)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (i < row)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				player++;
			if (!ft_strchr(" \t\n1", map[i][j]))
			{
				if (ft_strchr(" \t\n", map[i - 1][j])
					|| ft_strchr(" \t\n", map[i + 1][j])
					|| ft_strchr(" \t\n", map[i][j - 1])
					|| ft_strchr(" \t\n", map[i][j + 1]))
				{
					printf("[%d][%d]\n", i, j);	
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

	is_vaild_map(all->map.dp_map, all->map.row);

	/* debug */
	display_map_elements(all);
}
