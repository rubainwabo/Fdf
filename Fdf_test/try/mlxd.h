/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:44:49 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/21 16:23:26 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXD_H
# define MLXD_H
# include <stdlib.h>
# define MAX(x, y) ((x >= y) ? x : y)
# define MIN(x, y) ((x <= y) ? x : y)
#define  ABS(x) ((x >= 0) ? x : -x)
#include "mlx.h"
#include "fdf.h"

typedef float		Point[3];
typedef float		Face[8];

typedef struct		s_mouse
{
	int				x;
	int				y;
	struct s_mouse	*next;
}					t_mouse;
typedef	struct		s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_mouse			*mouse;
	struct s_param	*next;
}					t_param;
t_param				*ft_param_new(void *mlx_ptr, void *win_ptr, t_mouse *mouse);
t_mouse				*ft_mouse_new(int x, int y);
void				ft_mouse_add(t_mouse **start, t_mouse *elt);
void				draw_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color);
#endif
