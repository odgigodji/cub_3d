/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:36:36 by namerei           #+#    #+#             */
/*   Updated: 2021/02/07 22:28:35 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_all(char *av1, t_all *all)
{
	ft_parser(av1, all);
	ft_is_correct_map(all);
	ft_is_valid_map(all);
	init_move_key_structure(all);
	ft_spr_num(all);
	if (!(all->spr = (t_spr *)ft_calloc(all->spr_num + 1, sizeof(t_spr))))
		exit_cube("malloc error");
	if (!(all->spr->zbuffer = (double *)ft_calloc(all->width + 1,\
	sizeof(double))))
		exit_cube("malloc error");
	ft_init_player(all);
	ft_init_direction(all);
}

int		main(int ac, char **av)
{
	t_all all;
	t_win win;
	t_plr plr;
	t_ray ray;

	all.win = &win;
	all.plr = &plr;
	all.ray = &ray;
	if (ac == 2 || (ac == 3 && !ft_strcmp(av[2], "--save") && (all.save = 1)))
	{
		ft_init_all(av[1], &all);
		win.mlx = mlx_init();
		win.win = mlx_new_window(win.mlx, all.width, all.height, "cub3D");
		win.img = mlx_new_image(win.mlx, all.width, all.height);
		win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
		init_textures(&all);
		mlx_hook(all.win->win, 2, 1L << 0, key_press, &all);
		mlx_hook(all.win->win, 3, 1L << 0, key_release, &all);
		mlx_hook(all.win->win, 17, 1L << 0, ft_close, &all);
		mlx_loop_hook(all.win->mlx, engine, &all);
		mlx_loop(all.win->mlx);
	}
	else
		exit_cube("Incorrect arguments.");
}
