/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:56:59 by krutten           #+#    #+#             */
/*   Updated: 2019/01/29 18:03:36 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "libft/libft.h"
# define PI 3.14159
# define HEIGHT 1300
# define WIDTH 2600
# define MAX(x, y) ((x >= y) ? x : y)
# define MIN(x, y) ((x <= y) ? x : y)
# include "minilibx_macos/mlx.h"

typedef	struct		s_line
{
	char			**line;
	struct s_line	*next;
}					t_line;
typedef struct		s_array
{
	float			output[4];
	int				colour[12];
}					t_array;
typedef struct		s_reading
{
	t_line			*rdr;
	int				i;
	int				j;
	int				k;
	int				count;
	t_line			*head;
}					t_reading;
typedef	struct		s_vectorstruct
{
	float			x;
	float			y;
	float			z;
}					t_vector;
typedef struct		s_matrix
{
	float			m[3][3];
}					t_mat;
typedef struct		s_matspecs
{
	float			alpha;
	float			beta;
	int				proj;
	int				displace_x;
	int				displace_y;
	float			zoom;
	float			alt;
	int				coloured;
	int				colour_low;
	int				colour_high;
}					t_matspecs;

typedef struct		s_hook
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				***grid;
	int				width;
	int				height;
	int				coloured;
	t_matspecs		specs;
}					t_hook;
typedef struct		s_proj
{
	float			x;
	float			y;
	int				color;
}					t_proj;
typedef struct		s_draw
{
	int				x;
	int				y;
	int				cumul;
	int				dx;
	int				dy;
	int				color;
	int				xinc;
	int				yinc;
	double			percentage;
}					t_draw;
t_hook				*ft_hook_new(void *mlx_ptr, void *win_ptr, int ***grid);
void				ft_draw_circle(void *mlx_ptr, void *win_ptr, int ray);
void				ft_draw_line(char *image_str, t_proj start_pt,
					t_proj end_pt);
int					ft_get_color(int color1, int color2, double pourcentage);
void				draw_line(char *image_str, int x0, int y0, int x1, int y1,
					int color);
int					***ft_process_file(int fd, t_hook *specs);
t_mat				matrix_matrix_multiply(t_mat a, t_mat b);
t_vector			vector_matrix_multiply(t_vector one, t_mat matrix);
void				print_mat(t_mat matrix);
t_mat				rotation_matrix_x(float angle);
t_mat				rotation_matrix_y(float angle);
t_mat				rotation_matrix_z(float angle);
void				ft_window_finish(void *mlx_ptr, void *win_ptr);
void				ft_draw_line(char *image_str, t_proj start_pt,
					t_proj end_pt);
int					deal_key(int key, void *param);
int					draw_image(void *mlx_ptr, void *win_ptr, t_hook *par);
int					deal_mouse(int button, int x, int y, void *param);
int					ft_get_color(int color1, int color2, double percentage);
void				scale_and_offset(t_proj **points, int height, int width);
void				manipulate_colours(t_hook *par);
t_proj				**project_points(int ***grid, int height, int width,
					t_matspecs specs);
void				colour_circle(t_array *array);
t_proj				**malloc_project_pts(int height, int width);
void				free_3darray(int ***arr, int i, int j, int k);
int					ft_checker(char *line);
int					ft_throwError_main(int fd, t_hook *par, void *mlx_ptr, void *win_ptr);
#endif
