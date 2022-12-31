NAME = cub3D
# BONUS = cub3D_bonus

CC 			=	cc
CCFLAGS		=	-Wall -Wextra -Werror #-g3 -fsanitize=address
	
.c.o	:
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@ 

SRC_PATH	=	src
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

SRC_BN_PATH	=	src_bonus
SRC_BN_FILE	=	main_bonus.c \
				minimap_bonus.c \
				player_main_bonus.c \
				player_util_bonus.c \
				draw_ray_bonus.c \
				key_mouse_bonus.c \
				get_next_line_bonus.c \
				get_next_line_util_bonus.c \
				3d_render_bonus.c \
				texture_bonus.c \
				init_bonus.c \
				init2_bonus.c \
				ray_calculation_bonus.c \
				util_bonus.c \
				ray_util_bonus.c \
				loop_hook_bonus.c \
				parse_map_bonus.c \
				get_map_info_bonus.c \
				set_map_info_bonus.c \
				check_map_bonus.c
SRC_BN = $(addprefix $(SRC_BN_PATH)/, $(SRC_BN_FILE))		
OBJ_BN	=	$(SRC_BN:.c=.o)

LIBFT_PATH = libft
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

MLX_PATH = mlx
MLX_FLAGS	=	-I$(MLX_PATH) -L$(MLX_PATH) -lmlx -framework OpenGL -framework Appkit

INC = -Iinclude -Iinclude_bonus

ifdef 	WITH_BONUS
	OBJECT = $(OBJ_BN)
else
	OBJECT = $(OBJ)
endif

$(NAME) : $(OBJECT)
	make all -C $(LIBFT_PATH)
	make all -C $(MLX_PATH)
	$(CC) $(CCFLAG) $(INC) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@ $^

all	:	$(NAME)

bonus :
	$(MAKE) WITH_BONUS=1 all

clean	:
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX_PATH)
	$(RM) $(OBJ) $(OBJ_BN)

fclean	: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME) $(BONUS)

re	:	
		make fclean 
		make all

.PHONY	:	all clean fclean re bonus
