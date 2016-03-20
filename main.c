/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:36:28 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 17:55:35 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char **argv, char **environ)
{
	int		i;
	char	**envi;
	t_env	*env;
	char	*line;

	i = 0;
	line = ft_strdup("");
	envi = ft_tabdup(environ);
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	env = NULL;
	while (envi[++i] != 0)
		env = env_in_list(envi[i], env);
	free_tab(envi);
	if (argc == 1)
	{
		ft_strlen(argv[0]);
		while ((read_entry(ft_strsplit(line, ';'), env)) != -1)
		{
			print_prompt();
			get_next_line(0, &line);
		}
	}
	free_list(&env);
	return (0);
}
