/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_finish.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:57:28 by krutten           #+#    #+#             */
/*   Updated: 2019/01/28 18:56:13 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_circle(void *mlx_ptr, void *win_ptr, int r)
{
	t_array	array;
	int		count;
	float	pixel;
	float	angle;

	colour_circle(&array);
	angle = 0;
	count = 0;
	while (angle <= 6.28)
	{
		count = (int)(angle / (PI / 6));
		pixel = -1;
		while (++pixel <= r)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, (int)((WIDTH - 150) + pixel *
						cos(angle)), (int)((HEIGHT - 150) + pixel * sin(angle)),
					ft_get_color(array.colour[count], 0xffffff, 1 - pixel / r));
		}
		angle += 0.005;
	}
}

void	ft_bounding_box(void *mlx_ptr, void *win_ptr)
{
	int		x;
	int		y;

	x = 9;
	y = HEIGHT - 189;
	while (++x < WIDTH - 489)
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x1ec503);
	y = 9;
	while (++y < HEIGHT - 189)
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x1ec503);
	x = 9;
	y = 9;
	while (++x < WIDTH - 489)
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x1ec503);
	x = 9;
	y = 9;
	while (++y < HEIGHT - 189)
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x1ec503);
}

void	ft_instructions(void *mlx_ptr, void *win_ptr)
{
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 10, 0x1ec503,
			"wasd for moving image");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 50, 0x1ec503,
			"arrow keys for rotating image");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 90, 0x1ec503,
			"p to swap projection");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 130, 0x1ec503,
			"+ and - to change altitude");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 170, 0x1ec503,
			"scroll wheel to zoom");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 210, 0x1ec503,
			"r to reset all manipulations");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 250, 0x1ec503,
			"lmb to change bottom colour");
	mlx_string_put(mlx_ptr, win_ptr, WIDTH - 480, 290, 0x1ec503,
			"rmb to change top colour");
}

void	ft_window_finish(void *mlx_ptr, void *win_ptr)
{
	ft_bounding_box(mlx_ptr, win_ptr);
	ft_instructions(mlx_ptr, win_ptr);
	ft_draw_circle(mlx_ptr, win_ptr, (float)100);
}
