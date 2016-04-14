/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/14 13:25:52 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**path_in_tab(t_env *env, char **cmd)
{
	char	**path_tab;
	int		nb_dir;

	nb_dir = 0;
	path_tab = NULL;
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0 && ft_getbin_path(cmd[0]) == NULL)
			path_tab = ft_strsplit(env->content, ':');
		env = env->next;
	}
	if (!path_tab)
	{
		if ((path_tab = (char **)malloc(sizeof(char *) * 2)))
		{
			path_tab[0] = ft_getbin_path(cmd[0]);
			path_tab[1] = NULL;
		}
		else
			return (NULL);
	}
	return (path_tab);
}

static char		*search_path(char **path_tab, char **cmd)
{
	DIR				*ret;
	struct dirent	*elem;
	int				i;

	i = -1;
	if (!path_tab)
		return (NULL);
	while (path_tab[++i] != 0)
	{
		ret = opendir(path_tab[i]);
		if (access(ft_strjoin(path_tab[i], "/"), X_OK) != -1)
		{
			while ((elem = readdir(ret)))
			{
				if (ft_getbin_name(cmd[0])
					&& ft_strcmp(ft_getbin_name(cmd[0]), elem->d_name) == 0)
				{
					closedir(ret);
					return (ft_strdup(path_tab[i]));
				}
			}
			closedir(ret);
		}
	}
	return (NULL);
}

int				exe_fork2(t_env *env, char **cmd, char **path_tab)
{
	pid_t	pid;
	char	*cmd_path;

	if ((cmd_path = search_path(path_tab, cmd)) == NULL)
	{
		ft_env_error(cmd[0]);
		return (-1);
	}
	free_list(&env);
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		if (cmd[0][ft_strlen(cmd[0])] != '/')
			cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, ft_getbin_name(cmd[0]));
		if (env_manage_error(cmd_path) != -1)
			execve(cmd_path, cmd, NULL);
	}
	return (0);
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
		if (cmd[0][ft_strlen(cmd[0])] != '/')
			cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, ft_getbin_name(cmd[0]));
		execve(cmd_path, cmd, env_cpy);
	}
	return (0);
}
