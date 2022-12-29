#include "cub3d.h"

int ft_loop_hook(t_all *p_all)
{
	update_player(p_all);
	render_map(p_all);
	draw_player(p_all);
	mlx_put_image_to_window(p_all->mlx, p_all->win, p_all->img.img, 0, 0);
	return (0);
}

void	init_mlx(t_all *p_all)
{
	p_all->mlx = mlx_init();
	p_all->win = mlx_new_window(p_all->mlx, WINDOW_WID, WINDOW_HEI, "title");
	p_all->img.img = mlx_new_image(p_all->mlx, WINDOW_WID, WINDOW_HEI);
	p_all->img.data = (int *)mlx_get_data_addr(p_all->img.img, &(p_all->img.bpp), 
										&(p_all->img.size_line), &(p_all->img.endian));
}

void	init_key(t_all *p_all)
{
	p_all->key.up = false;
	p_all->key.down = false;
	p_all->key.left = false;
	p_all->key.right = false;
	p_all->key.left_rotation = false;
	p_all->key.right_rotation = false;
}

void	ft_init(t_all *p_all)
{
	init_player(p_all);
	init_key(p_all);
	init_mlx(p_all);
}

int	mouse(void)
{
	exit(0);
}

void	loop_hook(t_all *p_all)
{
	mlx_hook(p_all->win, X_EVENT_KEY_PRESS, 0, &key_press, p_all);
	mlx_hook(p_all->win, X_EVENT_KEY_RELEASE, 0, &key_release, p_all);
	mlx_hook(p_all->win, X_EVENT_WINDOW_DESTROY, 0, &mouse, 0);
	mlx_loop_hook(p_all->mlx, &ft_loop_hook, p_all);
	mlx_loop(p_all->mlx);
}

int main(int argc, char **argv)
{
	t_all	s_all;

	ft_init(&s_all);
	parse_map(argc, argv, &s_all);
	set_texture_img(&s_all);
	loop_hook(&s_all);
	return (0);
}
