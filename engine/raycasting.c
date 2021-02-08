/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:56:49 by namerei           #+#    #+#             */
/*   Updated: 2021/02/07 22:28:24 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_dda_was_hit(t_all *all)
{
	while (all->ray->hit == 0)
	{
		if (all->ray->side_dist_x < all->ray->side_dist_y)
		{
			all->ray->side_dist_x += all->ray->delta_dist_x;
			all->ray->map_x += all->ray->step_x;
			all->ray->side = 0;
		}
		else
		{
			all->ray->side_dist_y += all->ray->delta_dist_y;
			all->ray->map_y += all->ray->step_y;
			all->ray->side = 1;
		}
		if (all->map[all->ray->map_y][all->ray->map_x] == '1')
			all->ray->hit = 1;
	}
	if (all->ray->side == 0)
		all->plr->perp_wall_dist = (all->ray->map_x - all->plr->pos_x + \
		(double)(1 - all->ray->step_x) / 2) / all->ray->dir_x;
	else
		all->plr->perp_wall_dist = (all->ray->map_y - all->plr->pos_y + \
		(double)(1 - all->ray->step_y) / 2) / all->ray->dir_y;
}

void	ft_dda_init(t_all *all)
{
	all->ray->hit = 0;
	if (all->ray->dir_x < 0)
	{
		all->ray->step_x = -1;
		all->ray->side_dist_x = (all->plr->pos_x - all->ray->map_x) * \
		all->ray->delta_dist_x;
	}
	else
	{
		all->ray->step_x = 1;
		all->ray->side_dist_x = (all->ray->map_x + 1.0 - all->plr->pos_x) * \
		all->ray->delta_dist_x;
	}
	if (all->ray->dir_y < 0)
	{
		all->ray->step_y = -1;
		all->ray->side_dist_y = (all->plr->pos_y - all->ray->map_y) * \
		all->ray->delta_dist_y;
	}
	else
	{
		all->ray->step_y = 1;
		all->ray->side_dist_y = (all->ray->map_y + 1.0 - all->plr->pos_y) * \
		all->ray->delta_dist_y;
	}
}

void	ft_ray_init(t_all *all)
{
	all->ray->camera_x = (2.0 * all->x / (double)all->width) - 1;
	all->ray->dir_x = all->plr->dir_x + all->plr->plane_x * all->ray->camera_x;
	all->ray->dir_y = all->plr->dir_y + all->plr->plane_y * all->ray->camera_x;
	all->ray->map_x = (int)all->plr->pos_x;
	all->ray->map_y = (int)all->plr->pos_y;
	if (all->ray->dir_y == 0)
		all->ray->delta_dist_x = 0;
	else
		all->ray->delta_dist_x = (all->ray->dir_x == 0) ? 1 : \
		(fabs(1 / all->ray->dir_x));
	if (all->ray->dir_x == 0)
		all->ray->delta_dist_x = 0;
	else
		all->ray->delta_dist_y = (all->ray->dir_y == 0) ? 1 : \
		(fabs(1 / all->ray->dir_y));
}

void	ft_calculate_slice_height(t_all *all)
{
	all->ray->line_height = (int)(all->height / all->plr->perp_wall_dist);
	all->ray->draw_start = -all->ray->line_height / 2 + all->height / 2;
	if (all->ray->draw_start < 0)
		all->ray->draw_start = 0;
	all->ray->draw_end = all->ray->line_height / 2 + all->height / 2;
	if (all->ray->draw_end >= all->height)
		all->ray->draw_end = all->height;
	if (all->ray->side == 0)
		all->tex.wall_x = all->plr->pos_y + (all->plr->perp_wall_dist * \
		all->ray->dir_y);
	else
		all->tex.wall_x = all->plr->pos_x + (all->plr->perp_wall_dist *  \
		all->ray->dir_x);
	all->tex.wall_x -= floor((all->tex.wall_x));
	all->tex.tex_x = (int)(all->tex.wall_x * (double)all->tex.tex_width[0]);
	all->tex.tex_x = all->tex.tex_width[0] - all->tex.tex_x;
	all->tex.step = 1.0 * all->tex.tex_height[0] / all->ray->line_height;
	all->tex.tex_pos = (all->ray->draw_start - ((double)all->height / 2) + \
	(all->ray->line_height / 2)) * all->tex.step;
}

void	ray_casting(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	all->win->img = mlx_new_image(all->win->mlx, all->width, all->height);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp, \
	&all->win->line_l, &all->win->en);
	all->x = 0;
	while (all->x < all->width)
	{
		ft_ray_init(all);
		ft_dda_init(all);
		ft_dda_was_hit(all);
		ft_calculate_slice_height(all);
		draw_line(all);
		all->spr->zbuffer[all->x] = all->plr->perp_wall_dist;
		all->x++;
	}
	if (all->spr_num > 0)
		do_sprites(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	ft_do_screenshoot(all);
}
