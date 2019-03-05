/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:42:30 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/21 16:30:17 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxd.h"

t_param		*ft_param_new(void *mlx_ptr, void *win_ptr, t_mouse *mouse)
{
	t_param		*new;

	new = (t_param*)malloc(sizeof(t_param));
	new->mlx_ptr = mlx_ptr;
	new->win_ptr = win_ptr;
	new->mouse = mouse;
	new->next = NULL;
	return (new);
}
