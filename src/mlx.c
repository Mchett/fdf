/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:15:43 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 14:17:09 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(char *str, t_map *my_map)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx_ptr = mlx_init()) == NULL ||
			(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH,
										WIN_HEIGHT, str)) == NULL ||
			(mlx->cam = ft_memalloc(sizeof(t_cam))) == NULL ||
			(mlx->image = new_image(mlx)) == NULL ||
			(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL)
		return (mlxdel(mlx));
	mlx->my_map = my_map;
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
	mlx->mouse->x = 0;
	mlx->mouse->y = 0;
	mlx->cam->iso = 0;
	mlx->cam->zscale = 1;
	return (mlx);
}
