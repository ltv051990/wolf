/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 22:47:36 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/07/01 22:47:38 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_redraw_text(t_al *uk)
{
	uk->sdl->img = IMG_LoadTexture(uk->sdl->renderer, uk->sdl->img_path);
	SDL_QueryTexture(uk->sdl->img, NULL, NULL, &uk->sdl->w, &uk->sdl->h);
	uk->sdl->main_texture.x = 0;
	uk->sdl->main_texture.y = 0;
	uk->sdl->main_texture.w = WIDTH;
	uk->sdl->main_texture.h = HEIGHT;
	uk->sdl->weapon.w = 408 * 1.5;
	uk->sdl->weapon.h = 185 * 2.5;
	uk->sdl->weapon.x = (WIDTH / 5 * 3) - uk->sdl->weapon.w / 2;
	uk->sdl->weapon.y = HEIGHT - (uk->sdl->weapon.h - 20);
}

int		find_color_side_wall(t_al *uk)
{
	int	color;
	int	delta;

	color = 0;
	delta = 0;
	if (uk->ray->side == 1 && uk->ray->r_d_y > 0)
		delta = 0;
	if (uk->ray->side == 1 && uk->ray->r_d_y < 0)
		delta = 1;
	if (uk->ray->side == 0 && uk->ray->r_d_x > 0)
		delta = 2;
	if (uk->ray->side == 0 && uk->ray->r_d_x < 0)
		delta = 3;
	if (uk->er->map[uk->ray->x_map][uk->ray->y_map] == 1)
		uk->ad->pixels2 = (uint32_t *)uk->sdl->walls[0][delta]->pixels;
	else if (uk->er->map[uk->ray->x_map][uk->ray->y_map] == 2)
		uk->ad->pixels2 = (uint32_t *)uk->sdl->walls[1][delta]->pixels;
	else if (uk->er->map[uk->ray->x_map][uk->ray->y_map] == 3)
		uk->ad->pixels2 = (uint32_t *)uk->sdl->walls[2][delta]->pixels;
	else
		uk->ad->pixels2 = (uint32_t *)uk->sdl->walls[3][delta]->pixels;
	color = (unsigned int)uk->ad->pixels2[(TEXT_W * uk->ray->y_tex
			+ uk->ray->x_tex)];
	return (color);
}

void	fill_line_text(t_al *uk)
{
	int	y;

	y = uk->ray->start_paint - 1;
	uk->ad->pixels = (uint32_t *)uk->sdl->sur->pixels;
	while (++y < uk->ray->end_paint)
	{
		uk->ad->d = (y * 256 - HEIGHT * 128 + uk->ray->line_size * 128);
		uk->ray->y_tex = (uint32_t)(((uk->ad->d * TEXT_H)
						/ uk->ray->line_size) / 256);
		uk->ad->color_rgb = find_color_side_wall(uk);
		if (uk->ray->side == 1)
			uk->ad->color_rgb = (uk->ad->color_rgb >> 1) & 8355711;
		uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = uk->ad->color_rgb;
	}
}

void	add_fill_floor_textures(t_al *uk)
{
	t_floor a;

	uk->ray->dst_wl = uk->ray->p_wl_dst;
	uk->ray->dst_pl = 0.0;
	if (uk->ray->end_paint < 0)
		uk->ray->end_paint = HEIGHT;
	a.y = uk->ray->end_paint;
	while (++a.y <= HEIGHT)
	{
		uk->ray->c_dst = HEIGHT / (2.0 * a.y - HEIGHT);
		a.weight = (uk->ray->c_dst - uk->ray->dst_pl) / (uk->ray->dst_wl
					- uk->ray->dst_pl);
		a.cur_fl_x = a.weight * uk->ray->fl_x_wl + (1.0 - a.weight)
					* uk->ray->x_pos;
		a.cur_fl_y = a.weight * uk->ray->fl_y_wl + (1.0 - a.weight)
					* uk->ray->y_pos;
		a.fl_tex_x = (int)(a.cur_fl_x * TEXT_W) % TEXT_W;
		a.fl_tex_y = (int)(a.cur_fl_y * TEXT_H) % TEXT_H;
		uk->ad->pixels[uk->ray->x + a.y * uk->sdl->sur->w] =
		(uk->ad->pixels2[TEXT_W * a.fl_tex_y + a.fl_tex_x] >> 1) & 8355711;
		uk->ad->pixels[uk->ray->x + (HEIGHT - a.y) * uk->sdl->sur->w] =
		uk->ad->pixels3[TEXT_W * a.fl_tex_y + a.fl_tex_x];
	}
}

void	fill_floor_textures(t_al *uk)
{
	uk->ad->pixels = (uint32_t *)uk->sdl->sur->pixels;
	uk->ad->pixels2 = (uint32_t *)uk->sdl->walls[4][0]->pixels;
	uk->ad->pixels3 = (uint32_t *)uk->sdl->walls[2][1]->pixels;
	if (uk->ray->side == 0 && uk->ray->r_d_x > 0)
	{
		uk->ray->fl_x_wl = uk->ray->x_map;
		uk->ray->fl_y_wl = uk->ray->y_map + uk->ray->x_wall;
	}
	else if (uk->ray->side == 0 && uk->ray->r_d_x < 0)
	{
		uk->ray->fl_x_wl = uk->ray->x_map + 1.0;
		uk->ray->fl_y_wl = uk->ray->y_map + uk->ray->x_wall;
	}
	else if (uk->ray->side == 1 && uk->ray->r_d_y > 0)
	{
		uk->ray->fl_x_wl = uk->ray->x_map + uk->ray->x_wall;
		uk->ray->fl_y_wl = uk->ray->y_map;
	}
	else
	{
		uk->ray->fl_x_wl = uk->ray->x_map + uk->ray->x_wall;
		uk->ray->fl_y_wl = uk->ray->y_map + 1.0;
	}
	add_fill_floor_textures(uk);
}
