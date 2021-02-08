/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:02:25 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 21:02:26 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_spr_dist(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->spr_num)
	{
		all->spr[i].order = i;
		all->spr[i].distance = ((all->plr->pos_x - all->spr[i].x) * \
		(all->plr->pos_x - all->spr[i].x) + (all->plr->pos_y - all->spr[i].y)\
		* (all->plr->pos_y - all->spr[i].y));
	}
}

void	calculate_sprites(t_all *all, int i)
{
	double sprite_x;
	double sprite_y;
	double inv_dev;

	sprite_x = all->spr[(int)all->spr[i].order].x - all->plr->pos_x;
	sprite_y = all->spr[(int)all->spr[i].order].y - all->plr->pos_y;
	inv_dev = 1.0 / (all->plr->plane_x * all->plr->dir_y\
	- all->plr->dir_x * all->plr->plane_y);
	all->spr->transform_x = inv_dev * (all->plr->dir_y * sprite_x\
	- all->plr->dir_x * sprite_y);
	all->spr->transform_y = inv_dev * (-all->plr->plane_y * sprite_x\
	+ all->plr->plane_x * sprite_y);
	all->spr->sprite_sscreen_x = (int)((all->width / 2)\
	* (1 + all->spr->transform_x / all->spr->transform_y));
	all->spr->sprite_height = (int)fabs(all->height / (all->spr->transform_y));
}

void	calculate_height_stripe(t_all *all)
{
	int draw_start_x;

	all->spr->draw_start_y = -all->spr->sprite_height / 2 + all->height / 2;
	if (all->spr->draw_start_y < 0)
		all->spr->draw_start_y = 0;
	all->spr->draw_end_y = all->spr->sprite_height / 2 + all->height / 2;
	if (all->spr->draw_end_y >= all->height)
		all->spr->draw_end_y = all->height - 1;
	all->spr->sprite_width = (int)fabs((all->width / (all->spr->transform_y)));
	draw_start_x = -all->spr->sprite_width / 2 + all->spr->sprite_sscreen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	all->spr->draw_end_x = all->spr->sprite_width / 2\
	+ all->spr->sprite_sscreen_x;
	if (all->spr->draw_end_x >= all->width)
		all->spr->draw_end_x = all->width - 1;
	all->spr->stripe = draw_start_x;
}

void	drawing_stripe(t_all *all)
{
	while (all->spr->stripe < all->spr->draw_end_x)
	{
		all->spr->tex_x = (int)(256 * ((all->spr->stripe - \
		(-all->spr->sprite_width / 2 + all->spr->sprite_sscreen_x)) * \
		all->tex.tex_width[1] / all->spr->sprite_width) / 256);
		if (all->spr->transform_y > 0 && all->spr->stripe > 0 && \
		all->spr->stripe < all->width && all->spr->transform_y < \
		all->spr->zbuffer[all->spr->stripe])
		{
			all->spr->y_ = all->spr->draw_start_y;
			while (all->spr->y_ < all->spr->draw_end_y)
			{
				draw_y_sprite(all);
				all->spr->y_++;
			}
		}
		all->spr->stripe++;
	}
}

void	do_sprites(t_all *all)
{
	int i;

	i = 0;
	ft_init_spr_dist(all);
	while (i < all->spr_num)
	{
		calculate_sprites(all, i);
		sort_sprites(all);
		calculate_height_stripe(all);
		drawing_stripe(all);
		i++;
	}
}
