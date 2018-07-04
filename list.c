/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:39:27 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/06/06 21:39:29 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			ft_check_map(t_al *uk, char *av)
{
	int fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_print_error("Bad map");
	ft_read(uk, fd);
	ft_check_size(uk);
	ft_check_perimeter(uk);
	ft_fill_map(uk);
	ft_check_player(uk);
	close(fd);
}

void			ft_exit_mem(void)
{
	printf("%s\n", "Sorry, error with memory alocation!");
	exit(1);
}

t_map			*lst_matr(char **split, int nb)
{
	t_map		*tmp;

	if ((tmp = ft_memalloc(sizeof(t_map))) == NULL)
		ft_exit_mem();
	tmp->line = split;
	tmp->nb = nb;
	return (tmp);
}

void			lst_matr_pb(t_map **alst, t_map *new)
{
	t_map		*beg;

	if (!alst)
		return ;
	else if (!(*alst))
	{
		*alst = new;
		return ;
	}
	beg = (*alst);
	while (beg->next)
		beg = beg->next;
	beg->next = new;
}

void			ft_read(t_al *uk, int fd)
{
	char		*line;
	char		**split;
	int			res;
	int			ret;

	uk->er->map_height = -1;
	uk->er->map_width = -1;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret < 0)
			ft_print_error("Kiss my a.. with your directory!");
		++uk->er->map_height;
		res = ft_split_cw(line, ',', &split);
		lst_matr_pb(&uk->start, lst_matr(split, uk->er->map_height));
		if (uk->er->map_width == -1)
			uk->er->map_width = res;
		else if (res != uk->er->map_width)
		{
			free(line);
			ft_print_error("Bad map width");
		}
		free(line);
	}
}
