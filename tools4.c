/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 12:19:56 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 18:20:21 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt2(char *new, char *tmp, char *home)
{
	color(GREEN, "");
	ft_putstr("~");
	new = ft_strsub(tmp, ft_strlen(home), ft_strlen(tmp));
	ft_putstr_sp(new);
	color(RESET, "");
	ft_strdel(&new);
}

char	*get_data(t_env *env, char *ref_name)
{
	while (env)
	{
		if (ft_strcmp(env->name, ref_name) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
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
