/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 12:30:30 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 18:59:40 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		clean_all(t_map *my_map)
{
	t_p_list	*p2;
	t_line_list	*l2;

	while (my_map->points)
	{
		p2 = my_map->points->next;
		if (my_map->points->content != NULL)
			free(my_map->points->content);
		free(my_map->points);
		my_map->points = p2;
	}
	while (my_map->lines)
	{
		l2 = my_map->lines->next;
		if (my_map->lines->content != NULL)
			free(my_map->lines->content);
		free(my_map->lines);
		my_map->lines = l2;
	}
	free(my_map);
}

static void	ft_scale(t_mlx *mlx, t_map *map)
{
	if ((WIN_WIDTH / map->w) < (WIN_HEIGHT / map->h))
		mlx->cam->scale = ((WIN_WIDTH / map->w) / 2 > 1 ?
			(WIN_WIDTH / map->w) / 2 : 1);
	else
		mlx->cam->scale = ((WIN_HEIGHT / map->h) / 2 > 1 ?
			(WIN_HEIGHT / map->h) / 2 : 1);
}

void		draw(t_map *my_map, char *str)
{
	t_mlx	*m_mlx;

	m_mlx = init(str, my_map);
	if (m_mlx->mlx_ptr != NULL)
	{
		ft_scale(m_mlx, m_mlx->my_map);
		ft_putimage(m_mlx);
		mlx_key_hook(m_mlx->win_ptr, key_hook, m_mlx);
		mlx_hook(m_mlx->win_ptr, 5, 0, mouse_scroll, m_mlx);
		mlx_hook(m_mlx->win_ptr, 4, 0, mouse_scroll_down, m_mlx);
		mlx_hook(m_mlx->win_ptr, 6, 0, ft_mouse_move, m_mlx);
		mlx_loop(m_mlx->mlx_ptr);
	}
}

void		init_map(t_map *my_map)
{
	my_map->w = 0;
	my_map->h = 0;
	my_map->koef = 50;
	my_map->highest = -2147483648;
	my_map->lowest = 2147483647;
	my_map->points = NULL;
	my_map->lines = NULL;
	my_map->hc = 16777215;
	my_map->lc = 255;
}

int			main(int argc, char **argv)
{
	int		fd;
	t_map	*my_map;

	my_map = (t_map*)malloc(sizeof(t_map));
	init_map(my_map);
	if (argc != 2 && argc != 1)
		return (0);
	fd = 0;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	if (fd == 0)
		write(1, "Usage input file\n ", 17);
	else if (fd == -1)
		write(1, "Error read map\n ", 15);
	else if (read_map(fd, my_map) != 0)
		draw(my_map, argv[1]);
	else
	{
		clean_all(my_map);
		write(1, "Error map/n ", 10);
	}
	return (0);
}
