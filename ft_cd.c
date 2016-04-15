/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 13:58:26 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 18:49:50 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_cd_prev(t_env *env)
{
	char	buf[512];
	char	*tmp;
	t_env	*tmpenv;

	tmpenv = env;
	while (tmpenv)
	{
		if (ft_strcmp(tmpenv->name, "OLDPWD") == 0)
		{
			tmp = tmpenv->content;
			if (getcwd(buf, 512) != NULL)
				change_varcontent(tmpenv, "OLDPWD", getcwd(buf, 512));
			chdir(tmp);
			change_varcontent(env, "PWD", getcwd(buf, 512));
		}
		tmpenv = tmpenv->next;
	}
}

static void		ft_cd_home(t_env *env)
{
	char	buf[512];
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			if (getcwd(buf, 512) != NULL)
				change_varcontent(env, "OLDPWD", getcwd(buf, 512));
			chdir(env->content);
			change_varcontent(tmp, "PWD", getcwd(buf, 512));
		}
		env = env->next;
	}
}

static void		manage_error(char **cmd, t_env *env)
{
	t_stat	st;
	char	buf[512];

	if (stat(cmd[1], &st) == -1)
	{
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory.\n", 2);
	}
	else if (!(S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Not a directory.\n", 2);
	}
	else if (access(cmd[1], X_OK) == -1)
	{
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": Permission denied.\n", 2);
	}
	else
	{
		change_varcontent(env, "OLDPWD", getcwd(buf, 512));
		chdir(cmd[1]);
		change_varcontent(env, "PWD", getcwd(buf, 512));
	}
}

void			ft_cd(char **cmd, t_env **env)
{
	if (!cmd[1] || (ft_strcmp(cmd[1], "~") == 0))
		ft_cd_home(*env);
	else if (cmd[1] && cmd[2])
		ft_putstr_fd("cd: Too many arguments.\n", 2);
	else if (ft_strcmp(cmd[1], "-") == 0)
		ft_cd_prev(*env);
	else
		manage_error(cmd, *env);
}
