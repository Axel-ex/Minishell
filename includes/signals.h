/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:03:26 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 13:04:09 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

typedef struct s_env
{
	char	**env;
	char	**key;
	char	**content;
	int		len;
}			t_env;


/// ============================================================================
// SIGNALS.C
// =============================================================================
void	signals(int sig);
void	back_to_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
void    rl_replace_line(const char *text);

void allocate_memory(t_env *env);
void env_len(t_env *env);
void populate_env_structure(t_env *env);
void free_memory(t_env *env);

#endif