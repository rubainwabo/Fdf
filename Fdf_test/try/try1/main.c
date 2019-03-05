/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:03:03 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/21 16:22:49 by rkamegne         ###   ########.fr       */
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

void	draw_line_special (void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
	int x, y, dx, dy, xi, yi, xf, yf;
	double a, b;

	xi = MIN(x1, x2);
	xf = MAX(x1, x2);
	yi = MIN(y1, y2);
	yf = MAX(y1, y2);
	dx = xf - xi;
	dy = yf - yi;
	a = (double) (dy / dx);
	b = yi - a * xi;
	x = xi;
	while (x <= xf)
	{
		y = (int) (a * x + b);
		draw_pixel(mlx_ptr, win_ptr, x, y, color);
		x++;
	}
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

void	draw_triangle(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int x3, int y3)
{
	draw_line(mlx_ptr, win_ptr, x1, y1, x2, y2, 0xff00);
	//draw_line(mlx_ptr, win_ptr, x1, y1, x3, y3, 0xff00);
	draw_line(mlx_ptr, win_ptr, x2, y2, x3, y3, 0xff00);
}

int		deal_key(int button, int x, int y,  void *param)
{
	t_param		*local;
	t_mouse		*elt;

	local = (t_param *)param;
	elt = ft_mouse_new(x, y);
	if (local->mouse != NULL)
	{
		printf("HI\n");
		ft_mouse_add(&(local->mouse), elt);
		printf("local->mouse->next->x, y : %d, %d, local->mouse->x, y, %d, %d\n", local->mouse->next->x, local->mouse->next->y, local->mouse->x, local->mouse->y);
		draw_line(local->mlx_ptr, local->win_ptr,local->mouse->next->x, local->mouse->next->y, local->mouse->x, local->mouse->y, 0x90ee90);
	//	local->mouse = NULL;
	}
	else
	{
		printf("MIDDLE\n");
		local->mouse = elt;
		draw_pixel(local->mlx_ptr, local->win_ptr, elt->x, elt->y, 0x90ee90);
      //  draw_line(local->mlx_ptr, local->win_ptr, 10, 10, local->mouse->x, local->mouse->y, 0xffff00);	
	}
	//draw_pixel(local->mlx_ptr, local->win_ptr, x, y, 0xffff00);
//	draw_line1(local->mlx_ptr, local->win_ptr, 200, 200, x, y, 0xffff00);
	return (0);
}


int		main(int ac, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_mouse *mouse;
	t_param	*specs;
	t_coord *coord;
	int		fd;
	int		i;
	float	X;
	float	Y;
	int		number_points;

	i = -1;
	number_points = 0;
	fd = open(argv[1], O_RDONLY);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1200, 1200, "fdf");
	mouse = NULL;
	specs = ft_param_new(mlx_ptr, win_ptr, mouse);
	coord = ft_process_file(fd, &number_points);
	printf("number of points : %d\n", number_points);
	while (++i < number_points)
	{
		X = (float) coord[i].x * 0.5 - 0.5 * coord[i].y;
		Y = (float) coord[i].z + coord[i].x *  0.5 / 2 + coord[i].y * 0.5 / 2;
		printf("X = %f & Y = %f\n", X, Y);
		if (coord[i].z > 0)
			draw_pixel(mlx_ptr, win_ptr, X + 500, Y + 300, 0xc5c5c);
		else
			draw_pixel(mlx_ptr, win_ptr, X + 500, Y + 300, 0xffff00);
	}
//	draw_line(mlx_ptr, win_ptr, 0, 20, 250, 250, 0xffff00);
//	mlx_string_put(mlx_ptr, win_ptr, 125, 250, 0xFFFFFF, "Screen saver");
/*	float		cube[8][2];
	Point corners[8] = {
		 { 1, -1, -5}, 
         { 1, -1, -3}, 
         { 1,  1, -5}, 
         { 1,  1, -3}, 
         {-1, -1, -5}, 
         {-1, -1, -3}, 
         {-1,  1, -5}, 
         {-1,  1, -3} 
	};


	int		i = 0;
	while (i < 8)
	{
		float x_proj = corners[i][0] / -corners[i][2];
		float y_proj = corners[i][1] / -corners[i][2];
		float x_proj_remap = (1 + x_proj) / 2;
		float y_proj_remap = (1 + y_proj) / 2;
		float x_proj_pix = x_proj_remap * 100;
		float y_proj_pix = y_proj_remap * 100;
		cube[i][0] = x_proj_pix;
		cube[i][1] = y_proj_pix;
	    printf("corner: %d x:%f y:%f\n", i, cube[i][0], cube[i][1]);
	    i++;
	}

	Face sides[6] =
	{
		{cube[5][0], cube[5][1], cube[1][0], cube[1][1], cube[7][0], cube[7][1], cube[3][0], cube[3][1]},
		{cube[4][0], cube[4][1], cube[5][0], cube[5][1], cube[6][0], cube[6][1], cube[7][0], cube[7][1]},
		{cube[4][0], cube[4][1], cube[0][0], cube[0][1], cube[6][0], cube[6][1], cube[2][0], cube[2][1]},
		{cube[1][0], cube[1][1], cube[0][0], cube[0][1], cube[3][0], cube[3][1], cube[2][0], cube[2][1]},
		{cube[5][0], cube[5][1], cube[1][0], cube[1][1], cube[4][0], cube[4][1], cube[0][0], cube[0][1]},
		{cube[7][0], cube[7][1], cube[3][0], cube[3][1], cube[6][0], cube[6][1], cube[2][0], cube[2][1]}
	};


	i = 0;
	while (i < 6)
	{
		draw_triangle(mlx_ptr, win_ptr, sides[i][0], sides[i][1], sides[i][4], sides[i][5], sides[i][6], sides[i][7]);
		draw_triangle(mlx_ptr, win_ptr, sides[i][0], sides[i][1], sides[i][2], sides[i][3], sides[i][6], sides[i][7]);
		printf("Triangle %d : sides[%d][0] = %f, sides[%d][1] = %f, sides[%d][4] = %f, sides[%d][5] = %f, sides[%d][6] = %f, sides[%d][7] = %f\n", i + 1, i, sides[i][0], i
			, sides[i][1], i, sides[i][4], i, sides[i][5], i, sides[i][6], i, sides[i][7]);
		printf("Triangle %d' : sides[%d][0] = %f, sides[%d][1] = %f, sides[%d][2] = %f, sides[%d][3] = %f, sides[%d][6] = %f, sides[%d][7] = %f\n", i + 1, i, sides[i][0], i
			, sides[i][1], i, sides[i][2], i, sides[i][3], i, sides[i][6], i, sides[i][7]);

		i++;
	}
	while (i < 8)
	{
		//draw_triangle(mlx_ptr, win_ptr, cube[i][0], cube[i][1], cube[i + 1][0], cube[i + 1][1], cube[i + 2][0], cube[i + 2][1], 0xffff00);
		draw_pixel(mlx_ptr, win_ptr, cube[i][0], cube[i][1], 0xffff00);
		i++;
	}*/
	mlx_mouse_hook(win_ptr, deal_key, specs);
	close(fd);
	mlx_loop(mlx_ptr);
	return (0);
}
