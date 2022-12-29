NAME = cub3D

CC 			=	cc
CCFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

SRC			=	main.c \
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
				
OBJ	=	$(SRC:.c=.o)

LIBFT_PATH = ../libft
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

#I : 헤더파일 검색
MLX_PATH = ../mlx
MLX_FLAGS	=	-I$(MLX_PATH) -L$(MLX_PATH) -lmlx -framework OpenGL -framework Appkit

# libft make 먼저 해야되는데 잘 안돼서 일단 수동으로 make 해주는중 수정 필수!!! (hyko) 
# LIB = -L../libft -lft

all	:	$(NAME)
	
.c.o	:
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME)	: $(OBJ)
	make all -C $(LIBFT_PATH)
#	make all -C $(MLX_PATH)
	$(CC) $(CCFLAGS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(OBJ) -o $(NAME)

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
