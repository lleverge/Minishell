/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 15:48:21 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 15:20:38 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env		*add_var(t_env *start, char *cmd)
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

int					env_manage_error(char *cmd)
{
	t_stat	st;

	if (stat(cmd, &st) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory.\n", 2);
		return (-1);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied.\n", 2);
		return (-1);
	}
	return (0);
}

static void			ft_env_u(t_env *env, char **cmd)
{
	int		i;

	i = 1;
	if (!cmd[2])
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
}

static void			ft_env_opt(t_env *env, t_env *tmpenv, char **cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[1][++i])
		if (cmd[1][i] != 'u' && cmd[1][i] != 'i')
		{
			ft_bad_opt(cmd[1][i]);
			return ;
		}
	while (cmd[1][++j])
	{
		if (cmd[1][j] == 'u')
		{
			ft_env_u(env, cmd);
			return ;
		}
		else if (cmd[1][j] == 'i')
		{
			ft_env_i(tmpenv, cmd);
			return ;
		}
	}
}

void				ft_env(t_env **env, t_env *tmpenv, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (cmd[1])
		tmp = getvarname(cmd[1]);
	if (!cmd[1])
		print_list(*env);
	else if (cmd[1] && cmd[1][0] == '-')
		ft_env_opt(*env, tmpenv, cmd);
	else if (cmd[1] && cmd[1][0] != '-')
	{
		while (cmd[1][i])
		{
			if (cmd[1][i] == '=')
			{
				already_exist(&tmpenv, tmp);
				tmpenv = add_var(tmpenv, cmd[1]);
				print_list(tmpenv);
				ft_strdel(&tmp);
				return ;
			}
			i++;
		}
		ft_env_error(cmd[1]);
	}
	ft_strdel(&tmp);
}
