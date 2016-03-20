/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:36:28 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 16:22:04 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

static char		**ft_tabdup(char **tab)
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

int				main(int argc, char **argv, char **environ)
{
	int		i;
	char	**envi;
	t_env	*env;
	char	*line;

	i = 0;
	line = NULL;
	envi = ft_tabdup(environ);
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	env = NULL;
	while (envi[i] != 0)
	{
		env = env_in_list(envi[i], env);
		i++;
	}
	if (argc == 1)
	{
		ft_strlen(argv[0]);
		while ((read_entry(line, env)) != -1)
		{
			print_prompt();
			get_next_line(0, &line);
		}
	}
	return (0);
}
