/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:40:19 by krutten           #+#    #+#             */
/*   Updated: 2019/01/02 16:17:42 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*ft_line_new(char **input)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line *));
//	new->line = (char *)malloc(ft_strlen(input) + 1);
//	ft_strncpy(new->line, input, ft_strlen(input));
	new->line = input;
	new->next = NULL;
	//puts("++ALLOCATED++");
	return (new);
}
