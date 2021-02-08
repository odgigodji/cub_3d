/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:39:13 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 21:39:15 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_protect_tex_images(t_all *all)
{
	if (!all->tex.img[0] || !all->tex.img[1] || !all->tex.img[2] || \
	!all->tex.img[3] || !all->tex.img[4])
		exit_cube("Incorrect texture file.");
	free(all->tex.tex_path[0]);
	free(all->tex.tex_path[1]);
	free(all->tex.tex_path[2]);
	free(all->tex.tex_path[3]);
	free(all->tex.tex_path[4]);
}

void			init_textures(t_all *all)
{
	all->tex.img[0] = mlx_xpm_file_to_image(all->win->mlx, \
	all->tex.tex_path[0], &all->tex.tex_width[0], &all->tex.tex_height[0]);
	all->tex.img[1] = mlx_xpm_file_to_image(all->win->mlx, \
	all->tex.tex_path[1], &all->tex.tex_width[0], &all->tex.tex_height[0]);
	all->tex.img[2] = mlx_xpm_file_to_image(all->win->mlx, \
	all->tex.tex_path[2], &all->tex.tex_width[0], &all->tex.tex_height[0]);
	all->tex.img[3] = mlx_xpm_file_to_image(all->win->mlx, \
	all->tex.tex_path[3], &all->tex.tex_width[0], &all->tex.tex_height[0]);
	all->tex.img[4] = mlx_xpm_file_to_image(all->win->mlx, \
	all->tex.tex_path[4], &all->tex.tex_width[1], &all->tex.tex_height[1]);
	ft_protect_tex_images(all);
	all->tex.addr[0] = mlx_get_data_addr(all->tex.img[0], &all->tex.bpp[0],\
	&all->tex.line_l[0], &all->tex.en[0]);
	all->tex.addr[1] = mlx_get_data_addr(all->tex.img[1], &all->tex.bpp[1],\
	&all->tex.line_l[1], &all->tex.en[1]);
	all->tex.addr[2] = mlx_get_data_addr(all->tex.img[2], &all->tex.bpp[2],\
	&all->tex.line_l[2], &all->tex.en[2]);
	all->tex.addr[3] = mlx_get_data_addr(all->tex.img[3], &all->tex.bpp[3],\
	&all->tex.line_l[3], &all->tex.en[3]);
	all->tex.addr[4] = mlx_get_data_addr(all->tex.img[4], &all->tex.bpp[4],\
	&all->tex.line_l[4], &all->tex.en[4]);
}

int				ft_spr_tex_y(t_all *all, t_tex *tex)
{
	all->tex.tex_y = (int)(all->tex.tex_pos) & (tex->tex_height[0] - 1);
	all->tex.tex_pos += all->tex.step;
	return (all->tex.tex_y);
}

unsigned int	ft_texel_color(t_tex *tex, int x, int y, int i)
{
	char			*addr;
	unsigned int	color;

	addr = tex->addr[i] + (y * tex->line_l[i] + x * (tex->bpp[i] / 8));
	color = *(unsigned int *)addr;
	return (color);
}

void			sort_sprites(t_all *all)
{
	int		i;
	double	swap;

	i = 0;
	while (i < all->spr_num)
	{
		if (all->spr[i].distance < all->spr[i + 1].distance)
		{
			swap = all->spr[i].distance;
			all->spr[i].distance = all->spr[i + 1].distance;
			all->spr[i + 1].distance = swap;
			swap = all->spr[(int)all->spr[i].order].x;
			all->spr[(int)all->spr[i].order].x = \
			all->spr[(int)all->spr[i + 1].order].x;
			all->spr[(int)all->spr[i + 1].order].x = swap;
			swap = all->spr[(int)all->spr[i].order].y;
			all->spr[(int)all->spr[i].order].y = \
			all->spr[(int)all->spr[i + 1].order].y;
			all->spr[(int)all->spr[i + 1].order].y = swap;
			i = 0;
		}
		else
			i++;
	}
}
