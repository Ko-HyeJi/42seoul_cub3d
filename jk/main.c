#include "cub3d.h"

int main(int argc, char **argv)
{
	t_all	s_all;

	ft_init(&s_all);
	parse_map(argc, argv, &s_all);
	set_texture_img(&s_all);
	loop_hook(&s_all);
	return (0);
}
