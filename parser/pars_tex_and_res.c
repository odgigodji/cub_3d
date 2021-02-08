/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tex_and_res.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:14:54 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 19:14:56 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_tex(char *tex_path)
{
	int i;
	int fd;

	i = 0;
	while (tex_path[i])
		i++;
	if (i < 5 || ((tex_path[i - 1] != 'm' || tex_path[i - 1] != 'M') \
	&& (tex_path[i - 2] != 'p' || tex_path[i - 2] != 'P') && \
	(tex_path[i - 3] != 'x' || tex_path[i - 3] != 'X') \
	&& tex_path[i - 4] != '.'))
		exit_cube("Textures:incorrect extension.");
	if ((fd = open(tex_path, O_RDONLY)) < 0)
		exit_cube("Textures:invalid file.");
}

void	ft_min_and_max_res(t_all *all)
{
	if (all->width <= 150)
		all->width = 150;
	if (all->height <= 150)
		all->height = 150;
	if (all->width >= 2560)
		all->width = 2560;
	if (all->height >= 1440)
		all->height = 1440;
}

void	ft_resolution(char *line, t_all *all)
{
	char **res;

	if (!(res = ft_split(line, ' ')))
		exit_cube("malloc error.");
	if (ft_array_len(res) != 3)
		exit_cube("Resolution:incorrect number of element");
	if (((all->width = ft_atoi(res[1])) <= 0) && (ft_strlen(res[1]) < 19))
		exit_cube("Resolution:incorrect resolution width");
	if ((all->height = ft_atoi(res[2])) <= 0 && (ft_strlen(res[2]) < 19))
		exit_cube("Resolution:incorrect resolution height");
	if (ft_strlen(res[1]) > 5)
		all->width = 2560;
	if (ft_strlen(res[2]) > 5)
		all->height = 1440;
	ft_min_and_max_res(all);
	all->pars.rep_re++;
	all->parsed_elem++;
	free(res[0]);
	free(res[1]);
	free(res[2]);
	free(res);
}

/*
** i = 0 for east
** i = 1 for west
** i = 2 for south
** i = 3 for north
** i = 4 for sprite
*/

void	ft_tex_path(char *line, t_all *all, int i)
{
	char **res;

	if (!(res = ft_split(line, ' ')))
		exit_cube("malloc error");
	if (ft_array_len(res) != 2)
		exit_cube("Textures:incorrect number of element");
	all->tex.tex_path[i] = res[1];
	check_tex(all->tex.tex_path[i]);
	all->parsed_elem++;
	if (i == 0)
		all->pars.rep_ea++;
	if (i == 1)
		all->pars.rep_we++;
	if (i == 2)
		all->pars.rep_so++;
	if (i == 3)
		all->pars.rep_no++;
	if (i == 4)
		all->pars.rep_spr++;
	free(res[0]);
	free(res);
}
