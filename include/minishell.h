/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:55:55 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:43:33 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_list_2val
{
	char				*flag;
	char				*value;
	int					visible;
	struct s_list_2val	*next;
}t_list_2val;

//execute
typedef struct s_execute
{
	int				*fd;
	int				*pid;
	int				fd_correct;		
	int				fdin;
	int				fdout;
	int				num_cmd;
	char			*error_fd;
	int				err_fd;
	t_list_2val		*l_env;	
}t_execute;

//cmd
typedef struct s_cmd
{
	char				*part_cmd;
	t_list_2val			*fd_list;
	char				**cmd;
	int					our_cmd;
	t_list_2val			*l_env;
	struct s_cmd		*next;
}t_cmd;

//data
typedef struct s_sh
{
	char		*line;
	t_cmd		*l_cmd;
	t_list_2val	*l_env;
	char		*error_syntax;
	int			flag_error_syntax;
	int			num_cmd;
}t_sh;

//main
t_sh		*pars(char *line, t_list_2val *l_env);

//pars_env
t_list_2val	*pars_env(char **env, int i);

//pars
int			pars_check_line(char *line, char **error_syntax);
t_cmd		*pars_list_cmd(char *line, t_list_2val *env);
t_list_2val	*pars_list_fd(char *line, t_list_2val *env);
void		pars_list_find_fdin_fdout(t_cmd *cmd);
char		**pars_list_cmd_split(char *s);
void		pars_list_qoute_dollar_cmd(char **cmd, t_list_2val *env);
char		*pars_list_qoute_dollar_fd(char *cmd, t_list_2val *env);
char		*pars_list_open_dollars(char *str, int *i, t_list_2val *env);
char		*pars_list_access_cmd(char *cmd, t_list_2val *l_env, int *our_cmd);

//pars utils
void		pass_quotes(char *str, int *i, char qqq);

//minishell utils
int			ft_error_return(char *str);
void		ft_error_exit(char *str);
void		ft_error_malloc(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_free_split(char	**tmp);
char		*ft_strcpy(char *dest, const char *src);
int			gnl(int fd, char **line);

//pars env list
t_list_2val	*ft_lstnew_2val(char *flag, char *value);
void		ft_lstadd_back_2val(t_list_2val **lst, t_list_2val *new);
void		ft_lstprint_2val(t_list_2val *lst);

//execute
void		make_execute(t_sh *sh);
t_execute	*init_execute(int num, t_list_2val *l_env);
void		find_fdin_fdout_upgrade(t_execute *execute, t_cmd *cmd, int i);
char		**crt_new_env_array(t_list_2val *env);
void		create_fd_from_stdin(t_execute *execute, \
								int i, char *value, int ret);
void		do_our_in_pipe(t_sh *sh, t_cmd *cmd);
void		do_our_out_pipe(t_sh *sh, t_cmd *cmd);

//execute utils
void		update_errno(int status, t_list_2val *l_env);
void		close_fdin_fdout(t_execute *execute);
void		close_fd(t_execute *execute);
void		clear_execute(t_execute *execute);
void		update_execute(t_execute *execute);
void		close_all_execute(t_execute *execute, int ifff);
#endif
