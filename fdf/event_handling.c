/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 05:39:35 by krutten           #+#    #+#             */
/*   Updated: 2019/01/29 17:33:42 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_circle(t_array *array)
{
	array->colour[0] = 0x0000ff;
	array->colour[1] = 0x0080ff;
	array->colour[2] = 0x00ffff;
	array->colour[3] = 0x00ff80;
	array->colour[4] = 0x00ff00;
	array->colour[5] = 0x80ff00;
	array->colour[6] = 0xffff00;
	array->colour[7] = 0xff8000;
	array->colour[8] = 0xff0000;
	array->colour[9] = 0xff0080;
	array->colour[10] = 0xff00ff;
	array->colour[11] = 0x8000ff;
}

int		ft_colour_grid(int x, int y)
{
	t_array	array;
	float	angle;
	float	r;

	colour_circle(&array);
	x -= (WIDTH - 150);
	y -= (HEIGHT - 150);
	r = sqrt(pow((float)x / 100, 2) + pow((float)y / 100, 2));
	if (r > 1)
		return (0);
	angle = acos((float)(x / r) / 100);
	if (y < 0)
		angle = 2 * PI - angle;
	if ((int)(angle / (PI / 6)) < 0 || (int)(angle / (PI / 6)) > 11)
		return (0);
	return (ft_get_color(array.colour[(int)(angle / (PI / 6))], 0xffffff,
				1 - r));
}

int		deal_key_cont(int key, t_hook *reader)
{
	if (key == 15)
	{
		reader->specs.alpha = 0;
		reader->specs.beta = 0;
		reader->specs.zoom = 1;
		reader->specs.displace_x = 0;
		reader->specs.displace_y = 0;
		reader->specs.proj = 1;
		reader->specs.alt = 1;
		reader->specs.colour_low = 0xffffff;
		reader->specs.colour_high = 0x00ff00;
	}
	else if (key == 53)
	{
		exit(0);
		return (0);
	}
	if (draw_image(reader->mlx_ptr, reader->win_ptr, reader) < 0)
		exit(0);
	return (0);
}

int		deal_key(int key, void *param)
{
	t_hook		*reader;

	reader = param;
	if (key == 123 || key == 124)
		reader->specs.alpha -= key * 4 - 494;
	else if (key == 126 || key == 125)
		reader->specs.beta += key * 4 - 502;
	else if (key == 13)
		reader->specs.displace_y -= 5;
	else if (key == 1)
		reader->specs.displace_y += 5;
	else if (key == 0 || key == 2)
		reader->specs.displace_x += key * 5 - 5;
	else if (key == 35)
		reader->specs.proj *= -1;
	else if (key == 78)
		reader->specs.alt /= 1.1;
	else if (key == 69)
		reader->specs.alt *= 1.1;
	else
		deal_key_cont(key, reader);
	if (draw_image(reader->mlx_ptr, reader->win_ptr, reader) < 0)
		exit(0);
	return (0);
}

int		deal_mouse(int button, int x, int y, void *param)
{
	t_hook		*reader;

	reader = param;
	if (button == 4)
		reader->specs.zoom += 0.1;
	else if (button == 5)
		reader->specs.zoom -= 0.1;
	else if (button == 1 && (x > WIDTH - 250 && x < WIDTH - 50)
			&& (y > HEIGHT - 250 && y < HEIGHT - 50))
	{
		reader->specs.coloured = 0;
		reader->specs.colour_low = ft_colour_grid(x, y);
	}
	else if (button == 2 && (x > WIDTH - 250 && x < WIDTH - 50)
			&& (y > HEIGHT - 250 && y < HEIGHT - 50))
	{
		reader->specs.coloured = 0;
		reader->specs.colour_high = ft_colour_grid(x, y);
	}
	if (draw_image(reader->mlx_ptr, reader->win_ptr, reader) < 0)
		exit(0);
	return (0);
}
