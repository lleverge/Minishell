/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 15:59:00 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/15 16:20:12 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fork_error(char **cmd, char **path_tab)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found.\n", 2);
	free_tab(path_tab);
}

char		*search_path2(char *tmp2, char *tmp, char **path_tab)
{
	struct dirent	*elem;
	DIR				*ret;
	int				i;

	i = -1;
	while (path_tab[++i] != 0)
	{
		ret = opendir(path_tab[i]);
		tmp = ft_strjoin(path_tab[i], "/");
		if (access(tmp, X_OK) != -1)
		{
			while ((elem = readdir(ret)))
				if (tmp2 && ft_strcmp(tmp2, elem->d_name) == 0)
				{
					closedir(ret);
					ft_strdel(&tmp);
					ft_strdel(&tmp2);
					return (ft_strdup(path_tab[i]));
				}
		}
		closedir(ret);
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp2);
	return (NULL);
}
