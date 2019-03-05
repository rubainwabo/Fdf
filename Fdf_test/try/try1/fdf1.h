/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:56:59 by krutten           #+#    #+#             */
/*   Updated: 2019/01/03 18:06:54 by krutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct		s_proj
{
	float			x;
	float			y;
}					t_proj;
typedef struct		s_line
{
	char			**line;
	struct s_line	*next;
}					t_line;
t_line	*ft_line_new(char **input);
int		**ft_process_file(int fd, int *width, int *height);
#endif
