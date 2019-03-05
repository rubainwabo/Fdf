# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 18:23:24 by rkamegne          #+#    #+#              #
#    Updated: 2019/01/29 17:09:02 by rkamegne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRC=event_handling.c ft_draw_line.c ft_get_color.c ft_window_finish.c\
	ft_scale_offset.c main.c ft_process_file.c image_creation.c matrix_ops.c\
	ft_secure.c

OBJECTS=event_handling.o ft_draw_line.o ft_get_color.o ft_window_finish.o\
		ft_scale_offset.o main.o ft_process_file.o image_creation.o matrix_ops.o\
		ft_secure.o

HEADERS=fdf.h minilibx_macos/mlx.h

LIBRARIES=-L minilibx_macos -lmlx -L libft -lft

FRAMEWORKS=-framework OpenGl -framework Appkit

all: $(NAME)

$(NAME):
	#Compiling
	gcc -Wall -Wextra -Werror -o $(NAME) $(SRC) $(LIBRARIES) $(FRAMEWORKS)

clean:
	#Cleaning
	@/bin/rm -f $(OBJECTS)

fclean: clean
	#Fcleaning
	@/bin/rm -f $(NAME)

re: fclean all

PHONY : fclean clean all re
