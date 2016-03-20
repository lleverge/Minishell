/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:31:10 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 16:10:39 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_list(t_env *env)
{
	if (env)
	{
		while (env)
		{
			ft_putstr(env->var);
			ft_putchar('\n');
			env = env->next;
		}
	}
}

void		print_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr(tab[i]);
		ft_putchar('\n');
		i++;
	}
}

void		print_prompt(void)
{
	ft_putstr("$> ");
}
