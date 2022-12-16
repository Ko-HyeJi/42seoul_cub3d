#include "cub3d.h"

int ft_loop(t_all *p_all)
{
	update_player(p_all);
	render_map(p_all);
	render_player(p_all);
	draw_ray(p_all);
	mlx_put_image_to_window(p_all->mlx.mlx, p_all->mlx.win, p_all->img.img, 0, 0);
	
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("'2' arguments needed.\n");
		return (0);
	}//메시지, 반환값 수정!
	t_all	sall;
	init_map(argv[1], &sall);
	init_player(&sall);
	
	sall.mlx.mlx = mlx_init();
	sall.mlx.win = mlx_new_window(sall.mlx.mlx, WINDOW_WID, WINDOW_HEI, "title");
	sall.img.img = mlx_new_image(sall.mlx.mlx, WINDOW_WID, WINDOW_HEI);

	mlx_hook(sall.mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &sall);
	mlx_hook(sall.mlx.win, X_EVENT_KEY_RELEASE, 0, &key_release, &sall);
	mlx_loop_hook(sall.mlx.mlx, &ft_loop, &sall);
	mlx_loop(sall.mlx.mlx);

	return (0);
}