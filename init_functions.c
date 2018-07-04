/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 22:47:59 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/07/01 22:48:05 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				ft_init_sdl(t_al *uk)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(1);
	if ((uk->sdl->win = SDL_CreateWindow("WOLF3D", 100, 100,
						WIDTH, HEIGHT, 0)) == NULL)
		ft_print_error("Window problems =)");
	if ((uk->sdl->renderer = SDL_CreateRenderer(uk->sdl->win,
						-1, SDL_RENDERER_ACCELERATED)) == NULL)
		ft_print_error("Render problems =)");
	if ((uk->sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT,
						32, 0, 0, 0, 0)) == NULL)
		ft_print_error("Can't create surface");
}

void				init_struct(t_al *uk)
{
	uk->sdl = ft_memalloc(sizeof(t_sdl));
	uk->ray = ft_memalloc(sizeof(t_raycast));
	uk->pl = ft_memalloc(sizeof(t_player));
	uk->ad = ft_memalloc(sizeof(t_add));
	uk->er = ft_memalloc(sizeof(t_read));
	uk->sdl->walls = ft_memalloc(sizeof(SDL_Surface*) * 5);
	uk->sdl->walls[0] = ft_memalloc(sizeof(SDL_Surface*) * 4);
	uk->sdl->walls[1] = ft_memalloc(sizeof(SDL_Surface*) * 4);
	uk->sdl->walls[2] = ft_memalloc(sizeof(SDL_Surface*) * 4);
	uk->sdl->walls[3] = ft_memalloc(sizeof(SDL_Surface*) * 4);
	uk->sdl->walls[4] = ft_memalloc(sizeof(SDL_Surface*) * 4);
	uk->sdl->change_weapon = true;
	uk->sdl->tmp = 1;
	uk->sdl->img_path = "textures/23.png";
	uk->ray->ydir = 0;
	uk->ray->xdir = -1;
	uk->ray->xplan = 0;
	uk->ray->yplan = 0.66;
	uk->pl->time = 0;
	uk->pl->otime = 0;
}

void				init_sdl_pixel_format(SDL_PixelFormat *a)
{
	a->BitsPerPixel = 32;
	a->BytesPerPixel = 4;
	a->palette = NULL;
	a->Rmask = 0;
	a->Gmask = 0;
	a->Bmask = 0;
	a->Amask = 0;
}

void				ft_trans_img_to_int_array(t_al *uk, const char *text_name)
{
	SDL_PixelFormat	a;
	static int		index = -1;
	static int		nb_text = 0;

	++index;
	if (index == 4)
	{
		index = 0;
		++nb_text;
	}
	init_sdl_pixel_format(&a);
	uk->sdl->sur3 = IMG_Load(text_name);
	if (!uk->sdl->sur3)
		ft_print_error("Can't download IMG");
	uk->sdl->walls[nb_text][index] = SDL_ConvertSurface(uk->sdl->sur3, &a, 0);
	SDL_FreeSurface(uk->sdl->sur3);
}

void				load_textures(t_al *uk)
{
	if ((uk->sdl->menu = IMG_Load("weap.png")) == NULL)
		ft_print_error("Can't create surface");
	SDL_QueryTexture(uk->sdl->img_menu, NULL, NULL, &uk->sdl->w2, &uk->sdl->h2);
	if ((uk->sdl->img_menu = SDL_CreateTextureFromSurface(uk->sdl->renderer,
							uk->sdl->menu)) == NULL)
		ft_print_error("Can't create Texture");
	ft_trans_img_to_int_array(uk, "textures/1.png");
	ft_trans_img_to_int_array(uk, "textures/2.png");
	ft_trans_img_to_int_array(uk, "textures/3.png");
	ft_trans_img_to_int_array(uk, "textures/4.png");
	ft_trans_img_to_int_array(uk, "textures/5.png");
	ft_trans_img_to_int_array(uk, "textures/6.png");
	ft_trans_img_to_int_array(uk, "textures/7.png");
	ft_trans_img_to_int_array(uk, "textures/8.png");
	ft_trans_img_to_int_array(uk, "textures/9.png");
	ft_trans_img_to_int_array(uk, "textures/10.png");
	ft_trans_img_to_int_array(uk, "textures/11.png");
	ft_trans_img_to_int_array(uk, "textures/12.png");
	ft_trans_img_to_int_array(uk, "textures/13.png");
	ft_trans_img_to_int_array(uk, "textures/14.png");
	ft_trans_img_to_int_array(uk, "textures/15.png");
	ft_trans_img_to_int_array(uk, "textures/16.png");
	ft_trans_img_to_int_array(uk, "textures/floor.png");
}
