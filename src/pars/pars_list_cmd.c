/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:23:53 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/18 18:11:04 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*init_cmd(char *tmp_line, t_list_2val *env)
{
	t_cmd	*l_cmd;

	l_cmd = malloc(sizeof(t_cmd));
	if (!l_cmd)
		ft_error_malloc("Error malloc: pars_list_cmd.c - l_cmd");
	l_cmd->part_cmd = tmp_line;
	l_cmd->fd_list = ((void *)0);
	l_cmd->cmd = ((void *)0);
	l_cmd->our_cmd = 0;
	l_cmd->l_env = env;
	l_cmd->next = ((void *)0);
	return (l_cmd);
}

static void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

static t_cmd	*create_new_list_cmd(char *line, int j, int i, t_list_2val *env)
{
	char	*tmp_line;
	t_cmd	*tmp_list;

	if (*(line + i) == '|')
		tmp_line = ft_substr(line, j, i - j);
	else
		tmp_line = ft_substr(line, j, i - j + 1);
	if (!tmp_line)
		ft_error_malloc("Error malloc: pars_list_cmd.c - tmp_line");
	tmp_list = init_cmd(tmp_line, env);
	tmp_list->fd_list = pars_list_fd(tmp_list->part_cmd, tmp_list->l_env);
	tmp_list->cmd = pars_list_cmd_split(tmp_list->part_cmd);
	pars_list_qoute_dollar_cmd(tmp_list->cmd, tmp_list->l_env);
	tmp_list->cmd[0] = pars_list_access_cmd(tmp_list->cmd[0], \
									tmp_list->l_env, &tmp_list->our_cmd);
	errno = 0;
	return (tmp_list);
}

t_cmd	*pars_list_cmd(char *line, t_list_2val *env)
{
	int		i;
	int		j;
	t_cmd	*l_cmd;

	l_cmd = ((void *)0);
	i = 0;
	j = 0;
	while (*(line + i))
	{
		if (*(line + i) == '\'')
			pass_quotes(line, &i, '\'');
		else if (*(line + i) == '\"')
			pass_quotes(line, &i, '\"');
		else if (*(line + i) == '|')
		{
			cmd_lstadd_back(&l_cmd, create_new_list_cmd(line, j, i, env));
			i++;
			j = i;
		}
		else
			i++;
	}
	cmd_lstadd_back(&l_cmd, create_new_list_cmd(line, j, i, env));
	return (l_cmd);
}
