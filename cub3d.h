/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:23:45 by namerei           #+#    #+#             */
/*   Updated: 2021/02/08 12:40:45 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

/*
** keys
*/

# define ESC		53
# define W			13
# define A			0
# define S			1
# define D			2
# define Q			12
# define E			14
# define LEFT_KEY	123
# define RIGHT_KEY	124
# define UP_KEY		126
# define DOWN_KEY	125
# define SHIFT		257

/*
** SPEED
*/

# define MOVE_SPEED		1.5
# define ROTATE_SPEED	1

typedef struct		s_pars
{
	int				rep_no;
	int				rep_so;
	int				rep_we;
	int				rep_ea;
	int				rep_spr;
	int				rep_floor;
	int				rep_re;
	int				rep_ceiling;
}					t_pars;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
}					t_win;

/*
** tex_height[0] for textures
** tex_height[1] for sprites
** tex_width[0] for textures
** tex_width[1] for sprites
** tex_path[0] for east
** tex_path[1] for west
** tex_path[2] for south
** tex_path[3] for north
** tex_path[4] for sprite
** floor_or_ceiling_color[0] for floor
** floor_or_ceiling_color[1] for ceiling
*/

typedef struct		s_tex
{
	void			*img[5];
	void			*addr[5];
	int				line_l[5];
	int				bpp[5];
	int				en[5];
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				tex_height[2];
	int				tex_width[2];
	char			*tex_path[5];
	int				floor_or_ceiling_color[2];
}					t_tex;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_spr
{
	double			x;
	double			y;
	double			*zbuffer;
	double			distance;
	double			order;
	double			transform_x;
	double			transform_y;
	int				sprite_sscreen_x;
	int				sprite_height;
	int				stripe;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_end_x;
	int				sprite_width;
	int				pos;
	int				color;
	int				tex_x;
	int				tex_y;
	int				d;
	int				y_;
}					t_spr;

typedef struct		s_plr
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			perp_wall_dist;
	double			move_speed;
	double			rot_speed;
	char			side;
	int				have_player;
}					t_plr;

typedef struct		s_ray
{
	double			dir_x;
	double			dir_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct		s_move
{
	int				up;
	int				down;
	int				right;
	int				left;
	int				turn_l;
	int				turn_r;
	int				shift;
	double			old_dir_x;
	double			old_plane_x;
}					t_move;

typedef struct		s_all
{
	t_win			*win;
	t_plr			*plr;
	t_ray			*ray;
	char			**map;
	t_spr			*spr;
	int				x;
	t_move			move;
	t_tex			tex;
	int				spr_num;
	int				width;
	int				height;
	int				fd;
	int				parsed_elem;
	t_pars			pars;
	int				amount;
	char			*first_line;
	int				flag_line;
	int				map_source;
	int				map_end;
	int				max_len;
	int				save;
}					t_all;

void				ray_casting(t_all *all);
void				draw_line(t_all *all);
int					key_press(int key, t_all *all);
void				init_move_key_structure(t_all *all);
int					key_release(int key, t_all *all);
int					engine(t_all *all);
void				init_textures(t_all *all);
unsigned int		ft_texel_color(t_tex *tex, int x, int y, int i);
int					ft_spr_tex_y(t_all *all, t_tex *tex);
void				my_mlx_pixel_put(t_win *win, int x, int y, int color);
void				draw_line(t_all *all);
void				ray_casting(t_all *all);
void				ft_init_direction(t_all *all);
void				do_sprites(t_all *all);
void				make_map(t_list **head, t_all *all);
void				ft_init_player(t_all *all);
int					ft_close(int key, t_all *all);
void				ft_putendl(char *s);
void				move_up_or_down(t_all *all);
void				move_left_or_right(t_all *all);
void				turn_left_or_right(t_all *all);
void				sort_sprites(t_all *all);
void				ft_spr_num(t_all *all);
void				ft_parser(char *av, t_all *all);
void				ft_floor_or_ceiling_color(char *line, t_all *all, int i);
void				ft_is_correct_map(t_all *all);
void				ft_is_valid_map(t_all *all);
void				exit_cube(char *error_message);
void				ft_pars_map(char *line, t_all *all);
void				ft_check_parsed_elem(t_all *all);
void				ft_init_pars(t_all *all);
void				ft_commas_counter(const char *line, t_all *all);
void				do_res(char **res, int rgb[3]);
void				ft_floor_or_ceiling_color(char *line, t_all *all, int i);
void				ft_pars_map(char *line, t_all *all);
void				make_map(t_list **head, t_all *all);
void				ft_resolution(char *line, t_all *all);
void				ft_tex_path(char *line, t_all *all, int i);
void				ft_is_valid_lines(t_all *all, int i, int j);
void				draw_y_sprite(t_all *all);
void				ft_do_screenshoot(t_all *all);

#endif
