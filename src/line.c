/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:23:24 by mchett            #+#    #+#             */
/*   Updated: 2019/09/19 09:08:40 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	dl(t_mlx *m_mlx, int i, t_line *l)
{
	i = l->sp->ry - 1;
	if (l->ep->rx == l->sp->rx)
		if (l->ep->ry > l->sp->ry)
			while (++i < l->ep->ry)
				set_p(m_mlx, l, l->sp->rx, i);
		else
		{
			i = l->ep->ry - 1;
			while (++i < l->sp->ry)
				set_p(m_mlx, l, l->sp->rx, i);
		}
	else
	{
		i = l->sp->rx - 1;
		if (l->ep->rx > l->sp->rx)
			while (++i < l->ep->rx)
				set_p(m_mlx, l, i, l->sp->ry);
		else
		{
			i = l->ep->rx - 1;
			while (++i < l->sp->rx)
				set_p(m_mlx, l, i, l->sp->ry);
		}
	}
}

double	ft_abs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	d_l1(int i, t_mlx *m_mlx, t_line *l)
{
	double	y;

	if (l->ep->rx > l->sp->rx)
		while (++i < l->ep->rx)
		{
			y = l->sp->ry + (l->ep->ry - l->sp->ry) /
			(l->ep->rx - l->sp->rx) * (i - l->sp->rx);
			set_p(m_mlx, l, i, y);
		}
	else
	{
		i = l->ep->rx - 1;
		while (++i < l->sp->rx)
		{
			y = l->sp->ry + (l->ep->ry - l->sp->ry) /
			(l->ep->rx - l->sp->rx) * (i - l->sp->rx);
			set_p(m_mlx, l, i, y);
		}
	}
}

void	dl2(int i, t_mlx *m_mlx, t_line *l)
{
	double	y;

	if (l->ep->ry > l->sp->ry)
		while (++i < l->ep->ry)
		{
			y = l->sp->rx + (l->ep->rx - l->sp->rx) /
			(l->ep->ry - l->sp->ry) * (i - l->sp->ry);
			set_p(m_mlx, l, y, i);
		}
	else
	{
		i = l->ep->ry - 1;
		while (++i < l->sp->ry)
		{
			y = l->sp->rx + (l->ep->rx - l->sp->rx) /
			(l->ep->ry - l->sp->ry) * (i - l->sp->ry);
			set_p(m_mlx, l, y, i);
		}
	}
}

void	draw_line(t_mlx *m_mlx, t_line *l)
{
	int		i;

	if (l->ep->rx == l->sp->rx || l->ep->ry == l->sp->ry)
		dl(m_mlx, 0, l);
	else if (ft_abs(l->ep->rx - l->sp->rx) > ft_abs(l->ep->ry - l->sp->ry))
		d_l1(l->sp->rx - 1, m_mlx, l);
	else
		dl2(i = l->sp->ry - 1, m_mlx, l);
}
