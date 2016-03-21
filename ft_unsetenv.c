/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:53:41 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/21 16:41:06 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		unsetenv_error(char *varname)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd(": Not found\n", 2);
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
		}
		else
			ft_unsetenv(&(*begin_list)->next, varname);
	}
	else if (*begin_list == NULL)
		unsetenv_error(varname);
}
