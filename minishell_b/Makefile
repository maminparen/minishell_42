# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 16:20:28 by cdarrell          #+#    #+#              #
#    Updated: 2021/11/20 14:33:22 by cdarrell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell_bonus

SRC =	buildin/buildin.c	buildin/cd.c	buildin/cd2.c	buildin/echo.c	buildin/exit.c	buildin/export_unset.c	buildin/utils.c	\
		execute/create_new_env.c	execute/execute.c	execute/execute_utils.c	execute/find_fdin_from_stdin.c	execute/do_our.c	execute/execute_help.c	execute/find_fdin_fdout.c	\
		../minishell_b/src/main/main.c	../minishell_b/src/main/sh_all_check_line.c \
		pars/pars.c	pars/pars_env.c	pars/pars_list_cmd.c	pars/pars_list_fd.c	pars/pars_list_qoute_dollar.c	pars/pars_check_line.c	pars/pars_list_access_cmd.c	pars/pars_list_cmd_split.c	pars/pars_list_qoute.c	pars/pars_utils.c	\
		term/allmove.c	term/forline.c	term/initdata.c	term/lstutils.c	term/putcharutils.c	term/delete.c	term/free.c	term/history.c	term/input.c	term/memutils.c	term/termcap.c	\
		utils/ft_list_2val.c utils/minishell_utils.c utils/gnl.c \
		../minishell_b/src/wildcard/parsestar.c	../minishell_b/src/wildcard/star.c      ../minishell_b/src/wildcard/starutils.c \
		../minishell_b/src/bonus/free_sh_all.c       ../minishell_b/src/bonus/main_bonus.c         ../minishell_b/src/bonus/pars_sh_all.c        ../minishell_b/src/bonus/pass_skobka.c        ../minishell_b/src/bonus/sh_all_split.c       ../minishell_b/src/bonus/sh_all_split_norma.c

SRCS_DIR = ../src/

OBJS = ${addprefix ${SRCS_DIR}, ${SRC:.c=.o}}

HEADER = include/minishell.h include/termcap.h include/wildcard.h

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

%.o:%.c		${HEADER}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADER}
			@make -C ../libft/ all
			@${CC}	${OBJS} ../libft/libft.a -ltermcap -o ${NAME}
			@echo "minishell_bonus compiled successfully!"

all:		${NAME}

clean:		
			@make -C ../libft/ clean
			@${RM} ${OBJS}
			@echo "fclean successfully!"

fclean:		
			@make -C ../libft/ fclean
			@${RM} ${OBJS} ${NAME}
			@echo "fclean successfully!"

re: fclean all

.PHONY: all clean fclean re bonus
