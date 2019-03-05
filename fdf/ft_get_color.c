/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:36:00 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/26 21:16:02 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		ft_get_color(int color1, int color2, double percentage)
{
	int		green;
	int		blue;
	int		red;

	red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, percentage);
	green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, percentage);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
