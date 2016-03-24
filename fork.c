/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/24 14:22:15 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**path_in_tab(t_env *env)
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
	struct dirent	*elem;
	int				i;

	i = 0;
	while (path_tab[i] != 0)
	{
		ret = opendir(path_tab[i]);
		if (access(ft_strjoin(path_tab[i], "/"), X_OK) != -1)
		{
			while ((elem = readdir(ret)))
			{
				if (ft_strcmp(cmd[0], elem->d_name) == 0)
				{
					closedir(ret);
					return (ft_strdup(path_tab[i]));
				}
			}
			closedir(ret);
		}
		i++;
	}
	return (NULL);
}

int				exe_fork(t_env *env, char **cmd, char **path_tab)
{
	pid_t	pid;
	char	*cmd_path;
	char	**env_cpy;

	if ((cmd_path = search_path(path_tab, cmd)) == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		return (-1);
	}
	env_cpy = list_in_tab(env);
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		execve(cmd_path, cmd, env_cpy);
	}
	return (0);
}
