/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:07:59 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 16:56:00 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/termcap.h"
#include "../../include/minishell.h"
#include "../../include/wildcard.h"

void	read_file(int read_b)
{
	int		fd;
	char	buffer[11];

	fd = open("./src/term/head.txt", O_RDONLY);
	if (!fd || fd < 0)
		return ;
	while (read_b)
	{
		read_b = read(fd, buffer, 10);
		buffer[read_b] = '\0';
		printf("%s", buffer);
	}
	printf("\n");
	close(fd);
}

int	main(int argc, char **argv, char **envm)
{
	char		*last_cmd;
	t_history	*history;
	t_list_2val	*l_env;
	char		*error_syntax;

	(void)argc;
	(void)argv;
	history = NULL;
	l_env = pars_env(envm, -1);
	read_file(1);
	while (1)
	{
		error_syntax = NULL;
		last_cmd = ft_termcap(&history, l_env);
		last_cmd = pars_list_star(last_cmd);
		if (sh_all_check_line(last_cmd, &error_syntax))
		{
			printf("%s\n", error_syntax);
			update_errno(258, l_env);
			free (error_syntax);
		}
		else
			make_main_split(last_cmd, l_env);
	}
	return (0);
}
