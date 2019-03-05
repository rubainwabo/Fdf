/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:56:59 by krutten           #+#    #+#             */
/*   Updated: 2019/01/03 16:48:40 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;
typedef struct		s_line
{
	char			**line;
	struct s_line	*next;
}					t_line;
t_line	*ft_line_new(char **input);
t_coord	*ft_process_file(int fd, int *nb);
#endif
