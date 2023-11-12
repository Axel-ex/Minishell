/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:03:26 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:05:01 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/// ============================================================================
// SIGNALS.C
// =============================================================================
void	signals(int sig);
void	back_to_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
void    rl_replace_line(const char *text);

void	env_len(t_shell *shell);
void	init_env(t_shell *shell);
void	create_env(t_shell *shell, char **my_env);


#endif