/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:15:57 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 17:47:59 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_line		*new_line(t_my_point *ps, t_my_point *pe)
{
	t_line *l;

	l = (t_line*)ft_memalloc(sizeof(t_line));
	l->sp = ps;
	l->ep = pe;
	return (l);
}

void		add_line(t_map *my_map, int f, t_my_point *ps, t_my_point *pe)
{
	t_line		*l;
	t_line_list	*list;
	t_line_list	*new_list;

	if (f == 0)
		my_map->lines = ft_memalloc(sizeof(t_line_list));
	l = new_line(ps, pe);
	list = my_map->lines;
	if (f == 0)
	{
		list->content = l;
		list->next = NULL;
	}
	else
	{
		while (list->next != NULL)
			list = list->next;
		new_list = ft_memalloc(sizeof(t_line_list));
		new_list->content = l;
		list->next = new_list;
	}
}

t_p_list	*skip(t_p_list *p2, double k)
{
	while (p2->content->y == k)
		p2 = p2->next;
	return (p2);
}

void		create_lines(t_map *my_map, int i, int j, double k)
{
	t_p_list	*p1;
	t_p_list	*p2;

	p1 = my_map->points;
	p2 = my_map->points;
	p2 = skip(p2, k);
	while (++i < my_map->h - 1)
	{
		j = -1;
		while (++j < my_map->w - 1)
		{
			add_line(my_map, i + j, p1->content, p1->next->content);
			add_line(my_map, i + j + 1, p1->content, p2->content);
			p1 = p1->next;
			p2 = p2->next;
		}
		add_line(my_map, i + j, p1->content, p2->content);
		p1 = p1->next;
		p2 = p2->next;
	}
	while (p1->next != NULL)
	{
		add_line(my_map, 1, p1->content, p1->next->content);
		p1 = p1->next;
	}
}
