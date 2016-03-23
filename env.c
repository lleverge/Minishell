/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 15:48:21 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/23 16:02:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env(t_env *env, char **cmd)
{
	int		i;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] == 'u' && cmd[2])
			{
				ft_unsetenv(&env, cmd[2]);
				print_list(env);
			}
			i++;
		}
	}
	else if (cmd[1] && cmd[2] && cmd[1][0] != '-')
	{
		env = ft_setenv(cmd, env);
		print_list(env);
	}
	else if (!cmd[1])
		print_list(env);
}
