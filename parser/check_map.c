/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:50:21 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 18:50:23 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_parsed_elem(t_all *all)
{
	if (all->parsed_elem != 8 || all->pars.rep_ea != 1 \
	|| all->pars.rep_we != 1 || all->pars.rep_so != 1 || all->pars.rep_no != 1 \
	|| all->pars.rep_spr != 1 || all->pars.rep_floor != 1 \
	|| all->pars.rep_ceiling != 1)
		exit_cube("Incorrect numbers of element.");
}

void	ft_check_lines(int i, t_all *all)
{
	int j;

	j = 0;
	while (i <= all->map_source && j < (int)ft_strlen(all->map[i]))
	{
		if (!ft_strchr("1 ", all->map[i][j]))
			exit_cube("Invalid map.");
		j++;
	}
	j = 0;
	while (i > all->map_source && i < all->map_end && \
	j < (int)ft_strlen(all->map[i]))
	{
		if (!ft_strchr("NEWS120 ", all->map[i][j]))
			exit_cube("Invalid map. Incorrect line.");
		j++;
	}
	j = 0;
	while (i >= all->map_end && j < (int)ft_strlen(all->map[i]))
	{
		if (!ft_strchr("1 ", all->map[i][j]))
			exit_cube("Invalid map. Incorrect last line.");
		j++;
	}
}

void	ft_is_correct_map(t_all *all)
{
	int i;

	i = 0;
	while (i <= all->amount)
	{
		ft_check_lines(i, all);
		i++;
	}
}

void	ft_is_valid_lines(t_all *all, int i, int j)
{
	if ((all->map[all->map_source][j] == ' ' \
			&& all->map[all->map_source + 1][j + 1]) \
			&& !ft_strchr(" 1", all->map[all->map_source + 1][j + 1]))
		exit_cube("invalid map - top.");
	if ((all->map[i][j] == ' ' \
			&& all->map[i][j + 1] && !ft_strchr(" 1", all->map[i][j + 1]))\
			|| (all->map[i][j] == ' ' && (j != 0) \
			&& !ft_strchr(" 1", all->map[i][j - 1])))
		exit_cube("invalid map");
	if ((all->map[i][j] == ' ' && (i + 1) < all->amount \
			&& !ft_strchr(" 1", all->map[i + 1][j])) \
			|| (all->map[i][j] == ' ' && (i - 1) > all->map_source \
			&& !ft_strchr(" 1", all->map[i - 1][j])))
		exit_cube("invalid map");
	if ((all->map[all->map_end][j] == ' ' \
			&& !ft_strchr(" 1", all->map[all->map_end - 1][j])))
		exit_cube("invalid map - last line.");
}

void	ft_is_valid_map(t_all *all)
{
	int i;
	int j;

	i = all->map_source;
	while (i <= all->map_end)
	{
		j = 0;
		while (all->map[i][j])
		{
			ft_is_valid_lines(all, i, j);
			j++;
		}
		i++;
	}
}
