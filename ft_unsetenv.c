/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:41 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 13:40:35 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*getvarcontent(char *envar)
{
	int		i;
	int		j;
	char	*varcontent;

	i = 0;
	j = 0;
	while (envar[i])
		i++;
	while (envar[j] != '=')
		j++;
	j += 1;
	varcontent = ft_strsub(envar, j, i);
	return (varcontent);
}

char		*getvarname(char *envar)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	j = 0;
	while (envar[i] != '=')
		i++;
	varname = ft_strsub(envar, j, i);
	return (varname);
}

void			ft_unsetenv(t_env **begin_list, char *varname)
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
			ft_unsetenv(begin_list, varname);
		}
		else
			ft_unsetenv(&(*begin_list)->next, varname);
	}
}
