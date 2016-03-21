/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:18:57 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 16:22:55 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*getvarcontent(char *envar)
{
	int		i;
	int		j;
	char	*varcontent;

	i = 0;
	j = 0;
	while (envar[i])
		i++;
	while (envar[j] != '=')
		j++;
	j += 1;
	varcontent = ft_strsub(envar, j, i);
	return (varcontent);
}

char		*getvarname(char *envar)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	j = 0;
	while (envar[i] != '=')
		i++;
	varname = ft_strsub(envar, j, i);
	return (varname);
}

void		change_varcontent(t_env *env, char *name_ref, char *data)
{
	while (env)
	{
		if (!(ft_strcmp(env->name, name_ref)))
		{
			ft_strdel(&(env->content));
			env->content = data;
		}
		env = env->next;
	}
}
