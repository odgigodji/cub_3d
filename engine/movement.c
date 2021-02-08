/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:47:26 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 21:47:28 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up_or_down(t_all *all)
{
	if (all->move.up == 1)
	{
		if (all->map[(int)all->plr->pos_y][(int)(all->plr->pos_x + \
		all->plr->dir_x * all->plr->move_speed)] == '0')
			all->plr->pos_x += all->plr->dir_x * all->plr->move_speed;
		if (all->map[(int)(all->plr->pos_y + all->plr->dir_y * \
		all->plr->move_speed)][(int)all->plr->pos_x] == '0')
			all->plr->pos_y += all->plr->dir_y * all->plr->move_speed;
	}
	if (all->move.down == 1)
	{
		if (all->map[(int)all->plr->pos_y][(int)(all->plr->pos_x - \
		all->plr->dir_x * all->plr->move_speed)] == '0')
			all->plr->pos_x -= all->plr->dir_x * all->plr->move_speed;
		if (all->map[(int)(all->plr->pos_y - all->plr->dir_y * \
		all->plr->move_speed)][(int)all->plr->pos_x] == '0')
			all->plr->pos_y -= all->plr->dir_y * all->plr->move_speed;
	}
}

void	move_left_or_right(t_all *all)
{
	if (all->move.left == 1)
	{
		if (all->map[(int)all->plr->pos_y][(int)(all->plr->pos_x - \
		(all->plr->plane_x * all->plr->move_speed))] == '0')
			all->plr->pos_x -= (all->plr->plane_x * all->plr->move_speed);
		if (all->map[(int)(all->plr->pos_y - (all->plr->plane_y * \
		all->plr->move_speed))][(int)all->plr->pos_x] == '0')
			all->plr->pos_y -= (all->plr->plane_y * all->plr->move_speed);
	}
	if (all->move.right == 1)
	{
		if (all->map[(int)all->plr->pos_y][(int)(all->plr->pos_x +\
		(all->plr->plane_x * all->plr->move_speed))] == '0')
			all->plr->pos_x += (all->plr->plane_x * all->plr->move_speed);
		if (all->map[(int)(all->plr->pos_y + (all->plr->plane_y *\
		all->plr->move_speed))][(int)all->plr->pos_x] == '0')
			all->plr->pos_y += (all->plr->plane_y * all->plr->move_speed);
	}
}

void	turn_left(t_all *all)
{
	all->move.old_dir_x = all->plr->dir_x;
	all->plr->dir_x = all->plr->dir_x * cos(all->plr->rot_speed) -\
		all->plr->dir_y * sin(all->plr->rot_speed);
	all->plr->dir_y = all->move.old_dir_x * sin(all->plr->rot_speed) + \
	all->plr->dir_y * cos(all->plr->rot_speed);
	all->move.old_plane_x = all->plr->plane_x;
	all->plr->plane_x = all->plr->plane_x * cos(all->plr->rot_speed) - \
		all->plr->plane_y * sin(all->plr->rot_speed);
	all->plr->plane_y = all->move.old_plane_x * sin(all->plr->rot_speed) + \
		all->plr->plane_y * cos(all->plr->rot_speed);
}

void	turn_left_or_right(t_all *all)
{
	if (all->move.turn_l == 1)
	{
		all->move.old_dir_x = all->plr->dir_x;
		all->plr->dir_x = all->plr->dir_x * cos(-all->plr->rot_speed) - \
		all->plr->dir_y * sin(-all->plr->rot_speed);
		all->plr->dir_y = all->move.old_dir_x * sin(-all->plr->rot_speed)\
		+ all->plr->dir_y * cos(-all->plr->rot_speed);
		all->move.old_plane_x = all->plr->plane_x;
		all->plr->plane_x = all->plr->plane_x * cos(-all->plr->rot_speed) -\
		all->plr->plane_y * sin(-all->plr->rot_speed);
		all->plr->plane_y = all->move.old_plane_x * sin(-all->plr->rot_speed) +\
		all->plr->plane_y * cos(-all->plr->rot_speed);
	}
	if (all->move.turn_r == 1)
	{
		turn_left(all);
	}
}

int		engine(t_all *all)
{
	all->plr->move_speed = 0.1 * (double)MOVE_SPEED;
	all->plr->rot_speed = 0.08 * (double)ROTATE_SPEED;
	if (all->move.shift == 1)
		all->plr->move_speed *= 4;
	move_up_or_down(all);
	move_left_or_right(all);
	turn_left_or_right(all);
	ray_casting(all);
	mlx_string_put(all->win->mlx, all->win->win, all->width / 2,\
	all->height / 2 - 9.5, 0xd0d0ce, "+");
	return (0);
}
