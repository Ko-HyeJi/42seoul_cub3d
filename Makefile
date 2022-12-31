NAME = cub3D

CC 			=	cc
CCFLAGS		=	-Wall -Wextra -Werror #-g3 -fsanitize=address

SRC_PATH	=	jk
SRC_FILE	=	main.c \
				minimap.c \
				player_main.c \
				player_util.c \
				draw_ray.c \
				key_mouse.c \
				get_next_line.c \
				get_next_line_util.c \
				3d_render.c \
				texture.c \
				init.c \
				init2.c \
				ray_calculation.c \
				util.c \
				ray_util.c \
				loop_hook.c \
				parse_map.c \
				get_map_info.c \
				set_map_info.c \
				check_map.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILE))		
OBJ	=	$(SRC:.c=.o)

LIBFT_PATH = libft
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

MLX_PATH = mlx
MLX_FLAGS	=	-I$(MLX_PATH) -L$(MLX_PATH) -lmlx -framework OpenGL -framework Appkit

all	:	$(NAME)
	
.c.o	:
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	make all -C $(LIBFT_PATH)
#	make all -C $(MLX_PATH)
	$(CC) $(CCFLAGS) -I/$(SRC_PATH) $(MLX_FLAGS) $(LIBFT_FLAGS) $(OBJ) -o $(NAME)

clean	:
	make clean -C $(LIBFT_PATH)
#	make clean -C $(MLX_PATH)
	$(RM) $(OBJ)

fclean	: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re	:	
		make fclean 
		make all

.PHONY	:	all clean fclean re#bonus 추가

# ifdef	WITH_BONUS
# 	OBJECTS	=	$(OBJS_B)
# else
# 	OBJECTS	=	$(OBJS)
# endif

# bonus	:
# 	make WITH_BONUS=1 all
