/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/24 12:13:09 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**path_in_tab(t_env *env)
{
	char	**path_tab;

	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
		{
			path_tab = ft_strsplit(env->content, ':');
			return (path_tab);
		}
		env = env->next;
	}
	return (NULL);
}

static char		*search_path(char **path_tab, char **cmd)
{
	DIR				*ret;
	struct	dirent	*elem;
	int				i;

	i = 0;
	while (path_tab[i] != 0)
	{
		ret = opendir(path_tab[i]);
		elem = readdir(ret);
		while (elem)
		{
			if (ft_strcmp(cmd[0], elem->d_name) == 0)
			{
				return (ft_strdup(path_tab[i]));
			}
			elem = readdir(ret);
		}
	}
	return (NULL);
}

void		exe_fork(t_env *env, char **cmd, char **path_tab)
{
	pid_t	pid;
	char	*cmd_path;
	char	**env_cpy;

	cmd_path = search_path(path_tab, cmd);
	env_cpy = list_in_tab(env);
/*	if (access(cmd[0], X_OK) != -1)
	{*/
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		execve(cmd_path, cmd, env_cpy);
	}
	/*}
	else
	ft_putstr_fd("Permission denied\n", 2);*/
}
