/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:20:05 by hyko              #+#    #+#             */
/*   Updated: 2022/12/29 18:27:24 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_err_msg_and_exit(const char *err_msg)
{
	// free
	printf("ERROR\n");
	printf("%s\n", err_msg);
	exit (1);
}

static void	is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		display_err_msg_and_exit("Invalid file extension");
	if (ft_strncmp(&filename[len - 4], ".cub", 4))
		display_err_msg_and_exit("Invalid file extension");
}

static void	get_row(char *filename, t_all *p_all)
{
	char	*tmp;
	int		fd;
	int		i;
	int		map_flag;

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
				map_flag = 1;
			if (map_flag && (tmp[i] == '1' || tmp[i] == '\n'))
				p_all->map.row++;
		}
	}
	free(tmp);
	close(fd);
}

static void	fill_map(t_all *p_all)
{
	unsigned long long	i;
	unsigned long long	j;
	char				*tmp;

	i = 0;
	while (i < p_all->map.row)
	{
		tmp = p_all->map.dp_map[i];
		p_all->map.dp_map[i] = malloc(sizeof(char) * (p_all->map.col + 1));
		j = 0;
		while (tmp[j] != '\n')
		{
			p_all->map.dp_map[i][j] = tmp[j];
			j++;
		}
		while (j < p_all->map.col)
		{
			p_all->map.dp_map[i][j] = ' ';
			j++;
		}
		p_all->map.dp_map[i][j] = '\0';
		free(tmp);
		i++;
	}
	p_all->map.dp_map[p_all->map.row] = NULL;
}

void	parse_map(int argc, char **argv, t_all *p_all)
{
	int		fd;
	char	*line;

	if (argc != 2)
		display_err_msg_and_exit("Invalid argument");
	is_cub_file(argv[1]);
	init_map(p_all);
	get_row(argv[1], p_all);
	init_map_info(p_all);
	fd = open(argv[1], O_RDONLY);
	line = " ";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			check_type(line, p_all);
	}
	free(line);
	close(fd);
	fill_map(p_all);
	is_vaild_map(p_all);
	p_all->map.row_tile_size = WINDOW_HEI / p_all->map.row;
	p_all->map.col_tile_size = WINDOW_WID / p_all->map.col;
}
