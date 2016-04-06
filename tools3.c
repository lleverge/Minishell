/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 12:01:29 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/06 18:11:17 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup_path(char **tab, char *content)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	if (!(tab_cpy = (char **)malloc(sizeof(char *) * (count_tablen(tab) + 2))))
		exit(1);
	while (tab[i] != 0)
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_cpy[i] = ft_strdup(content);
	free_tab(tab);
	return (tab_cpy);
}

char	**part_tabcpy(char **tab)
{
	int		i;
	int		j;
	int		count;
	char	**new;

	i = 2;
	j = 0;
	count = 0;
	while (tab[i] != 0)
	{
		count++;
		i++;
	}
	if (!(new = (char **)malloc(sizeof(char *) * count + 1)))
		return (NULL);
	i = 2;
	while (tab[i] != 0)
	{
		new[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

int		list_size(t_env *env)
{
	int		size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**list_in_tab(t_env *env)
{
	int		size;
	char	*str;
	char	*tmp;
	char	**envir;
	int		i;

	i = 0;
	size = list_size(env);
	if (!(envir = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		str = ft_strjoin(tmp, env->content);
		ft_strdel(&tmp);
		envir[i] = str;
		i++;
		env = env->next;
	}
	envir[i] = 0;
	return (envir);
}
