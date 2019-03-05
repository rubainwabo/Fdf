/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:03:03 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/03 20:15:53 by krutten          ###   ########.fr       */
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

//t_proj	**project_points(points)
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
	t_proj	**points;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1200, 1200, "fdf");
	mouse = NULL;
	specs = ft_param_new(mlx_ptr, win_ptr, mouse);
	grid = ft_process_file(fd, &width, &height);
	//points = project_grid(grid);
	//printf("width %d height %d\n", width, height);
	a = -1;
	points = (t_proj **)malloc(sizeof(t_proj *) * width);
	while (++a < width)
	{
		b = -1;
		points[a] = (t_proj *)malloc(sizeof(t_proj) * height);
		while (++b < height)
		{
			X = (float) b * 8.66 - a * 8.66;
			points[a][b].x = X;
			Y = (float) a * 5 + b * 5 - grid[a][b];
			points[a][b].y = Y;
			//printf("grid[%d][%d]\tX = %f & Y = %f\npoints[a][b].x = %f\n", a, b, X, Y,points[a][b].x);
			//if (grid[a][b] == 0)
			//	draw_pixel(mlx_ptr, win_ptr,  500 + X, 100 + Y, 0xffff00);
			//else
			//	draw_pixel(mlx_ptr, win_ptr, 500 + X, 100 + Y, 0xf00000);
		}
	}
//	connect_dots(points, )
	mlx_mouse_hook(win_ptr, deal_key, specs);
	close(fd);
	mlx_loop(mlx_ptr);
	return (0);
}
