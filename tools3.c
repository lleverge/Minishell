/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:01:29 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/24 12:11:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		list_size(t_env *env)
{
	int		size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**list_in_tab(t_env *env)
{
	int		size;
	char	*str;
	char	*tmp;
	char	**envir;
	int		i;

	i = 0;
	size = list_size(env);
	if (!(envir = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		str = ft_strjoin(tmp, env->content);
		ft_strdel(&tmp);
		envir[i] = str;
		i++;
		env = env->next;
	}
	envir[i] = 0;
	return (envir);
}
