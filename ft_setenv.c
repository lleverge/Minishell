/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:30 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 12:18:53 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_setenv_error(void)
{
	ft_putstr_fd("Error: Usage: setenv [varname] [Content]\n", 2);
}

static	t_env	*add_var(t_env *start, char *data)
{
	t_env	*tmp;
	t_env	*voyager;

	tmp = (t_env *)malloc(sizeof(t_env));
	voyager = start;
	tmp->var = ft_strdup(data);
	if (start == NULL)
		return (tmp);
	while (voyager->next)
		voyager = voyager->next;
	voyager->next = tmp;
	return (start);
}

t_env			*ft_setenv(char **cmd, t_env *env, int i)
{
	char *newvar;

	if (!(cmd[i + 1]) || !(cmd[i + 2]))
	{
		ft_setenv_error();
		return (NULL);
	}
	newvar = ft_strjoin(cmd[i + 1], "=");
	newvar = ft_strjoin(newvar, cmd[i + 2]);
	env = add_var(env, newvar);
	return (env);
}
