/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:44:30 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 21:44:32 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ft_draw_east_west_tex(t_all *all, int color[5], int y)
{
	if (all->ray->step_x > 0)
	{
		color[0] = (int)ft_texel_color(&all->tex, all->tex.tex_x,\
		ft_spr_tex_y(all, &all->tex), 0);
		my_mlx_pixel_put(all->win, all->x, y, color[0]);
	}
	else
	{
		color[1] = (int)ft_texel_color(&all->tex, all->tex.tex_x,\
		ft_spr_tex_y(all, &all->tex), 1);
		my_mlx_pixel_put(all->win, all->x, y, color[1]);
	}
}

void	ft_draw_south_north_tex(t_all *all, int color[5], int y)
{
	if (all->ray->step_y > 0)
	{
		color[2] = (int)ft_texel_color(&all->tex, all->tex.tex_x,\
		ft_spr_tex_y(all, &all->tex), 2);
		my_mlx_pixel_put(all->win, all->x, y, color[2]);
	}
	else
	{
		color[3] = (int)ft_texel_color(&all->tex, all->tex.tex_x,\
		ft_spr_tex_y(all, &all->tex), 3);
		my_mlx_pixel_put(all->win, all->x, y, color[3]);
	}
}

void	draw_line(t_all *all)
{
	int y;
	int wall_tex_color[5];

	y = 0;
	while (y < all->height)
	{
		if (y < all->ray->draw_start)
			my_mlx_pixel_put(all->win, all->x, y, \
			all->tex.floor_or_ceiling_color[1]);
		else if (y >= all->ray->draw_start && y <= all->ray->draw_end)
		{
			if (all->ray->side == 0)
				ft_draw_east_west_tex(all, wall_tex_color, y);
			else
				ft_draw_south_north_tex(all, wall_tex_color, y);
		}
		else if (y > all->ray->draw_end)
			my_mlx_pixel_put(all->win, all->x, y,\
			all->tex.floor_or_ceiling_color[0]);
		y++;
	}
}

void	draw_y_sprite(t_all *all)
{
	all->spr->d = all->spr->y_ * 256 - all->height * 128 + \
	all->spr->sprite_height * 128;
	all->spr->tex_y = ((all->spr->d * all->tex.tex_height[1])\
	/ all->spr->sprite_height) / 256;
	all->spr->color = (int)ft_texel_color(&all->tex,\
	all->spr->tex_x, all->spr->tex_y, 4);
	if (all->spr->color != 0x000000)
		my_mlx_pixel_put(all->win, all->spr->stripe,\
					all->spr->y_, all->spr->color);
}
