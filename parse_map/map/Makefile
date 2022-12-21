NAME = parsing_test

SRC = map.c parse_map.c ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
MLX = -L../mlx -lmlx -framework OpenGL -framework Appkit

CC = cc
RM = rm -rf

# LFT = ../libft/libft.a
# # INC = -Ilibft
LIB = -L../libft -lft

all : $(LFT) $(NAME)

# $(LFT):
# 	# $(MAKE) -s -C libft bonus


$(NAME) : $(OBJ)
	make -C ../mlx/
	$(CC) $(CFLAGS) $(MLX) -o $(NAME) $(OBJ) $(LIB)

clean :
	$(RM) $(OBJ)

fclean : clean
	make -C ../mlx/ clean
	$(RM) $(NAME)

re : fclean all
