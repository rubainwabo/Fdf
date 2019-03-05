/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:03:03 by rkamegne          #+#    #+#             */
/*   Updated: 2019/02/24 22:17:14 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlxd.h"
#include <unistd.h>
#include <stdio.h>
void	draw_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color);

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
int		deal_key(int button, int x, int y,  void *param)
{
	return (0);
}

void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
	int x, y, dx, dy, xinc, yinc, cumul, i;

	dy = y2 - y1;
	dx = x2 - x1;
	x = x1;
	y = y1;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = ABS(dx);
	dy = ABS(dy);
	i = 1;
	draw_pixel(mlx_ptr, win_ptr, x, y, color);
	if (dx > dy)
	{
		cumul = dx / 2;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			draw_pixel(mlx_ptr, win_ptr, x, y, color);
			i++;
		}
	}
	else
	{
		cumul = dy / 2;
		while (i <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
		draw_pixel(mlx_ptr, win_ptr, x, y, color);
		i++;
		}
	}
}

void	connect_dots(void *mlx_ptr, void *win_ptr, t_proj **points, t_inf inf, int color)
{
	int		i;
	int		j;
	int		width;
	int		height;
	int		color1 = 0xf00000;

	width = inf.width;
	height = inf.height;
	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			if (j + 1 < height)
				draw_line(mlx_ptr, win_ptr, points[i][j].x, points[i][j].y, points[i][j + 1].x,
						points[i][j + 1].y, color);
			if (j - 1 > 0)
				draw_line(mlx_ptr, win_ptr, points[i][j].x, points[i][j].y, points[i][j - 1].x,
						points[i][j - 1].y, color);
			if (i + 1 < width)
				draw_line(mlx_ptr, win_ptr, points[i][j].x, points[i][j].y, points[i + 1][j].x,
						points[i + 1][j].y, color);
			if (i - 1 > 0)
				draw_line(mlx_ptr, win_ptr, points[i][j].x, points[i][j].y, points[i - 1][j].x,
						points[i - 1][j].y, color);
		}
	}
}

int		main(int ac, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mouse *mouse;
	t_param	*specs;
	int		**grid;
	int		fd;
	int		width;
	int		height;
	int		i;
	float	X;
	float	Y;
	int		a;
	int		b;
	int		dis;
	float	xscaling;
	float	yscaling;
	t_inf	inf;
	t_proj	**points;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "fdf");
	mouse = NULL;
	specs = ft_param_new(mlx_ptr, win_ptr, mouse);
	grid = ft_process_file(fd, &width, &height);
	//points = project_grid(grid);
	printf("width %d height %d\n", width, height);
	a = -1;
	inf.width = width;
	inf.height = height;
	xscaling = WIDTH/((0.866 * width + 0.866 * height));
    yscaling = HEIGHT/(0.5*width + 0.5*height);
	printf("x and y scaling : %f & %f\n", xscaling, yscaling);
	points = (t_proj **)malloc(sizeof(t_proj *) * width);
	while (++a < width)
	{
		b = -1;
		points[a] = (t_proj *)malloc(sizeof(t_proj) * height);
		while (++b < height)
		{
			X = (float)0.866 * height * xscaling + b * 0.866 * xscaling - a * 0.866 * xscaling;
			//X = (float) b * xscaling - grid[a][b] / 2;
            points[a][b].x = X;
          Y = (float) a * 0.5 * yscaling + b * 0.5 * yscaling - grid[a][b];
			//Y =	a * yscaling + 0.866 / 2 * grid[a][b];  
			points[a][b].y = Y;
			points[a][b].alt = grid[a][b];
			printf("grid[%d][%d]\tX = %f & Y = %f\npoints[a][b].x = %f points[a][b].alt = %d\n", a, b, X, Y,points[a][b].x, points[a][b].alt);
		/*	if (grid[a][b] == 0)
				draw_pixel(mlx_ptr, win_ptr, X, Y, 0xffff00);
			else
				draw_pixel(mlx_ptr, win_ptr, X, Y, 0xf00000);*/
		}
	}
	connect_dots(mlx_ptr, win_ptr, points, inf, 0xffff00);
	mlx_mouse_hook(win_ptr, deal_key, specs);
	close(fd);
	mlx_loop(mlx_ptr);
	return (0);
}
