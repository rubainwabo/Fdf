/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 20:41:23 by rkamegne          #+#    #+#             */
/*   Updated: 2018/12/17 18:10:03 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxd.h"

t_mouse		*ft_mouse_new(int x, int y)
{
	t_mouse		*new;

	if(!(new = (t_mouse*)malloc(sizeof(*new))))
		return (0);
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}
