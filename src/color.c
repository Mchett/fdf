/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:23:44 by mchett            #+#    #+#             */
/*   Updated: 2019/09/19 09:20:27 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double	count_p(double val, double first, double second)
{
	if (val == first)
		return (0.0);
	if (val == second)
		return (1.0);
	return ((val - first) / (second - first));
}

int		ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int		clerp(int c1, int c2, double p)
{
	int r;
	int g;
	int b;

	if (c1 == c2)
		return (c1);
	r = ft_lerpi((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = ft_lerpi((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = ft_lerpi(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}

void	set_p(t_mlx *m_mlx, t_line *l, double x, double y)
{
	double		z;
	int			c;
	double		p;

	if (ft_abs(l->ep->rx - l->sp->rx) < ft_abs(l->ep->ry - l->sp->ry))
		p = count_p(y, l->sp->ry, l->ep->ry);
	else
		p = count_p(x, l->sp->rx, l->ep->rx);
	z = (l->ep->z - l->sp->z) * p + l->sp->z;
	p = count_p(z, m_mlx->my_map->lowest, m_mlx->my_map->highest);
	c = clerp(m_mlx->my_map->lc, m_mlx->my_map->hc, p);
	image_set_pixel(m_mlx->image, x, y, c);
}
