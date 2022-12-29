#include "cub3d.h"

void init_img_data(t_all* p_all) 
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEI)
	{
		x = 0;
		while (x < WINDOW_WID)
		{
			p_all->img.data[WINDOW_WID * y + x] = 0;
			x++;
		}
		y++;
	}
}

void init_player(t_all *p_all)
{
	p_all->player.x = WINDOW_WID / 2;
	p_all->player.y = WINDOW_HEI / 2;
	p_all->player.rotation_angle = 0;// E일 경우.오른쪽을 봄
	p_all->player.walk_speed = 1;
	p_all->player.turn_speed = 2 * (PI / 180);//?
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

void	init_mlx(t_all *p_all)
{
	p_all->mlx = mlx_init();
	p_all->win = mlx_new_window(p_all->mlx, WINDOW_WID, WINDOW_HEI, "title");
	p_all->img.img = mlx_new_image(p_all->mlx, WINDOW_WID, WINDOW_HEI);
	p_all->img.data = (int *)mlx_get_data_addr(p_all->img.img, &(p_all->img.bpp), 
										&(p_all->img.size_line), &(p_all->img.endian));
}

void	ft_init(t_all *p_all)
{
	init_player(p_all);
	init_key(p_all);
	init_mlx(p_all);
}
