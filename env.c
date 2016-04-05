/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 15:48:21 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/05 14:39:21 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_env_error(char *file)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static void		ft_env_usage(char opt)
{
	ft_putstr_fd("env: option requires an argument -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putstr_fd("\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\n", 2);
	ft_putstr_fd("           [name=value ...] [utility [argument ...]]\n", 2);
}

static t_env	*add_var(t_env *start, char *cmd)
{
	t_env *tmp;
	t_env *voyager;

	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->name = getvarname(cmd);
	tmp->content = getvarcontent(cmd);
	tmp->next = NULL;
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

void			ft_env_opt(t_env *env, char **cmd)
{
	int		i;

	i = 1;
	while (cmd[1][i])
	{
		if (cmd[1][i] == 'u' && !cmd[2] && !(cmd[1][i + 1]))
		{
			ft_env_usage(cmd[1][i]);
			return ;
		}
		else if (cmd[3])
		{
			ft_env_error(cmd[3]);
			return ;
		}
		else if (cmd[1][i] == 'u' && cmd[2])
		{
			ft_unsetenv(&env, cmd[2]);
			print_list(env);
		}
		i++;
	}
}

void			ft_env(t_env *env, char **cmd)
{
	int		i;

	i = 0;
	if (!cmd[1])
		print_list(env);
	else if (cmd[1] && cmd[1][0] == '-')
	{
		ft_env_opt(env, cmd);
	}
	else if (cmd[1] && cmd[1][0] != '-')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] == '=')
			{
				already_exist(&env, getvarname(cmd[1]));
				add_var(env, cmd[1]);
				print_list(env);
				return ;
			}
			i++;
		}
		ft_env_error(cmd[1]);
	}
}
