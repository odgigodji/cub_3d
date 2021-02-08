/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:00:40 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 21:00:42 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_move_key_structure(t_all *all)
{
	all->move.up = 0;
	all->move.down = 0;
	all->move.right = 0;
	all->move.left = 0;
	all->move.turn_l = 0;
	all->move.turn_r = 0;
	all->move.shift = 0;
}

int		key_press(int key, t_all *all)
{
	if (key == W || key == UP_KEY)
		all->move.up = 1;
	if (key == S || key == DOWN_KEY)
		all->move.down = 1;
	if (key == A)
		all->move.left = 1;
	if (key == D)
		all->move.right = 1;
	if (key == LEFT_KEY || key == 12)
		all->move.turn_l = 1;
	if (key == RIGHT_KEY || key == 14)
		all->move.turn_r = 1;
	if (key == SHIFT)
		all->move.shift = 1;
	if (key == ESC)
	{
		ft_putendl("\033[35mEXIT CUBE....\033[0m");
		exit(0);
	}
	return (0);
}

int		key_release(int key, t_all *all)
{
	if (key == W || key == UP_KEY)
		all->move.up = 0;
	if (key == S || key == DOWN_KEY)
		all->move.down = 0;
	if (key == A)
		all->move.left = 0;
	if (key == D)
		all->move.right = 0;
	if (key == LEFT_KEY || key == Q)
		all->move.turn_l = 0;
	if (key == RIGHT_KEY || key == E)
		all->move.turn_r = 0;
	if (key == SHIFT)
		all->move.shift = 0;
	return (0);
}

int		ft_close(int key, t_all *all)
{
	(void)key;
	(void)all;
	ft_putendl("\033[35mEXIT CUBE....\033[0m");
	exit(0);
}
