/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:16:08 by hyko              #+#    #+#             */
/*   Updated: 2022/12/31 16:35:11 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_texture(int *texture_img, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			texture_img[(TEXTURE_SIZE * y) + x]
				= img->data[(TEXTURE_SIZE * y) + x];
			x++;
		}
		y++;
	}
}

static int	*load_image(t_all *p_all, int dir)
{
	t_img	img;
	int		*texture_img;

	img.img = p_all->map_info.v_texture[dir];
	img.data = (int *)mlx_get_data_addr
		(img.img, &img.bpp, &img.size_line, &img.endian);
	if (!img.data)
		display_err_msg_and_exit("mlx image_data error");
	texture_img = (int *)malloc(sizeof(int) * (TEXTURE_SIZE * TEXTURE_SIZE));
	if (!texture_img)
		display_err_msg_and_exit("Malloc Failed");
	copy_texture(texture_img, &img);
	mlx_destroy_image(p_all->mlx, img.img);
	return (texture_img);
}

void	set_texture_img(t_all *p_all)
{
	p_all->map_info.i_texture[NO] = load_image(p_all, NO);
	p_all->map_info.i_texture[SO] = load_image(p_all, SO);
	p_all->map_info.i_texture[WE] = load_image(p_all, WE);
	p_all->map_info.i_texture[EA] = load_image(p_all, EA);
}
