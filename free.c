/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:37:36 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 16:43:15 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		ft_strdel(&(current->var));
		free(current);
		current = next;
	}
	*head = NULL;
}

void		free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}
