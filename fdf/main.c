/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:06:24 by krutten           #+#    #+#             */
/*   Updated: 2019/01/29 18:44:35 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void		connect_dots(char *image_str, t_proj **points, int width,
		int height)
{
	int		i;
	int		j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (j + 1 < width)
				ft_draw_line(image_str, points[i][j], points[i][j + 1]);
			if (i + 1 < height)
				ft_draw_line(image_str, points[i][j], points[i + 1][j]);
		}
	}
}

int			draw_image(void *mlx_ptr, void *win_ptr, t_hook *par)
{
	void	*image_ptr;
	int		specs[3];
	char	*image_str;
	t_proj	**points;

	image_ptr = mlx_new_image(mlx_ptr, WIDTH - 500, HEIGHT - 200);
	image_str = mlx_get_data_addr(image_ptr, &specs[0], &specs[1], &specs[2]);
	manipulate_colours(par);
	if (!(points = project_points(par->grid,
			par->height, par->width, par->specs)))
		return (-1);
	connect_dots(image_str, points, par->width, par->height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, image_ptr, 10, 10);
	mlx_destroy_image(mlx_ptr, image_ptr);
	return (0);
}

t_hook		*ft_hook_new(void *mlx_ptr, void *win_ptr, int ***grid)
{
	t_hook	*new;

	if (!(new = (t_hook*)malloc(sizeof(t_hook))))
		return (NULL);
	new->win_ptr = win_ptr;
	new->mlx_ptr = mlx_ptr;
	new->grid = grid;
	new->specs.proj = 1;
	new->specs.zoom = 1;
	new->specs.alpha = 0;
	new->specs.coloured = 0;
	new->specs.beta = 0;
	new->specs.displace_x = 0;
	new->specs.displace_y = 0;
	new->specs.alt = 1;
	new->specs.colour_low = 0xffffff;
	new->specs.colour_high = 0x00ff00;
	return (new);
}

static int	ft_throw_error(int fd, t_hook *par, void *mlx_ptr, void *win_ptr)
{
	if (!(par->grid = ft_process_file(fd, par)))
	{
		ft_putendl("Map error");
		return (0);
	}
	if (draw_image(mlx_ptr, win_ptr, par) < 0)
	{
		ft_putendl("Error");
		return (0);
	}
	return (1);
}

int			main(int ac, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_hook	*param;
	int		fd;

	if (ac != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("usage: ./fdf some_map.fdf");
		return (0);
	}
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (!(param = ft_hook_new(mlx_ptr, win_ptr, NULL)))
	{
		ft_putendl("Error");
		return (0);
	}
	if (!(ft_throw_error(fd, param, mlx_ptr, win_ptr)))
		return (0);
	ft_window_finish(mlx_ptr, win_ptr);
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_mouse_hook(win_ptr, deal_mouse, param);
	close(fd);
	mlx_loop(mlx_ptr);
	return (0);
}
