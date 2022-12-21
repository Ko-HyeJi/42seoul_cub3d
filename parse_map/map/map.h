#ifndef MAP_H
# define MAP_H

#include "../get_next_line/get_next_line.h"
#include "cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>

typedef	enum	e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	TILE,
}				t_type;

void	is_cub_file(const char* filename);
void	check_type(char* line, t_all *all);
void	display_err_msg_and_exit(const char* err_msg);

#endif
