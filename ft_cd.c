/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 13:58:26 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 14:19:23 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_cd_error(char *name)
{
	ft_putstr_fd("Error:", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("Not such directory", 2);
	ft_putchar('\n');
}

void			ft_cd(char *moveto, t_env *env)
{
	if (!moveto || (ft_strcmp(moveto, "~") == 0))
	{
		while (env)
		{
			if (ft_strcmp(env->name, "HOME") == 0)
				chdir(env->content);
			env = env->next;
		}
	}
	else if (opendir(moveto) == NULL)
	{
		ft_cd_error(moveto);
		return ;
	}
	else
		chdir(moveto);
}
