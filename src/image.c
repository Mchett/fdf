/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 11:51:12 by mchett            #+#    #+#             */
/*   Updated: 2019/09/18 18:45:37 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		ft_putimage(t_mlx *mlx)
{
	t_p_list	*points;
	t_line_list	*l;

	points = mlx->my_map->points;
	ft_bzero(mlx->image->data, WIN_WIDTH * WIN_HEIGHT * mlx->image->bitspp);
	while (points != NULL)
	{
		*points->content = project_point(*points->content, mlx);
		points = points->next;
	}
	create_lines(mlx->my_map, -1, 0, mlx->my_map->points->content->y);
	l = mlx->my_map->lines;
	while (l != NULL)
	{
		draw_line(mlx, l->content);
		l = l->next;
	}
	while (mlx->my_map->lines != NULL)
	{
		free(mlx->my_map->lines->content);
		l = mlx->my_map->lines->next;
		free(mlx->my_map->lines);
		mlx->my_map->lines = l;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image->ptr, 0, 0);
}

t_image		*ft_delimage(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->ptr != NULL)
			mlx_destroy_image(mlx->mlx_ptr, img->ptr);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

void		image_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(image->data + (x * image->bitspp + y * image->string)) = color;
}

t_image		*new_image(t_mlx *mlx)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (ft_delimage(mlx, img));
	img->data = mlx_get_data_addr(img->ptr, &img->bitspp, &img->string,
			&img->endian);
	img->bitspp /= 8;
	return (img);
}
