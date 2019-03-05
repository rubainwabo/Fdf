/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:42:25 by rkamegne          #+#    #+#             */
/*   Updated: 2018/11/24 14:46:38 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_err(const char *str)
{
	size_t	i;

	i = 0;
	while (str && *str)
	{
		i++;
		str++;
	}
	return (i);
}
