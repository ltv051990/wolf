/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:58:43 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/07/03 19:44:50 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft/libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include <SDL.h>
# include <stdbool.h>
# include <SDL_image.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# define WIDTH 1200
# define HEIGHT 1000
# define TEXT_W 64
# define TEXT_H 64

typedef struct		s_floor
{
	double			weight;
	double			cur_fl_x;
	double			cur_fl_y;
	int				fl_tex_x;
	int				fl_tex_y;
	int				y;
}					t_floor;

typedef struct		s_map
{
	char			**line;
	int				nb;
	struct s_map	*next;
}					t_map;

typedef struct		s_read
{
	int				**map;
	int				map_width;
	int				map_height;
}					t_read;

typedef struct		s_add
{
	int				mus;
	int				d;
	int				x;
	int				done;
	int				color_rgb;
	uint32_t		*pixels;
	uint32_t		*pixels2;
	uint32_t		*pixels3;
	double			f_weight;
	double			now_fl_x;
	double			now_fl_y;
}					t_add;

typedef struct		s_raycast
{
	int				tx_nb;
	int				y_tex;
	int				x_tex;
	int				x_map;
	int				y_map;
	int				stp_x;
	int				stp_y;
	int				hit;
	int				side;
	int				line_size;
	int				start_paint;
	int				end_paint;
	int				x;
	double			x_wall;
	double			x_pos;
	double			y_pos;
	double			xdir;
	double			ydir;
	double			xplan;
	double			yplan;
	double			cam_x;
	double			r_d_x;
	double			r_d_y;
	double			s_dst_x;
	double			s_dst_y;
	double			d_dst_x;
	double			d_dst_y;
	double			p_wl_dst;
	double			fl_x_wl;
	double			fl_y_wl;
	double			dst_wl;
	double			dst_pl;
	double			c_dst;
}					t_raycast;

typedef struct		s_player
{
	double			time;
	double			otime;
	double			fr_time;
	double			mv_sp;
	double			rt_sp;
}					t_player;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*img;
	SDL_Texture		*fillscreen;
	SDL_Rect		main_texture;
	SDL_Rect		weapon;
	SDL_Event		event;
	SDL_Surface		*sur;
	SDL_Surface		*sur2;
	SDL_Surface		*sur3;
	SDL_Surface		*menu;
	SDL_Texture		*img_menu;
	SDL_Surface		***walls;
	int				w;
	int				h;
	int				w2;
	int				h2;
	int				tmp;
	char			*img_path;
	int				change_weapon;
	const Uint8		*keykey;
	bool			way;
}					t_sdl;

typedef struct		s_al
{
	t_sdl			*sdl;
	t_player		*pl;
	t_raycast		*ray;
	t_add			*ad;
	t_read			*er;
	t_map			*start;
}					t_al;

/*
*** init functions
*/

void				ft_init_sdl(t_al *uk);
void				init_struct(t_al *uk);
void				init_sdl_pixel_format(SDL_PixelFormat *a);
void				ft_trans_img_to_int_array(t_al *uk, const char *text_name);
void				load_textures(t_al *uk);

/*
*** print_error functions
*/

void				ft_print_error(char *error_type);
void				full_exit(t_al *uk);

/*
*** read and check map
*/

void				ft_check_map(t_al *uk, char *av);
void				ft_read(t_al *uk, int fd);
void				ft_check_size(t_al *uk);
void				ft_check_perimeter(t_al *uk);
void				ft_check_player(t_al *uk);
void				ft_fill_map(t_al *uk);

/*
*** hooks
*/

void				key_left(t_al *uk);
void				key_right(t_al *uk);
void				key_up(t_al *uk);
void				key_down(t_al *uk);

/*
*** dda_algo
*/

void				calc_ray_pos_and_direct(t_al *uk);
void				calc_step_and_init_side_dist(t_al *uk);
void				calc_dda(t_al *uk);

/*
*** dda_algo
*/

void				ft_redraw_text(t_al *uk);
void				present_picture(t_al *uk);
int					find_color_side_wall(t_al *uk);
void				fill_line_text(t_al *uk);
void				fill_floor_textures(t_al *uk);

#endif
