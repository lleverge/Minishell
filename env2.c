/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 18:36:44 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/06 18:45:58 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env_i(t_env *env, char **cmd)
{
	if (!cmd[2])
		return ;
	else
		exe_fork2(env, cmd, path_in_tab(env));
}

void		ft_bad_opt(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: env [-iv] [-u name]", 2);
	ft_putstr_fd("\n           [name=value ...] [utility [argument ...]]\n", 2);
}

void		ft_env_usage(char opt)
{
	ft_putstr_fd("env: option requires an argument -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putstr_fd("\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\n", 2);
	ft_putstr_fd("           [name=value ...] [utility [argument ...]]\n", 2);
}

void		ft_env_error(char *file)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
