/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:31:10 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/14 09:33:58 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

char		**ft_tabdup(char **tab)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	if (!(tab_cpy = (char **)malloc(sizeof(char *) * (count_tablen(tab) + 1))))
		exit(1);
	while (tab[i] != 0)
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_cpy[i] = 0;
	return (tab_cpy);
}

void		print_list(t_env *env)
{
	if (env)
	{
		while (env)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			ft_putstr(env->content);
			ft_putchar('\n');
			env = env->next;
		}
	}
	else
		ft_putstr("empty env\n");
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
