/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:41:03 by hzona             #+#    #+#             */
/*   Updated: 2021/11/18 17:52:29 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

int			array_wood(void);
char		**new_array_star(int len);
void		free_star(char *pre, char *su, char **arr);
char		*parse_star(char *str, int i, char *res, char **arr);

char		*ft_strjoin_free(char *s1, char const *s2);
char		*ft_strdup2(char *str);
char		*pref(char *str);
char		*suf(char *str);
int			check_su(char *str, char *su);

char		*pars_list_star(char *line);
#endif