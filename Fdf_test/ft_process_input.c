/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:07:15 by rkamegne          #+#    #+#             */
/*   Updated: 2018/12/21 17:46:21 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_strlen_zer(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str != ' ')
			i++;
		str++;
	}
	return (i);
}

int		ft_process_input(int fd)
{
	char	*line;
	char	*buffer;
	int		ret;
	int		nb_line;
	int		len;

	buffer = NULL;
	nb_line = 0;
	len = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		nb_line++;
		if (!buffer)
			buffer = ft_strdup(line);
		if(ft_strlen_zer(buffer) != ft_strlen_zer(line))
			return (0);
		buffer = ft_strdup(line);
	}
	ft_putstr("Number of lines : ");
	ft_putnbr(nb_line);
	ft_putchar('\n');
	len = ft_strlen_zer(line);
	ft_putstr("len of each line : ");
	ft_putnbr(len);
	ft_putchar('\n');
	return (1);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	if (ft_process_input(fd))
		ft_putendl("OK!");
	else
		ft_putendl("Invalid file");
	close(fd);
	return (0);
}
