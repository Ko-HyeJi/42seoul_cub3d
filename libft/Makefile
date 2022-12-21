# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 18:58:22 by hyko              #+#    #+#              #
#    Updated: 2022/01/18 00:16:54 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAG = -Wall -Wextra -Werror

RM = rm -rf

INCLUDE = ./libft.h

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c \
		ft_strlen.c ft_strncmp.c ft_strlcpy.c \
		ft_strlcat.c ft_strnstr.c ft_strchr.c ft_strrchr.c \
		ft_bzero.c ft_atoi.c ft_memchr.c ft_memcmp.c ft_memset.c \
		ft_memcpy.c ft_memmove.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c \
		ft_striteri.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		
SRC_BN = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c

%.o : %.c
	$(CC) $(CFLAG) -c $^ -o $@

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BN:.c=.o)

all : $(NAME)
	
$(NAME) : $(OBJ)
	ar rc $@ $^	

clean : 
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

bonus : $(OBJ) $(OBJ_BONUS)
	ar rc $(NAME) $^	

.PHONY : all clean fclean re bonus
