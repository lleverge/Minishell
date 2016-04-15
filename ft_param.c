/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:36:02 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 18:33:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env				*env_in_list(char *envar, t_env *start)
{
	t_env	*tmp;
	t_env	*voyager;

	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->name = getvarname(envar);
	tmp->content = getvarcontent(envar);
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

static int			do_builtin(char **cmd, t_env **env, t_env *tmpenv)
{
	int		i;

	i = 0;
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (-1);
	else
	{
		if (ft_strcmp(cmd[0], "setenv") == 0)
			*env = ft_setenv(cmd, env);
		else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		{
			while (cmd[++i])
				ft_unsetenv(env, cmd[i]);
		}
		else if (ft_strcmp(cmd[0], "env") == 0)
			ft_env(env, tmpenv, cmd);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_cd(cmd, env);
		else
		{
			if ((exe_fork(*env, cmd, path_in_tab(*env, cmd)) == -1))
				return (1);
		}
	}
	return (0);
}

static int			manage_entry(char **cmd, t_env **env)
{
	t_env	*tmpenv;

	tmpenv = NULL;
	tmpenv = env_cpy(tmpenv, *env);
	if (do_builtin(cmd, env, tmpenv) == -1)
	{
		free_list(&tmpenv);
		return (-1);
	}
	else
	{
		free_list(&tmpenv);
		return (0);
	}
}

int					read_entry(char **cmd, t_env **env)
{
	int		i;
	char	**tab;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i])
	{
		tab = ft_strsplit_ws(cmd[i]);
		if (manage_entry(tab, env) == -1)
		{
			free_tab(cmd);
			free_tab(tab);
			return (-1);
		}
		i++;
		free_tab(tab);
	}
	free_tab(cmd);
	return (0);
}
