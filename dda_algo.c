/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:07:36 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/06/09 20:07:38 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		calc_ray_pos_and_direct(t_al *uk)
{
	uk->ray->cam_x = 2 * uk->ray->x / (double)WIDTH - 1;
	uk->ray->r_d_x = uk->ray->xdir + uk->ray->xplan * uk->ray->cam_x;
	uk->ray->r_d_y = uk->ray->ydir + uk->ray->yplan * uk->ray->cam_x;
	uk->ray->x_map = (int)uk->ray->x_pos;
	uk->ray->y_map = (int)uk->ray->y_pos;
	uk->ray->d_dst_x = fabs(1 / uk->ray->r_d_x);
	uk->ray->d_dst_y = fabs(1 / uk->ray->r_d_y);
	uk->ray->hit = 0;
}

void		calc_step_and_init_side_dist(t_al *uk)
{
	if (uk->ray->r_d_x < 0)
	{
		uk->ray->stp_x = -1;
		uk->ray->s_dst_x = (uk->ray->x_pos - uk->ray->x_map) * uk->ray->d_dst_x;
	}
	else
	{
		uk->ray->stp_x = 1;
		uk->ray->s_dst_x = (uk->ray->x_map + 1.0
							- uk->ray->x_pos) * uk->ray->d_dst_x;
	}
	if (uk->ray->r_d_y < 0)
	{
		uk->ray->stp_y = -1;
		uk->ray->s_dst_y = (uk->ray->y_pos - uk->ray->y_map) * uk->ray->d_dst_y;
	}
	else
	{
		uk->ray->stp_y = 1;
		uk->ray->s_dst_y = (uk->ray->y_map + 1.0
						- uk->ray->y_pos) * uk->ray->d_dst_y;
	}
}

static void	add_calc_dda(t_al *uk)
{
	if (uk->ray->side == 0)
		uk->ray->p_wl_dst = (uk->ray->x_map - uk->ray->x_pos
							+ (1 - uk->ray->stp_x) / 2) / uk->ray->r_d_x;
	else
		uk->ray->p_wl_dst = (uk->ray->y_map - uk->ray->y_pos
							+ (1 - uk->ray->stp_y) / 2) / uk->ray->r_d_y;
	uk->ray->p_wl_dst += 0.01;
	uk->ray->line_size = (int)(HEIGHT / uk->ray->p_wl_dst);
	uk->ray->start_paint = -uk->ray->line_size / 2 + HEIGHT / 2;
	if (uk->ray->start_paint < 0)
		uk->ray->start_paint = 0;
	uk->ray->end_paint = (int)(uk->ray->line_size / 2 + HEIGHT / 2);
	if (uk->ray->end_paint >= HEIGHT)
		uk->ray->end_paint = HEIGHT - 1;
	uk->ray->p_wl_dst -= 0.01;
}

void		calc_dda(t_al *uk)
{
	while (uk->ray->hit == 0)
	{
		if (uk->ray->s_dst_x < uk->ray->s_dst_y)
		{
			uk->ray->s_dst_x += uk->ray->d_dst_x;
			uk->ray->x_map += uk->ray->stp_x;
			uk->ray->side = 0;
		}
		else
		{
			uk->ray->s_dst_y += uk->ray->d_dst_y;
			uk->ray->y_map += uk->ray->stp_y;
			uk->ray->side = 1;
		}
		if (uk->er->map[uk->ray->x_map][uk->ray->y_map] > 0)
			uk->ray->hit = 1;
	}
	add_calc_dda(uk);
}

void		present_picture(t_al *uk)
{
	if ((uk->sdl->img = SDL_CreateTextureFromSurface(uk->sdl->renderer,
						uk->sdl->sur)) == NULL)
		ft_print_error("Can't create textures");
	SDL_RenderClear(uk->sdl->renderer);
	SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img, NULL,
					&uk->sdl->main_texture);
	SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img_menu, NULL,
					&uk->sdl->weapon);
	SDL_DestroyTexture(uk->sdl->img);
	SDL_RenderPresent(uk->sdl->renderer);
}
