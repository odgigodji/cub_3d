/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:54:40 by namerei           #+#    #+#             */
/*   Updated: 2021/02/07 13:54:46 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_do_header(t_all *all, unsigned char *f_hdr, unsigned char *info_hdr)
{
	int	file_size;

	file_size = 14 + 40 + all->height * all->width * all->win->bpp / 8;
	ft_bzero(f_hdr, 14);
	ft_bzero(info_hdr, 40);
	f_hdr[0] = 'B';
	f_hdr[1] = 'M';
	f_hdr[2] = (unsigned char)(file_size);
	f_hdr[3] = (unsigned char)(file_size >> 8);
	f_hdr[4] = (unsigned char)(file_size >> 16);
	f_hdr[5] = (unsigned char)(file_size >> 24);
	f_hdr[10] = (unsigned char)(14 + 40);
	info_hdr[0] = (unsigned char)(40);
	info_hdr[4] = (unsigned char)(all->width);
	info_hdr[5] = (unsigned char)(all->width >> 8);
	info_hdr[6] = (unsigned char)(all->width >> 16);
	info_hdr[7] = (unsigned char)(all->width >> 24);
	info_hdr[8] = (unsigned char)(-all->height);
	info_hdr[9] = (unsigned char)(-all->height >> 8);
	info_hdr[10] = (unsigned char)(-all->height >> 16);
	info_hdr[11] = (unsigned char)(-all->height >> 24);
	info_hdr[12] = (unsigned char)(1);
	info_hdr[14] = (unsigned char)(all->win->bpp);
}

void	ft_do_screenshoot(t_all *all)
{
	unsigned char	f_hdr[14];
	unsigned char	info_hdr[40];
	int				fd;
	int				size_of_block;
	int				i;

	i = 0;
	if (all->save)
	{
		if (!(fd = open("screenshot.bmp", O_RDWR | O_TRUNC | O_CREAT, 0775)))
			exit_cube("screenshot error");
		ft_do_header(all, f_hdr, info_hdr);
		write(fd, f_hdr, 14);
		write(fd, info_hdr, 40);
		size_of_block = all->win->bpp / 8 * all->width;
		while (i < all->height)
			write(fd, all->win->addr + (i++) \
			* all->win->line_l, size_of_block);
		close(fd);
		ft_putendl("\033[36mDoing screenshot...\033[0m");
		ft_putendl("\033[35mEXIT CUBE....\033[0m");
		exit(0);
	}
	else
		return ;
}
