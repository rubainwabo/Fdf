/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:50:31 by rkamegne          #+#    #+#             */
/*   Updated: 2019/01/29 19:06:52 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_checker(char *line)
{
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (!ft_isdigit(line[i]) && !ft_ispace(line[i]) && line[i] != 'x' &&
			(line[i] < 'a' || line[i] > 'f') && (line[i] < 'A' || line[i] > 'F')
			&& line[i] != '+' && line[i] != '-' && line[i] != ',')
			return (0);
	}
	return (1);
}
void	free_3darray(int ***arr, int i, int j, int k)
{
	if (k == 1)
	{
		while (--i >= 0)
		{
			while (--j >= 0)
				free(arr[i][j]);
			free(arr[i]);
		}
		free(arr);
	}
	else
	{
		while (--i >= 0)
			free(arr[i]);
		free(arr);
	}
}

static void	free_2darray(t_proj **pts, int i)
{
	while (--i >= 0)
		free(pts[i]);
	free(pts);
}

t_proj	**malloc_project_pts(int height, int width)
{
	int			a;
	t_proj		**pts;

	a = -1;
	if (!(pts = (t_proj **)malloc(sizeof(t_proj *) * height)))
		return (NULL);
	while (++a < height)
	{
		if (!(pts[a] = (t_proj *)malloc(sizeof(t_proj) * width)))
		{
			free_2darray(pts, a);
			return (NULL);
		}
	}
	return (pts);
}
