NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

MLX = mlx

LXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRCS = cub3d.c parse.c parse_tools.c tools.c \
	  gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(MLX) $(OBJS)
		$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LXFLAGS)

$(MLX) : 
		@$(MAKE) -C mlx

clean:
	rm -rf *.o

fclean:		 clean
				rm -rf $(NAME)

re: fclean all

test: re
		./$(NAME) map/map.cub
