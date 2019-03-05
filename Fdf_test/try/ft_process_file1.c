/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:49:02 by krutten           #+#    #+#             */
/*   Updated: 2019/01/03 22:50:19 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			build_grid(int **grid, t_line *head)
{
	t_line		*reader;
	int			j;
	int			k;
	int			count;

	reader = head;
	count = 0;
	j = 0;
	while (reader->line[j++])
			count++;
	j = 0;
	while (reader)
	{
		grid[j] = (int *)malloc(sizeof(int *) * count);
		k = -1;
		while (++k < count)
			grid[j][k] = ft_atoi(reader->line[k]);
		reader = reader->next;
		j++;
	}
	return (count);
}

int			**ft_process_file(int fd, int *width, int *height)
{
	int		**grid;
	char	*line;
	int		i;
	int		j;
	int		l;
	t_line	*head;
	t_line	*reader;
	int		count;
//	int		x;
//	int		y;
	int		k;
//	t_coord *coord;

	i = 0;
	head = NULL;
	//printf("-------ARRIVED IN PROCESS_FILE -----\nopened fd = %d\n", fd);
	while (get_next_line(fd, &line))
	{
		//printf("++fetching line++\n%s\n", line);
		i++;
		if (!head)
		{
			head = ft_line_new(ft_strsplit(line, ' '));
			reader = head;
		}
		else
		{
			reader->next = ft_line_new(ft_strsplit(line, ' '));
			reader = reader->next;
		}
		free (line);
	}
	grid = (int **)malloc(sizeof(int **) * i);
	*width = i;
	count = build_grid(grid, head);
	*height = count;
//	printf("i * count = %d\n", i * count);
/*	coord = (t_coord *)malloc(sizeof(t_coord *) * i);
	l = -1;
	k = 0;
	x = 100;
	y = 100;
	while (++l < i)
	{
		j = -1;
		while (++j < count)
		{
			printf("%d\t",grid[l][j]);
			coord[k].x = x;
			coord[k].y = y;
			coord[k].z = grid[l][j];
			k++;
			x = x + 50;	
		}
		x = 100;
		y = y + 50;
		puts("");
	}
	k = -1;
	while (++k < i * count)
	{
		printf("x = %d & y = %d & z = %d  ", coord[k].x, coord[k].y, coord[k].z);
		printf("\n");
		if (k != 0 && (k + 1) % 19 == 0)
			printf("\n");
	}*/
	return (grid);
}

/*int			main(int argc, char **argv)
{
	int		fd;

	if (argc < 2)
	{
		puts("usage: ./fdf map1 map2 map3 ...");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	ft_process_file(fd);
	close (fd);
}*/
