/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:18:57 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 15:27:32 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
