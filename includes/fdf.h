/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 10:06:23 by mchett            #+#    #+#             */
/*   Updated: 2019/09/19 09:23:04 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>

typedef struct				s_point
{
	double					x;
	double					y;
	double					z;
	double					rx;
	double					ry;
	double					rz;
	int						color;
}							t_my_point;

typedef struct				s_point_list
{
	t_my_point				*content;
	struct s_point_list		*next;
}							t_p_list;

typedef struct				s_line
{
	t_my_point				*sp;
	t_my_point				*ep;
}							t_line;

typedef struct				s_line_list
{
	t_line					*content;
	struct s_line_list		*next;
}							t_line_list;

typedef struct				s_cam
{
	double					offsetx;
	double					offsety;
	double					x;
	double					y;
	double					scale;
	double					zscale;
	int						iso;
}							t_cam;

typedef struct				s_mouse
{
	int						x;
	int						y;
	int						prevx;
	int						prevy;
	int						down;
}							t_mouse;

typedef struct				s_map
{
	int						hc;
	int						lc;
	int						highest;
	double					koef;
	int						lowest;
	int						w;
	int						h;
	t_line_list				*lines;
	t_p_list				*points;
}							t_map;

typedef struct				s_image
{
	void					*ptr;
	char					*data;
	int						bitspp;
	int						string;
	int						endian;
}							t_image;

typedef struct				s_mlx
{
	t_map					*my_map;
	void					*mlx_ptr;
	void					*win_ptr;
	t_image					*image;
	t_mouse					*mouse;
	t_cam					*cam;
}							t_mlx;

double						ft_abs(double a);

t_my_point					project_point(t_my_point v, t_mlx *mlx);

t_my_point					rotate(t_my_point p, t_cam *r, double x);

void						ft_putimage(t_mlx *mlx);

t_image						*ft_delimage(t_mlx *mlx, t_image *img);

void						image_set_pixel(t_image *image,
							int x, int y, int color);

t_image						*new_image(t_mlx *mlx);

int							key_hook(int keycode, void *param);

void						draw_line(t_mlx	*m_mlx, t_line *line);

int							read_map(int fd, t_map *my_map);

int							check_mass(char **point_mass, t_map *my_map, int y);

void						hl(t_my_point	*tmp, t_map *my_map);

void						add_point(char *point, t_map *my_map,
							double x, double y);

int							mouse_scroll_down(int but, int x, int y,
							t_mlx *m_mlx);

int							mouse_scroll(int but, int x, int y, t_mlx *m_mlx);

int							ft_mouse_move(int x, int y, t_mlx *mlx);

void						hl(t_my_point	*tmp, t_map *my_map);

void						add_point(char *point, t_map *my_map,
							double x, double y);

int							check_mass(char **point_mass, t_map *my_map, int y);

int							read_map(int fd, t_map *my_map);

t_line						*new_line(t_my_point *ps, t_my_point *pe);

void						add_line(t_map *my_map, int f,
							t_my_point *ps, t_my_point *pe);

void						create_lines(t_map *my_map, int i, int j, double k);

void						clean_all(t_map *my_map);

t_mlx						*mlxdel(t_mlx *mlx);

t_mlx						*init(char *str, t_map *my_map);

void						draw(t_map *my_map, char *str);

void						init_map(t_map	*my_map);

int							clerp(int c1, int c2, double p);

void						set_p(t_mlx *m_mlx, t_line *l, double x, double y);

#endif
