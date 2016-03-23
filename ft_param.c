/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:36:02 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/23 15:56:06 by lleverge         ###   ########.fr       */
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

static int			manage_entry(char **cmd, t_env *env)
{
	t_env	*tmpenv;

	tmpenv = NULL;
	tmpenv = env_cpy(tmpenv, env);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (-1);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		tmpenv = ft_setenv(cmd, env);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ft_unsetenv(&env, cmd[1]);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(tmpenv, cmd);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_cd(cmd[1], tmpenv);
		return (0);
	}
	free_list(&tmpenv);
	return (0);
}

int					read_entry(char **cmd, t_env *env)
{
	int		i;
	char	**tab;

	i = 0;
	if (cmd == NULL)
		return (-1);
	while (cmd[i])
	{
		tab = ft_strsplit(cmd[i], ' ');
		if (manage_entry(tab, env) == -1)
			return (-1);
		i++;
		free_tab(tab);
	}
	return (0);
}
