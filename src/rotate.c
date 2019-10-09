/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:46:24 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 15:29:53 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_my_point	project_point(t_my_point v, t_mlx *mlx)
{
	v = rotate(v, mlx->cam, 0);
	v.rx *= mlx->cam->scale;
	v.ry *= mlx->cam->scale;
	v.rx += mlx->cam->offsetx;
	v.ry += mlx->cam->offsety;
	return (v);
}

t_my_point	rotate(t_my_point p, t_cam *r, double x)
{
	t_my_point	v;
	double		y;
	double		z;

	x = p.x;
	z = p.z * r->zscale;
	y = p.y;
	v.x = p.x;
	v.y = p.y;
	v.z = p.z;
	if (r->iso == 1)
	{
		v.rx = (x - y) * cos(0.523599);
		v.ry = -z + (x + y) * sin(0.523599);
		v.rz = p.z;
		v.color = p.color;
		return (v);
	}
	v.rx = cos(r->y) * x + sin(r->y) * z;
	v.rz = -sin(r->y) * x + cos(r->y) * z;
	z = v.z;
	v.ry = cos(r->x) * y - sin(r->x) * z;
	v.rz = sin(r->x) * y + cos(r->x) * z;
	v.color = p.color;
	return (v);
}
