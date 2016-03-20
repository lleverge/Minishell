/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:36:02 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 17:54:27 by lleverge         ###   ########.fr       */
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

static int			manage_entry(char *cmd, t_env *env)
{
	if (cmd == NULL)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (-1);
	else if (ft_strcmp(cmd, "env") == 0)
	{
		print_list(env);
		return (0);
	}
	else
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
			if (manage_entry(tab[j], env) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
