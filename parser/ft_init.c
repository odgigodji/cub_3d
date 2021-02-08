/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:06:50 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 19:06:51 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_pars(t_all *all)
{
	all->pars.rep_no = 0;
	all->pars.rep_so = 0;
	all->pars.rep_we = 0;
	all->pars.rep_ea = 0;
	all->pars.rep_spr = 0;
	all->pars.rep_re = 0;
	all->pars.rep_floor = 0;
	all->pars.rep_ceiling = 0;
	all->parsed_elem = 0;
	all->amount = 0;
	all->map_source = 0;
	all->spr_num = 0;
	all->map = NULL;
	all->plr->have_player = 0;
	all->flag_line = 0;
}

void	ft_init_direction(t_all *all)
{
	if (all->plr->side == 'E' || all->plr->side == 'W')
	{
		all->plr->dir_y = 0;
		all->plr->plane_x = 0;
		all->plr->dir_x = (all->plr->side == 'E') ? 1 : -1;
		all->plr->plane_y = (all->plr->side == 'E') ? 0.66 : -0.66;
	}
	if (all->plr->side == 'N' || all->plr->side == 'S')
	{
		all->plr->dir_x = 0.001;
		all->plr->plane_y = 0;
		all->plr->dir_y = (all->plr->side == 'N') ? -1 : 1;
		all->plr->plane_x = (all->plr->side == 'N') ? 0.66 : -0.66;
	}
}

void	ft_check_side(t_all *all, int pos_y, int pos_x)
{
	if (all->plr->have_player == 1)
		exit_cube("Player init: duplicate position.");
	if (all->map[pos_y][pos_x] == 'N')
		all->plr->side = 'N';
	if (all->map[pos_y][pos_x] == 'E')
		all->plr->side = 'E';
	if (all->map[pos_y][pos_x] == 'W')
		all->plr->side = 'W';
	if (all->map[pos_y][pos_x] == 'S')
		all->plr->side = 'S';
	all->plr->have_player = 1;
	all->map[pos_y][pos_x] = '0';
}

void	ft_spr_and_plr_pos(t_all *all, int y, int x)
{
	if (ft_strchr("NEWS", all->map[y][x]))
	{
		all->plr->pos_x = (double)x + 0.5;
		all->plr->pos_y = (double)y + 0.5;
		ft_check_side(all, y, x);
	}
	if (all->map[y][x] == '2')
	{
		all->spr[all->spr->pos].x = x + 0.5;
		all->spr[all->spr->pos].y = y + 0.5;
		all->spr->pos++;
	}
}

void	ft_init_player(t_all *all)
{
	t_point pos;

	ft_bzero(&pos, sizeof(t_point));
	while (all->map[pos.y])
	{
		pos.x = 0;
		while (pos.y < all->amount && all->map[pos.y][pos.x])
		{
			ft_spr_and_plr_pos(all, pos.y, pos.x);
			pos.x++;
		}
		pos.y++;
	}
	if (!all->plr->have_player)
		exit_cube("Missing player.");
}
