/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_offset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 17:35:37 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/29 17:35:41 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_center(t_proj **points, int height, int width)
{
	float	limits[2];
	int		i;
	int		j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (points[i][j].x > limits[0])
				limits[0] = points[i][j].x;
			if (points[i][j].y > limits[1])
				limits[1] = points[i][j].y;
		}
	}
	while (--i >= 0)
	{
		j = -1;
		while (++j < width)
		{
			points[i][j].x += ((WIDTH - 500) - limits[0]) / 2;
			points[i][j].y += ((HEIGHT - 200) - limits[1]) / 2;
		}
	}
}

void	scaling_compute(t_proj **points, int height, int width, t_array *ar)
{
	int		i;
	int		j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (points[i][j].x < ar->output[0])
				ar->output[0] = points[i][j].x;
			if (points[i][j].x > ar->output[1])
				ar->output[1] = points[i][j].x;
			if (points[i][j].y < ar->output[2])
				ar->output[2] = points[i][j].y;
			if (points[i][j].y > ar->output[3])
				ar->output[3] = points[i][j].y;
		}
	}
}

void	scale_and_offset(t_proj **points, int height, int width)
{
	int		i;
	int		j;
	int		scaling;
	t_array	array;

	scaling_compute(points, height, width, &array);
	scaling = MIN((WIDTH - 500) / (array.output[1] - array.output[0]),
			(HEIGHT - 200) / (array.output[3] - array.output[2]));
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			points[i][j].x -= array.output[0];
			points[i][j].y -= array.output[2];
			points[i][j].x *= scaling;
			points[i][j].y *= scaling;
		}
	}
	ft_center(points, height, width);
}
