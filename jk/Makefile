NAME = cub3D

CC 			=	cc
CC_M1 			=	arch -x86_64 cc
CCFLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c \
				minimap.c \
				playeronmap.c \
				draw_ray.c \
				key.c \
				map_parse.c \
				get_next_line.c \
				get_next_line_util.c
				
OBJ	=	$(SRC:.c=.o)
MLX_FLAGS	=	-I. -L../mlx -lmlx -framework OpenGL -framework Appkit

all	:	$(NAME)

.c.o	:
	 $(CC) $(CCFLAGS) -c $< -o $@
#	$(CC_M1) $(CCFLAGS) -c $< -o $@
#  $(CC) $(CCFLAGS) $(MLX_FLAGS) -c $< -o $@
	
$(NAME)	: $(OBJ)
	$(CC) $(CCFLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)
#	$(CC_M1) $(CCFLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re	:	
		make fclean 
		make all

.PHONY	:	all clean fclean re