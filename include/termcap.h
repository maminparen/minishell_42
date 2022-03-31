/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:05:00 by hzona             #+#    #+#             */
/*   Updated: 2021/11/19 16:59:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_H
# define TERMCAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <term.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_history
{
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}t_history;

typedef struct s_line
{
	size_t				width;
	size_t				height;
	struct termios		term;
	struct winsize		window_size;
	char				buf[6];
	char				*line;
	char				*tmp;
	size_t				line_size;
	char				*name;
	size_t				name_size;
	size_t				cursor_pos;
	size_t				coord_x;
	size_t				coord_y;
	int					sigint_flag;
	t_history			*free_history;
}t_line;

t_line			*g_data;

char		*ft_termcap(t_history **history, t_list_2val *env);
t_line		*init_data(t_history **history);
void		sigint_start(int first);
void		init_cursor(t_line *data);

t_history	*ft_lstnew_2(char *str);
int			ft_lstsize_2(t_history *lst);
void		ft_lstadd_front_2(t_history **lst, t_history *new2);

int			ft_putchar_int(int c);

void		left_move(t_line *data);
void		right_move(t_line *data);
void		move_home(t_line *data);
void		move_end(t_line *data);
void		move_cursor(t_line *data);

t_history	*search_up(t_line *data, t_history *history);
t_history	*search_next(t_line *data, t_history *history);
t_history	*search_history(t_line *data, t_history *history, char arrow);

void		delete2(t_line *data);
void		delete_down(t_line *data);

void		up_line(t_line *data);
void		down_last(t_line *data);
void		down_line(t_line *data);
void		next_word(t_line *data);
void		init_line(t_line *data);

void		ctrl_arrow(t_line *data, char arrow);
void		insert(t_line *data);
void		input(t_line *data, t_history **history, t_history **tmp);

void		free_all(t_line **data);
void		free_line(char **line);
void		free_history(t_history *history);

void		command_exit(void);
void		command_echo(t_cmd	*cmd);
void		command_env(t_list_2val	*l_env);
void		command_pwd(t_list_2val	*l_env);
void		command_cd(t_cmd *cmd, t_list_2val *l_env);
void		command_export(t_cmd *cmd, t_list_2val *l_env, char *flag,
				char *value);
void		command_unset(t_cmd *cmd, t_list_2val *l_env);
void		command_exit_input(t_cmd	*cmd);
void		find_flag_value2(char *env, char **flag, char **value);

char		*absolute_path(t_list_2val *l_env, char *tmp, char *ret,
				char *freec);
int			used_flag(char *flag, t_list_2val *l_env);
void		print_export(t_list_2val *l_env);
char		*new_real(char *real);

void		quiet_signal(int sig);
#endif