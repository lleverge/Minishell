/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:32:12 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 15:31:20 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**path_in_tab(t_env *env, char **cmd)
{
	char	**path_tab;
	int		nb_dir;
	char	*bin_path;

	nb_dir = 0;
	path_tab = NULL;
	bin_path = ft_getbin_path(cmd[0]);
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0 && bin_path == NULL)
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
	ft_strdel(&bin_path);
	return (path_tab);
}

static char		*search_path(char **path_tab, char **cmd)
{
	DIR				*ret;
	struct dirent	*elem;
	int				i;
	char			*tmp;
	char			*tmp2;

	i = -1;
	tmp2 = ft_getbin_name(cmd[0]);
	if (!path_tab)
		return (NULL);
	while (path_tab[++i] != 0)
	{
		ret = opendir(path_tab[i]);
		tmp = ft_strjoin(path_tab[i], "/");
		if (access(tmp, X_OK) != -1)
		{
			while ((elem = readdir(ret)))
			{
				if (tmp2 && ft_strcmp(tmp2, elem->d_name) == 0)
				{
					closedir(ret);
					ft_strdel(&tmp);
					ft_strdel(&tmp2);
					return (ft_strdup(path_tab[i]));
				}
			}
			closedir(ret);
		}
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp2);
	return (NULL);
}

int				exe_fork2(char **cmd, char **path_tab)
{
	pid_t	pid;
	char	*cmd_path;

	if ((cmd_path = search_path(path_tab, cmd)) == NULL)
	{
		ft_env_error(cmd[0]);
		free_tab(path_tab);
		return (-1);
	}
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (cmd[0][ft_strlen(cmd[0])] != '/')
			cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, ft_getbin_name(cmd[0]));
		if (env_manage_error(cmd_path) != -1)
			execve(cmd_path, cmd, NULL);
	}
	ft_strdel(&cmd_path);
	free_tab(path_tab);
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
		free_tab(path_tab);
		return (-1);
	}
	env_cpy = list_in_tab(env);
	pid = fork();
	if (pid > 0)
		wait(0);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (cmd[0][ft_strlen(cmd[0])] != '/')
			cmd_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(cmd_path, ft_getbin_name(cmd[0]));
		execve(cmd_path, cmd, env_cpy);
	}
	free_tab(env_cpy);
	ft_strdel(&cmd_path);
	free_tab(path_tab);
	return (0);
}
