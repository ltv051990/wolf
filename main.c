/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:58:34 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/05/14 19:58:36 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		start_wolf(t_al *uk, char **argv)
{
	init_struct(uk);
	ft_check_map(uk, argv[1]);
	ft_init_sdl(uk);
	load_textures(uk);
	ft_redraw_text(uk);
	SDL_RenderClear(uk->sdl->renderer);
	SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img, NULL,
					&uk->sdl->main_texture);
	SDL_RenderPresent(uk->sdl->renderer);
	SDL_Delay(3000);
	system("afplay mp3/1.mp3 & > /dev/null 2>&1");
}

void		change_music(t_al *uk)
{
	++uk->ad->mus;
	system("kill $(pgrep afplay) > /dev/null 2>&1");
	if (uk->ad->mus == 3)
		uk->ad->mus = 0;
	if (uk->ad->mus == 0)
		system("afplay mp3/1.mp3 & > /dev/null 2>&1");
	else if (uk->ad->mus == 1)
		system("afplay mp3/2.mp3 & > /dev/null 2>&1");
	else if (uk->ad->mus == 2)
		system("afplay mp3/3.mp3 & > /dev/null 2>&1");
}

void		catch_hooks(t_al *uk)
{
	uk->pl->fr_time = (uk->pl->time - uk->pl->otime) / 1000.0;
	uk->pl->mv_sp = uk->pl->fr_time * 3.0;
	uk->pl->rt_sp = uk->pl->fr_time * 2.2;
	uk->sdl->keykey = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&uk->sdl->event);
	if (uk->sdl->event.type == SDL_QUIT)
	{
		system("kill $(pgrep afplay) > /dev/null 2>&1");
		full_exit(uk);
	}
	if (uk->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		system("kill $(pgrep afplay) > /dev/null 2>&1");
		full_exit(uk);
	}
	if (uk->sdl->keykey[SDL_SCANCODE_UP])
		key_up(uk);
	if (uk->sdl->keykey[SDL_SCANCODE_DOWN])
		key_down(uk);
	if (uk->sdl->keykey[SDL_SCANCODE_RIGHT])
		key_right(uk);
	if (uk->sdl->keykey[SDL_SCANCODE_LEFT])
		key_left(uk);
	if (uk->sdl->keykey[SDL_SCANCODE_SPACE])
		change_music(uk);
}

void		in_cycle(t_al *uk)
{
	while (++uk->ray->x < WIDTH)
	{
		calc_ray_pos_and_direct(uk);
		calc_step_and_init_side_dist(uk);
		calc_dda(uk);
		uk->ray->tx_nb = uk->er->map[uk->ray->x_map][uk->ray->y_map] - 1;
		if (uk->ray->side == 0)
			uk->ray->x_wall = uk->ray->y_pos + uk->ray->p_wl_dst
							* uk->ray->r_d_y;
		else
			uk->ray->x_wall = uk->ray->x_pos + uk->ray->p_wl_dst
							* uk->ray->r_d_x;
		uk->ray->x_wall -= floor((uk->ray->x_wall));
		uk->ray->x_tex = (int)(uk->ray->x_wall * (double)TEXT_W);
		if (uk->ray->side == 0 && uk->ray->r_d_x > 0)
			uk->ray->x_tex = TEXT_W - uk->ray->x_tex - 1;
		if (uk->ray->side == 1 && uk->ray->r_d_y < 0)
			uk->ray->x_tex = TEXT_W - uk->ray->x_tex - 1;
		fill_line_text(uk);
		fill_floor_textures(uk);
	}
}

int			main(int argc, char **argv)
{
	t_al	*uk;
	int		done;

	if (argc != 2)
		ft_print_error("./wolf maps/[choose map]");
	uk = ft_memalloc(sizeof(t_al));
	start_wolf(uk, argv);
	done = 1;
	while (done)
	{
		uk->ray->x = -1;
		in_cycle(uk);
		present_picture(uk);
		uk->pl->otime = uk->pl->time;
		uk->pl->time = SDL_GetTicks();
		catch_hooks(uk);
	}
	full_exit(uk);
	return (0);
}
