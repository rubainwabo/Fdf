/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 04:11:11 by krutten           #+#    #+#             */
/*   Updated: 2019/01/29 19:18:26 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_line	*ft_line_new(char **input)
{
	t_line		*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->line = input;
	new->next = NULL;
	return (new);
}

static int		build_grid1(int ***grid, t_line *head)
{
	t_reading	read;

	read.rdr = head;
	read.count = 0;
	while (read.rdr->line[read.count])
		read.count++;
	read.i = -1;
	while (read.rdr)
	{
		if (!(grid[++read.i] = (int **)malloc(sizeof(int *) * read.count)))
		{
			free_3darray(grid, read.i, 0, 2);
			return (-1);
		}
		read.j = 0;
		while (read.j < read.count)
			read.j++;
		if (read.j != read.count)
			return (-1);
		read.rdr = read.rdr->next;
	}
	return (read.count);
}

int				build_grid(int ***grid, t_line *head)
{
	t_reading	read;

	read.rdr = head;
	if ((read.count = build_grid1(grid, head)) < 0)
		return (-1);
	read.i = 0;
	while (read.rdr)
	{
		read.j = -1;
		while (++read.j < read.count)
		{
			if (!(grid[read.i][read.j] = (int *)malloc(sizeof(int) * 2)))
			{
				free_3darray(grid, read.i, read.j, 1);
				return (-1);
			}
			grid[read.i][read.j][0] =
				ft_atoi_base(ft_strdup_at(read.rdr->line[read.j], 'x'), 16);
			grid[read.i][read.j][1] = ft_atoi(read.rdr->line[read.j]);
		}
		read.rdr = read.rdr->next;
		read.i++;
	}
	return (read.count);
}

t_line			*build_ch_list(int fd, int *i)
{
	t_reading	read;
	char		*line;

	*i = 0;
	read.head = NULL;
	while (get_next_line(fd, &line))
	{
		(*i)++;
		if (!ft_checker(line))
			return (NULL);
		if (!read.head)
		{
			if (!(read.head = ft_line_new(ft_strsplit(line, ' '))))
				return (NULL);
			read.rdr = read.head;
		}
		else
		{
			if (!(read.rdr->next = ft_line_new(ft_strsplit(line, ' '))))
				return (NULL);
			read.rdr = read.rdr->next;
		}
		free(line);
	}
	return (read.head);
}

int				***ft_process_file(int fd, t_hook *specs)
{
	int			***grid;
	int			i[3];
	t_reading	read;

	read.j = -1;
	if (!(read.head = build_ch_list(fd, &(i[0]))))
		return (NULL);
	if (!(grid = (int ***)malloc(sizeof(int **) * i[0])))
		return (NULL);
	specs->height = i[0];
	if ((specs->width = build_grid(grid, read.head)) < 0)
		return (NULL);
	while (++read.j < specs->height)
	{
		read.k = -1;
		while (++read.k < specs->width)
		{
			if (grid[read.j][read.k][0] != 0)
				specs->specs.coloured = 1;
		}
	}
	return (grid);
}
