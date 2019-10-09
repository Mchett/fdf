/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:22:56 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 13:13:35 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	mouse_scroll_down(int but, int x, int y, t_mlx *m_mlx)
{
	x = 0;
	y = 0;
	m_mlx->mouse->down |= (1 << but);
	if (but == 4 || but == 5)
		m_mlx->mouse->down = 0;
	if (but == 4)
		m_mlx->cam->scale *= 1.1f;
	if (but == 5)
		m_mlx->cam->scale /= 1.1f;
	ft_putimage(m_mlx);
	return (0);
}

int	mouse_scroll(int but, int x, int y, t_mlx *m_mlx)
{
	x = 0;
	y = 0;
	but = 0;
	m_mlx->mouse->down = 0;
	return (0);
}

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->mouse->prevx == 0)
		mlx->mouse->prevx = x;
	if (mlx->mouse->prevy == 0)
		mlx->mouse->prevy = y;
	mlx->mouse->prevx = mlx->mouse->x;
	mlx->mouse->prevy = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if ((mlx->mouse->down & (1 << 2)) && (mlx->mouse->down & (1 << 1)))
		mlx->cam->scale += ((x - mlx->mouse->prevx) / 2000.0f) *
			(mlx->cam->scale * 2.1f);
	else if (mlx->mouse->down & (1 << 2))
	{
		mlx->cam->offsetx += x - mlx->mouse->prevx;
		mlx->cam->offsety += y - mlx->mouse->prevy;
	}
	else if (mlx->mouse->down & (1 << 1))
	{
		mlx->cam->y += (x - mlx->mouse->prevx) / 200.0f;
		mlx->cam->x -= (y - mlx->mouse->prevy) / 200.0f;
	}
	else if ((mlx->mouse->down & (1 << 3)))
		mlx->cam->zscale += (x - mlx->mouse->prevx) / 200.0f;
	ft_putimage(mlx);
	return (0);
}
