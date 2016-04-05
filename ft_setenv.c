/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:30 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/05 14:44:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		test_alpha(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

void			already_exist(t_env **begin_list, char *varname)
{
	t_env	*tmp;

	tmp = *begin_list;
	if (*begin_list)
	{
		if (!(ft_strcmp((*(begin_list))->name, varname)))
		{
			tmp = *begin_list;
			*begin_list = (*(begin_list))->next;
			ft_strdel(&(tmp->name));
			ft_strdel(&(tmp->content));
			free(tmp);
		}
		else
			already_exist(&(*begin_list)->next, varname);
	}
}

static t_env	*add_var(t_env *start, char *name, char *data)
{
	t_env	*tmp;
	t_env	*voyager;

	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->name = ft_strdup(name);
	if (data)
		tmp->content = ft_strdup(data);
	else
		tmp->content = ft_strdup("");
	tmp->next = NULL;
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

t_env			*ft_setenv(char **cmd, t_env *env)
{
	if (!(cmd[1]))
		print_list(env);
	else if (test_alpha(cmd[1]) == -1)
	{
		ft_putstr_fd("setenv: Variable name must contain ", 2);
		ft_putstr_fd("alphanumeric characters.\n", 2);
	}
	else if (cmd[1] && !cmd[2])
	{
		already_exist(&env, cmd[1]);
		env = add_var(env, cmd[1], NULL);
	}
	else if (cmd[1] && cmd[2] && !cmd[3])
	{
		already_exist(&env, cmd[1]);
		env = add_var(env, cmd[1], cmd[2]);
	}
	else
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	return (env);
}
