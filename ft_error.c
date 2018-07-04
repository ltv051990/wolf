/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 20:25:51 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/06/07 20:25:53 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_print_error(char *error_type)
{
	ft_printf("%s\n", error_type);
	exit(1);
}

void			full_exit(t_al *uk)
{
	SDL_DestroyTexture(uk->sdl->img);
	SDL_DestroyRenderer(uk->sdl->renderer);
	SDL_DestroyWindow(uk->sdl->win);
	exit(1);
}

static void		init_map_struct(t_al *uk)
{
	int			start;

	start = 0;
	uk->er->map = ft_memalloc(sizeof(int*) * (uk->er->map_height + 1));
	while (start <= uk->er->map_height)
	{
		uk->er->map[start] = ft_memalloc(sizeof(int) * uk->er->map_width);
		start++;
	}
}

void			ft_fill_map(t_al *uk)
{
	t_map		*tmp;
	int			x;
	char		**print;

	x = 0;
	tmp = uk->start;
	init_map_struct(uk);
	while (tmp)
	{
		print = tmp->line;
		x = 0;
		while (x < uk->er->map_width)
		{
			uk->er->map[tmp->nb][x] = ft_atoi(print[x]);
			x++;
		}
		tmp = tmp->next;
	}
}
