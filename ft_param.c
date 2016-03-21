/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:36:02 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 12:15:46 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env				*env_in_list(char *envar, t_env *start)
{
	int		i;
	t_env	*tmp;
	t_env	*voyager;

	i = 0;
	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->var = ft_strdup(envar);
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

static int			manage_entry(char **cmd, t_env *env)
{
	int		i;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i] != 0)
	{
		if (ft_strcmp(cmd[i], "exit") == 0)
			return (-1);
		else if (ft_strcmp(cmd[i], "setenv") == 0)
		{
			env = ft_setenv(cmd, env, i);
			return (0);
		}
		else if (ft_strcmp(cmd[i], "unsetenv") == 0)
			ft_unsetenv(&env, cmd[i + 1]);
		else if (ft_strcmp(cmd[i], "env") == 0)
		{
			print_list(env);
			return (0);
		}
		i++;
	}
	return (0);
}

int					read_entry(char **cmd, t_env *env)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		tab = ft_strsplit(cmd[i], ' ');
		while (tab[j])
		{
			if (manage_entry(tab, env) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
