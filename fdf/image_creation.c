/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:01:06 by krutten           #+#    #+#             */
/*   Updated: 2019/03/05 22:23:35 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat	compute_matrix(t_matspecs specs)
{
	t_mat		output;
	t_mat		proj;
	t_mat		rot;

	if (specs.proj == -1)
	{
		proj = matrix_matrix_multiply(rotation_matrix_x(-90),
				rotation_matrix_y(0));
	}
	else
	{
		proj = matrix_matrix_multiply(rotation_matrix_x(-35.264),
				rotation_matrix_y(-45));
	}
	rot = matrix_matrix_multiply(rotation_matrix_y(specs.alpha),
			rotation_matrix_x(specs.beta));
	output = matrix_matrix_multiply(proj, rot);
	return (output);
}

void	ft_zoom_displace(t_proj **pts, t_matspecs specs, int height, int width)
{
	int			a;
	int			b;

	a = -1;
	while (++a < height)
	{
		b = -1;
		while (++b < width)
		{
			pts[a][b].x = (pts[a][b].x -
					(WIDTH - 500) / 2) * specs.zoom + (WIDTH - 500) / 2;
			pts[a][b].y = (pts[a][b].y -
					(HEIGHT - 200) / 2) * specs.zoom + (HEIGHT - 200) / 2;
		}
	}
	a = -1;
	while (++a < height)
	{
		b = -1;
		while (++b < width)
		{
			pts[a][b].x += specs.displace_x;
			pts[a][b].y += specs.displace_y;
		}
	}
}

t_proj	**project_points(int ***grid, int height, int width, t_matspecs specs)
{
	t_vector	two;
	int			a;
	int			b;
	t_proj		**pts;

	a = -1;
	if (!(pts = malloc_project_pts(height, width)))
		return (NULL);
	while (++a < height)
	{
		b = -1;
		while (++b < width)
		{
			two.x = b;
			two.y = -(grid[a][b][1] / 3.0) * specs.proj * specs.alt;
			two.z = a;
			two = vector_matrix_multiply(two, compute_matrix(specs));
			pts[a][b].x = two.x - cos(PI / 6) * two.z * (specs.proj - 1) * -0.5;
			pts[a][b].y = two.y + sin(PI / 6) * two.z * (specs.proj - 1) * -0.5;
			pts[a][b].color = grid[a][b][0];
		}
	}
	scale_and_offset(pts, height, width);
	ft_zoom_displace(pts, specs, height, width);
	return (pts);
}

void	refill_colours(t_hook *par, float min, float max)
{
	int			a;
	int			b;

	a = -1;
	while (++a < par->height)
	{
		b = -1;
		while (++b < par->width)
		{
			if (!(max == 0 && min == 0))
				par->grid[a][b][0] = ft_get_color(par->specs.colour_low,
						par->specs.colour_high,
						(float)((par->grid[a][b][1] - min) / (max - min)));
			else
				par->grid[a][b][0] = par->specs.colour_low;
		}
	}
}

void	manipulate_colours(t_hook *par)
{
	int			a;
	int			b;
	float		max;
	float		min;

	if (par->specs.coloured == 1)
		return ;
	max = 0;
	min = 0;
	a = -1;
	while (++a < par->height)
	{
		b = -1;
		while (++b < par->width)
		{
			if (par->grid[a][b][1] > max)
				max = par->grid[a][b][1];
			if (par->grid[a][b][1] < min)
				min = par->grid[a][b][1];
		}
	}
	refill_colours(par, min, max);
}
