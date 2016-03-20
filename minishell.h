/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:23:33 by lleverge          #+#    #+#             */
/*   Updated: 2016/03/20 17:19:30 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"

typedef struct			s_env
{
	char			*var;
	struct s_env	*next;
}						t_env;

void					free_list(t_env **head);
void					free_tab(char **tab);
char					**ft_tabdup(char **tab);
int						count_tablen(char **tab);
t_env					*env_in_list(char *envar, t_env *start);
void					print_list(t_env *env);
void					print_tab(char **tab);
int						read_entry(char **cmd, t_env *env);
void					print_prompt(void);
#endif
