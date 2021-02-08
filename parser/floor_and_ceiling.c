/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:03:41 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 19:03:44 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_commas_counter(const char *line, t_all *all)
{
	int j;
	int k;

	(void)all;
	j = 0;
	k = 0;
	while (line[j++])
	{
		if (line[j] == ',')
			k++;
	}
	if (k != 2)
		exit_cube("C/F:incorrect numbers of element or commas.");
}

void	do_res(char **res, int rgb[3])
{
	char	*s;
	int		j;

	s = NULL;
	j = 0;
	while (j < 3)
	{
		if (!(s = ft_strtrim(res[j], " ")))
			exit_cube("malloc error");
		rgb[j] = ft_atoi(s);
		free(s);
		free(res[j]);
		j++;
	}
}

/*
** i = 0 and floor_or_ceiling_color[0] for floor
** i = 1 and floor_or_ceiling_color[1] for ceiling
*/

void	ft_floor_or_ceiling_color(char *line, t_all *all, int i)
{
	int		rgb[3];
	char	**res;

	ft_commas_counter(line, all);
	if (!(res = ft_split(line, ',')))
		exit_cube("malloc error");
	if (ft_array_len(res) != 3)
		exit_cube("C/F:incorrect number of elements.");
	do_res(res, rgb);
	if ((rgb[0] < 0 || rgb[0] > 255) || (rgb[1] < 0 || rgb[1] > 255)\
	|| (rgb[2] < 0 || rgb[2] > 255))
		exit_cube("C/F:incorrect value of RGB.");
	if (i == 0)
		all->pars.rep_floor++;
	if (i == 1)
		all->pars.rep_ceiling++;
	all->tex.floor_or_ceiling_color[i] = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	all->parsed_elem++;
	free(res);
}
