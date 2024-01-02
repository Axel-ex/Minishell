/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:03:26 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/02 12:01:33 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/// ============================================================================
// SIGNALS.C
// =============================================================================
void	rl_replace_line(const char *text, int clear_undo);
void	signals(int sig);
void	back_to_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);

#endif