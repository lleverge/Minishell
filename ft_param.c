/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:36:02 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 16:52:16 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*env_in_list(char *envar, t_env *start)
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

int			read_entry(char *cmd, t_env *env)
{
	int	i;

	i = 0;
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
