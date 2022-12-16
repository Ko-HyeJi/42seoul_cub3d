#include "cub3d.h"

void get_row_col(char *argv, t_all *p_all)
{
	char	*str;

	p_all->map.row = 0;
	p_all->map.col = 0;
	int	fd;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
        printf("%s\n", strerror(errno));
        exit (0);//값 수정
	}
	str = "temp";
	while (str)
	{
		str = get_next_line(fd);
		free(str);
		if (str)
			p_all->map.col = ft_strlen(str);
		p_all->map.row++;
	}
	p_all->map.row--;
	free(str);
	close(fd);
}

void	get_map(char *argv, t_all *p_all)
{
    get_row_col(argv, p_all);
	int	fd;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
        printf("%s\n", strerror(errno));
        exit (0);//값 수정
	}
	p_all->map.dp_map = malloc((p_all->map.row + 1) * sizeof(char *));
	if (p_all->map.dp_map == NULL)
	{
        printf("%s\n", strerror(errno));
        exit (0);//값 수정
	}
    unsigned long long  ull;

    ull = 0;
	while (ull < p_all->map.row)
	{
		p_all->map.dp_map[ull] = get_next_line(fd);
		ull++;
	}
	p_all->map.dp_map[ull] = NULL;
	close(fd);
}

void	init_map(char *argv, t_all *p_all)
{
	get_map(argv, p_all);
	p_all->map.row_tile_size = WINDOW_HEI / p_all->map.row;
	p_all->map.col_tile_size = WINDOW_WID / p_all->map.col;
}
