#include "cub3d.h"

static void	set_texture_buffer(int *texture_img, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < TEXTURE_HEIGHT)
	{
		x = 0;
		while (x < TEXTURE_WIDTH)
		{
			texture_img[(TEXTURE_WIDTH * y) + x] = img->data[(TEXTURE_WIDTH * y) + x];
			x++;
		}
		y++;
	}
}

static int	*load_image(t_all* all, int dir)
{
	t_img	img;
	int		*texture_img;

	img.img = all->map_info.v_texture[dir];
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	// if (!img.data || img.bpp != 32 || img.endian != 0)
	// 	display_err_msg_and_exit("mlx image_data error");
	if (!img.data)
		display_err_msg_and_exit("mlx image_data error");
	texture_img = (int *)malloc(sizeof(int) * (TEXTURE_HEIGHT * TEXTURE_WIDTH));
	if (!texture_img)
		display_err_msg_and_exit("texture_img : malloc error");
	set_texture_buffer(texture_img, &img);
	mlx_destroy_image(all->mlx, img.img);
	return (texture_img);
}

void	set_texture_img(t_all* all)
{
	all->map_info.i_texture[NO] = load_image(all, NO);
	all->map_info.i_texture[SO] = load_image(all, SO);
	all->map_info.i_texture[WE] = load_image(all, WE);
	all->map_info.i_texture[EA] = load_image(all, EA);
}
