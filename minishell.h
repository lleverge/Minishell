/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:23:33 by lleverge          #+#    #+#             */
/*   Updated: 2016/04/05 12:05:22 by lleverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <dirent.h>

typedef struct			s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}						t_env;

void					already_exist(t_env **begin_list, char *varname);
int						list_size(t_env *env);
char					**list_in_tab(t_env *env);
char					**path_in_tab(t_env *env);
int						exe_fork(t_env *env, char **cmd, char **path_tab);
void					ft_env(t_env *env, char **cmd);
t_env					*var_cpy(t_env *env, t_env *cpy);
t_env					*env_cpy(t_env *envtmp, t_env *env);
void					change_varcontent(t_env *env,
										char *name_ref, char *data);
void					ft_cd(char *moveto, t_env *env);
char					*getvarname(char *envar);
char					*getvarcontent(char *envar);
void					ft_unsetenv(t_env **begin_list, char *varname);
t_env					*ft_setenv(char **cmd, t_env *env);
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
