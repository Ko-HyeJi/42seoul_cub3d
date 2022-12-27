NAME = cub3D

CC 			=	cc
CC_M1 		=	arch -x86_64 cc
CCFLAGS		=	-Wall -Wextra -Werror#-g3 -fsanitize=address

SRC			=	main.c \
				minimap.c \
				playeronmap.c \
				draw_ray.c \
				key.c \
				get_next_line.c \
				get_next_line_util.c \
				3d_render.c \
				# parse_map.c \
				map_info.c
				
OBJ	=	$(SRC:.c=.o)

LIBFT_PATH = ../libft
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH)

#I : 헤더파일 검색
MLX_PATH = ../mlx
MLX_FLAGS	=	-I$(MLX_PATH) -L$(MLX_PATH) -lmlx -framework OpenGL -framework Appkit

# libft make 먼저 해야되는데 잘 안돼서 일단 수동으로 make 해주는중 수정 필수!!! (hyko) 
# LIB = -L../libft -lft

all	:	$(NAME)

.c.o	:
	$(CC) $(CCFLAGS) -c $< -o $@
#	$(CC_M1) $(CCFLAGS) -c $< -o $@
	
$(NAME)	: $(OBJ)
#	make all -C $(LIBFT_PATH)
#	make all -C $(MLX_PATH)
	$(CC) $(CCFLAGS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(OBJ) -o $(NAME)
#	$(CC_M1) $(CCFLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

clean	:
#	make clean -C $(LIBFT_PATH)
#	make clean -C $(MLX_PATH)
	$(RM) $(OBJ)

fclean	: clean
#	make fclean -C $(LIBFT_PATH)
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