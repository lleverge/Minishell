/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:30 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 13:36:34 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_setenv_error(void)
{
	ft_putstr_fd("Error: Usage: setenv [varname] [Content]\n", 2);
}

static	t_env	*add_var(t_env *start, char *name, char *data)
{
	t_env	*tmp;
	t_env	*voyager;

	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->name = ft_strdup(name);
	tmp->content = ft_strdup(data);
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
	if (!(cmd[1]) || !(cmd[2]))
	{
		ft_setenv_error();
		return (NULL);
	}
	env = add_var(env, cmd[1], cmd[2]);
	return (env);
}
