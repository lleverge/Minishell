/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:41 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 12:17:08 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*getvarname(char *envar)
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
	char	*suspect;

	tmp = *begin_list;
	if (*begin_list)
	{
		suspect = getvarname((*(begin_list))->var);
		if (!(ft_strcmp(suspect, varname)))
		{
			tmp = *begin_list;
			*begin_list = (*(begin_list))->next;
			ft_strdel(&(tmp->var));
			free(tmp);
			ft_unsetenv(begin_list, varname);
		}
		else
			ft_unsetenv(&(*begin_list)->next, varname);
	}
}
