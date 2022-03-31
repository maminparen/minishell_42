# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/13 20:39:11 by crow              #+#    #+#              #
#    Updated: 2021/10/08 15:55:35 by cdarrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
HEADER		:=	libft.h

CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra

SRC			:=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
 
SRC_B		:=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c 

OBJ_DIR 	:=	obj/

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_B		=	$(addprefix $(OBJ_DIR), $(SRC_B:.c=.o))

RM_DIR		:=	rm -rf
RM_FILE		:=	rm -f

LIBC		:=	ar -rcs

${NAME}:	${OBJ}
			${LIBC} ${NAME} ${OBJ}

all: 		$(NAME)

bonus:		${OBJ} $(OBJ_B)
			${LIBC} ${NAME} ${OBJ} $(OBJ_B)
	
$(OBJ): 	| $(OBJ_DIR)
$(OBJ_B): 	| $(OBJ_DIR)			

$(OBJ_DIR):
			mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(HEADER) Makefile
			${CC} $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
		${RM_DIR} ${OBJ_DIR}

fclean:	clean
		${RM_FILE} $(NAME)

re:		fclean all

.PHONY: all clean fclean re bonus
