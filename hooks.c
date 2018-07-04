/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:02:56 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/06/09 20:02:57 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		key_left(t_al *uk)
{
	double	old_pl_x;
	double	old_dr_x;

	old_dr_x = uk->ray->xdir;
	uk->ray->xdir = uk->ray->xdir * cos(uk->pl->rt_sp) - uk->ray->ydir
					* sin(uk->pl->rt_sp);
	uk->ray->ydir = old_dr_x * sin(uk->pl->rt_sp) + uk->ray->ydir
					* cos(uk->pl->rt_sp);
	old_pl_x = uk->ray->xplan;
	uk->ray->xplan = uk->ray->xplan * cos(uk->pl->rt_sp) - uk->ray->yplan
					* sin(uk->pl->rt_sp);
	uk->ray->yplan = old_pl_x * sin(uk->pl->rt_sp) + uk->ray->yplan
					* cos(uk->pl->rt_sp);
}

void		key_right(t_al *uk)
{
	double	old_dr_x;
	double	old_pl_x;

	old_dr_x = uk->ray->xdir;
	uk->ray->xdir = uk->ray->xdir * cos(-uk->pl->rt_sp) - uk->ray->ydir
					* sin(-uk->pl->rt_sp);
	uk->ray->ydir = old_dr_x * sin(-uk->pl->rt_sp) + uk->ray->ydir
					* cos(-uk->pl->rt_sp);
	old_pl_x = uk->ray->xplan;
	uk->ray->xplan = uk->ray->xplan * cos(-uk->pl->rt_sp) - uk->ray->yplan
					* sin(-uk->pl->rt_sp);
	uk->ray->yplan = old_pl_x * sin(-uk->pl->rt_sp) + uk->ray->yplan
					* cos(-uk->pl->rt_sp);
}

void		key_up(t_al *uk)
{
	if (uk->er->map[(int)(uk->ray->x_pos + uk->ray->xdir
		* uk->pl->mv_sp)][(int)(uk->ray->y_pos)] == false)
		uk->ray->x_pos += uk->ray->xdir * uk->pl->mv_sp;
	if (uk->er->map[(int)(uk->ray->x_pos)][(int)(uk->ray->y_pos
		+ uk->ray->ydir * uk->pl->mv_sp)] == false)
		uk->ray->y_pos += uk->ray->ydir * uk->pl->mv_sp;
	if (!uk->sdl->way && ++uk->sdl->change_weapon < 10)
		uk->sdl->weapon.y -= 2;
	if (!uk->sdl->way && uk->sdl->change_weapon >= 10)
		uk->sdl->way = true;
	if (uk->sdl->way && --uk->sdl->change_weapon > 0)
		uk->sdl->weapon.y += 2;
	if (uk->sdl->way && uk->sdl->change_weapon <= 0)
		uk->sdl->way = false;
}

void		key_down(t_al *uk)
{
	if (uk->er->map[(int)(uk->ray->x_pos - uk->ray->xdir
		* uk->pl->mv_sp)][(int)(uk->ray->y_pos)] == false)
		uk->ray->x_pos -= uk->ray->xdir * uk->pl->mv_sp;
	if (uk->er->map[(int)(uk->ray->x_pos)][(int)(uk->ray->y_pos
		- uk->ray->ydir * uk->pl->mv_sp)] == false)
		uk->ray->y_pos -= uk->ray->ydir * uk->pl->mv_sp;
	if (!uk->sdl->way && ++uk->sdl->change_weapon < 10)
		uk->sdl->weapon.y -= 2;
	if (!uk->sdl->way && uk->sdl->change_weapon >= 10)
		uk->sdl->way = true;
	if (uk->sdl->way && --uk->sdl->change_weapon > 0)
		uk->sdl->weapon.y += 2;
	if (uk->sdl->way && uk->sdl->change_weapon <= 0)
		uk->sdl->way = false;
}
