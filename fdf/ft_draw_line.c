/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:52:56 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/28 15:55:14 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_put_pixel_img(char *image_str, int x, int y, int color)
{
	unsigned int	pos;

	pos = (x + (WIDTH - 500) * y) * 4;
	if (pos <= (WIDTH - 500) * (HEIGHT - 200) * 4)
	{
		image_str[pos] = color & 0xFF;
		image_str[pos + 1] = (color >> 8) & 0xFF;
		image_str[pos + 2] = (color >> 16) & 0xFF;
	}
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

void	ft_draw_l(char *image_str, t_proj start_pt, t_proj end_pt, t_draw draw)
{
	int	i;

	i = 1;
	while (i <= draw.dx)
	{
		draw.x += draw.xinc;
		draw.percentage = percent(start_pt.x, end_pt.x, draw.x);
		draw.color = ft_get_color(start_pt.color, end_pt.color,
				draw.percentage);
		draw.cumul += draw.dy;
		if (draw.cumul >= draw.dx)
		{
			draw.cumul -= draw.dx;
			draw.y += draw.yinc;
		}
		if (draw.x < WIDTH - 500 && draw.x > 0)
		{
			mlx_put_pixel_img(image_str, draw.x, draw.y, draw.color);
		}
		i++;
	}
}

void	ft_draw_h(char *image_str, t_proj start_pt, t_proj end_pt, t_draw draw)
{
	int	i;

	i = 1;
	while (i <= draw.dy)
	{
		draw.y += draw.yinc;
		draw.percentage = percent(start_pt.y, end_pt.y, draw.y);
		draw.color = ft_get_color(start_pt.color, end_pt.color,
				draw.percentage);
		draw.cumul += draw.dx;
		if (draw.cumul >= draw.dy)
		{
			draw.cumul -= draw.dy;
			draw.x += draw.xinc;
		}
		if (draw.x < WIDTH - 500 && draw.x > 0)
		{
			mlx_put_pixel_img(image_str, draw.x, draw.y, draw.color);
		}
		i++;
	}
}

void	ft_draw_line(char *image_str, t_proj start_pt, t_proj end_pt)
{
	t_draw	draw;

	draw.x = start_pt.x;
	draw.y = start_pt.y;
	draw.dy = end_pt.y - start_pt.y;
	draw.dx = end_pt.x - start_pt.x;
	draw.xinc = (draw.dx > 0) ? 1 : -1;
	draw.yinc = (draw.dy > 0) ? 1 : -1;
	if (draw.dx < 0)
		draw.dx = -draw.dx;
	if (draw.dy < 0)
		draw.dy = -draw.dy;
	if (draw.dx > draw.dy)
	{
		draw.cumul = draw.dx / 2;
		ft_draw_l(image_str, start_pt, end_pt, draw);
	}
	else
	{
		draw.cumul = draw.dy / 2;
		ft_draw_h(image_str, start_pt, end_pt, draw);
	}
}
