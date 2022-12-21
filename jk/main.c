#include "cub3d.h"

int ft_loop(t_all *p_all)//이름 수정할거임
{
	printf("[debug: stop here]\n");	
	update_player(p_all);
	render_map(p_all);
	render_player(p_all);
	draw_ray(p_all);
	mlx_put_image_to_window(p_all->mlx.mlx, p_all->mlx.win, p_all->img.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_all	s_all;

	init_player(&s_all);
	
	s_all.mlx.mlx = mlx_init();
	s_all.mlx.win = mlx_new_window(s_all.mlx.mlx, WINDOW_WID, WINDOW_HEI, "jeeko's cub3d");
	s_all.img.img = mlx_new_image(s_all.mlx.mlx, WINDOW_WID, WINDOW_HEI);
	s_all.img.data = (int *)mlx_get_data_addr(s_all.img.img, &(s_all.img.bpp), 
										&(s_all.img.size_line), &(s_all.img.endian));
	parse_map(argc, argv, &s_all);

	mlx_hook(s_all.mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &s_all);
	mlx_hook(s_all.mlx.win, X_EVENT_KEY_RELEASE, 0, &key_release, &s_all);
	mlx_loop_hook(s_all.mlx.mlx, &ft_loop, &s_all);
	mlx_loop(s_all.mlx.mlx);

	return (0);
}
