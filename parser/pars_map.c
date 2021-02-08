/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:09:47 by namerei           #+#    #+#             */
/*   Updated: 2021/02/04 19:09:50 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_end(int k, char *line, t_all *all, t_list **head)
{
	ft_lstadd_back(head, ft_lstnew(line));
	k++;
	if ((*line == '\0' || ft_empty_line(line)))
		k--;
	all->amount++;
	all->map_end = k + all->map_source - all->flag_line;
	all->max_len = (all->max_len < (int)ft_strlen(line)) \
	? (int)ft_strlen(line) : all->max_len;
}

void	ft_line_to_list(char *line, t_all *all, int j, t_list **head)
{
	t_list	*new;
	int		k;

	k = 0;
	new = 0;
	if (!(new = ft_lstnew(line)))
		exit_cube("malloc error");
	ft_lstadd_back(head, new);
	all->max_len = (all->max_len < (int)ft_strlen(line)) ? \
	(int)ft_strlen(line) : all->max_len;
	while (get_next_line(all->fd, &line))
	{
		if ((*line == '\0' || ft_empty_line(line)))
			j++;
		ft_lstadd_back(head, ft_lstnew(line));
		if (*line != '\0' && !ft_empty_line(line))
		{
			all->map_source = j;
			k++;
		}
		all->max_len = (all->max_len < (int)ft_strlen(line)) ? \
		(int)ft_strlen(line) : all->max_len;
		all->amount++;
	}
	ft_map_end(k, line, all, head);
}

void	ft_pars_map(char *line, t_all *all)
{
	t_list	*head;
	int		j;

	head = 0;
	if (*line == '\0' || ft_empty_line(line))
	{
		all->flag_line = 1;
		j = 1;
	}
	else
		j = 0;
	ft_line_to_list(line, all, j, &head);
	make_map(&head, all);
}

void	ft_init_map_line(t_list *tmp, t_all *all, int i)
{
	int		k;
	int		space_len;
	char	*spaces;
	char	*t;

	k = 0;
	space_len = all->max_len - ft_strlen(tmp->content) + 1;
	if (!(spaces = malloc(sizeof(char) * space_len + 1)))
		exit_cube("malloc error");
	spaces[space_len] = '\0';
	while (k < space_len)
	{
		spaces[k] = ' ';
		k++;
	}
	if (!(t = (char *)ft_strjoin((char *)tmp->content, spaces)))
		exit_cube("malloc error");
	if (*t != '\0' || !ft_empty_line(t))
	{
		if (!(all->map[i] = (char *)ft_strjoin((char *)" ", t)))
			exit_cube("malloc error");
	}
	free(t);
	free(spaces);
}

void	make_map(t_list **head, t_all *all)
{
	int		i;
	t_list	*tmp;

	tmp = *head;
	i = 0;
	if (!(all->map = (char **)ft_calloc(all->amount + 1, sizeof(char *))))
		exit_cube("malloc error");
	while (tmp && i <= all->amount)
	{
		ft_init_map_line(tmp, all, i);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(head, &free);
}
