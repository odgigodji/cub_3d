/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:16:54 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 19:17:01 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_cube(char *error_message)
{
	ft_putstr("\033[31mError\n\033[0m");
	write(1, "\033[33m", 5);
	ft_putendl(error_message);
	write(1, "\033[0m", 5);
	ft_putendl("\033[35mEXIT CUBE....\033[0m");
	exit(0);
}

void	check_fd(char *av, t_all *all)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	if (i < 5 || (av[i - 1] != 'b' && av[i - 2] != 'u' && \
	av[i - 3] != 'c' && av[i - 4] != '.'))
		exit_cube("Invalid file");
	if ((all->fd = open(av, O_RDONLY)) < 0)
		exit_cube("Invalid file");
}

void	pars_all_param(char *line_, t_all *all)
{
	char *line;

	if (line_[0] == '\0' || ft_empty_line(line_))
		return ;
	if (!(line = ft_strtrim(line_, " 	\t")))
		exit_cube("malloc error");
	if (line[0] == 'R' && line[1] == ' ')
		ft_resolution(line, all);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		ft_tex_path(line, all, 3);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		ft_tex_path(line, all, 2);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		ft_tex_path(line, all, 1);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		ft_tex_path(line, all, 0);
	else if (line[0] == 'S' && line[1] == ' ')
		ft_tex_path(line, all, 4);
	else if (line[0] == 'F' && line[1] == ' ')
		ft_floor_or_ceiling_color(line + 1, all, 0);
	else if (line[0] == 'C' && line[1] == ' ')
		ft_floor_or_ceiling_color(line + 1, all, 1);
	else
		exit_cube("Parsing error.");
	free(line);
}

void	ft_spr_num(t_all *all)
{
	t_point pos;

	all->spr_num = 0;
	ft_bzero(&pos, sizeof(t_point));
	while (pos.y != (int)all->amount)
	{
		pos.x = 0;
		while (all->map[pos.y][pos.x])
		{
			if (all->map[pos.y][pos.x] == '2')
				all->spr_num++;
			pos.x++;
		}
		pos.y++;
	}
}

void	ft_parser(char *av1, t_all *all)
{
	char *line;

	line = NULL;
	check_fd(av1, all);
	ft_init_pars(all);
	while (get_next_line(all->fd, &line) > 0 && all->parsed_elem != 8)
	{
		pars_all_param(line, all);
		free(line);
	}
	ft_check_parsed_elem(all);
	ft_pars_map(line, all);
}
