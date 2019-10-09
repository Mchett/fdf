/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:44:58 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 18:46:14 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	hl(t_my_point *tmp, t_map *my_map)
{
	if (tmp->z > my_map->highest)
		my_map->highest = tmp->z;
	if (tmp->z < my_map->lowest)
		my_map->lowest = tmp->z;
}

void	add_point(char *point, t_map *my_map, double x, double y)
{
	t_my_point	*tmp;
	t_p_list	*p1;

	p1 = my_map->points;
	tmp = ft_memalloc(sizeof(t_my_point));
	tmp->x = x;
	tmp->y = y;
	tmp->z = ft_atoi((const char*)point);
	hl(tmp, my_map);
	if (x == 0 && y == 0)
	{
		my_map->points = (t_p_list*)ft_memalloc(sizeof(t_p_list));
		my_map->points->content = tmp;
		my_map->points->next = NULL;
	}
	else
	{
		while (p1->next)
			p1 = p1->next;
		p1->next = ft_memalloc(sizeof(t_p_list));
		p1->next->content = tmp;
		p1->next->next = NULL;
	}
}

int		check_mass(char **point_mass, t_map *my_map, int y)
{
	int flag;
	int i;
	int j;

	flag = 1;
	i = 0;
	while (point_mass[i])
	{
		j = 0;
		while (point_mass[i][j])
		{
			if ((point_mass[i][j] < '0' || point_mass[i][j] > '9') &&
					point_mass[i][j] != '-' && point_mass[i][j] != '+')
				return (0);
			if ((point_mass[i][j] == '-' || point_mass[i][j] == '+') &&
					(point_mass[i][j + 1] < '0' || point_mass[i][j + 1] > '9'))
				return (0);
			j++;
		}
		add_point(point_mass[i], my_map, (double)i, (double)y);
		i++;
	}
	return (i == 0 ? -1 : i);
}

void	free_mass(char **point_mass, int i)
{
	while (point_mass[i])
	{
		free(point_mass[i]);
		i++;
	}
	free(point_mass);
}

int		read_map(int fd, t_map *my_map)
{
	char			*line;
	char			**point_mass;
	int				i;

	while (get_next_line(fd, &line) == 1)
	{
		point_mass = ft_strsplit(line, ' ');
		if (!point_mass)
			return (0);
		i = check_mass(point_mass, my_map, my_map->h);
		free_mass(point_mass, 0);
		if ((i != my_map->w && my_map->w != 0) || i == -1)
			return (0);
		my_map->w = i;
		my_map->h++;
		free(line);
	}
	return (1);
}
