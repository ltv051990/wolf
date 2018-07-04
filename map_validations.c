/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:37:17 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/06/06 21:37:19 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	ft_check_per(t_map *tmp)
{
	char	**print;
	int		a;

	a = 0;
	print = tmp->line;
	while (print[a])
	{
		if (ft_atoi(print[a]) < 1)
			ft_print_error("Really? Are you stuped???");
		a++;
	}
}

void		ft_check_size(t_al *uk)
{
	if (uk->er->map_height < 2 || uk->er->map_width < 2)
		ft_print_error("Too small size");
	if (uk->er->map_height > 50 || uk->er->map_width > 50)
		ft_print_error("Too large size");
}

void		ft_check_perimeter(t_al *uk)
{
	t_map	*tmp;
	char	**print;

	tmp = uk->start;
	ft_check_per(tmp);
	while (tmp->next)
	{
		print = tmp->line;
		if (ft_atoi(print[0]) < 1 || ft_atoi(print[uk->er->map_width - 1]) < 1)
			ft_print_error("Really? Are you stuped???");
		tmp = tmp->next;
	}
	ft_check_per(tmp);
}

static void	add_player_check(t_al *uk, int pl_count)
{
	if (pl_count != 1)
		ft_print_error("Player positions error");
	uk->ray->y_pos += 0.4;
	uk->ray->x_pos += 0.4;
}

void		ft_check_player(t_al *uk)
{
	int		x;
	int		pl_count;
	t_map	*tmp;

	pl_count = 0;
	tmp = uk->start;
	while (tmp)
	{
		x = -1;
		while (++x < uk->er->map_width)
		{
			if (ft_strequ("P", tmp->line[x]))
			{
				uk->ray->y_pos = x;
				uk->ray->x_pos = tmp->nb;
				++pl_count;
			}
		}
		tmp = tmp->next;
	}
	add_player_check(uk, pl_count);
}
