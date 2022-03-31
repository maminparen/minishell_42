/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:35:52 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/17 19:38:07 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_three_strjoin(char *flag, char *value)
{
	char	*new_env;

	new_env = ft_strjoin(flag, "=");
	if (!new_env)
		ft_error_malloc("Error malloc: execute.c - str");
	new_env = ft_strjoin(new_env, value);
	if (!new_env)
		ft_error_malloc("Error malloc: execute.c - str");
	return (new_env);
}

char	**crt_new_env_array(t_list_2val *env)
{
	char		**new_env;
	int			i;
	t_list_2val	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->visible == 1)
			i++;
		tmp = tmp->next;
	}
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		ft_error_malloc("Error malloc:execute.c - new_env");
	new_env[i] = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{		
		if (tmp->visible == 1)
			new_env[i++] = ft_three_strjoin(tmp->flag, tmp->value);
		tmp = tmp->next;
	}
	return (new_env);
}
