/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_our.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:26:26 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/15 20:06:19 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/termcap.h"

void	do_our_in_pipe(t_sh *sh, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd[0], "pwd\0"))
		command_pwd(sh->l_env);
	if (!ft_strcmp(cmd->cmd[0], "env\0"))
		command_env(sh->l_env);
	if (!ft_strcmp(cmd->cmd[0], "echo\0"))
		command_echo(cmd);
	if (!ft_strcmp(cmd->cmd[0], "export"))
		command_export(cmd, sh->l_env, NULL, NULL);
}

void	do_our_out_pipe(t_sh *sh, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd[0], "exit\0"))
		command_exit_input(cmd);
	if (!ft_strcmp(cmd->cmd[0], "cd\0"))
		command_cd(cmd, sh->l_env);
	if (!ft_strcmp(cmd->cmd[0], "export"))
		command_export(cmd, sh->l_env, NULL, NULL);
	if (!ft_strcmp(cmd->cmd[0], "unset"))
		command_unset(cmd, sh->l_env);
}
