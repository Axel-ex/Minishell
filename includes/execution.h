/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:06:20 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/21 14:50:06 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/// ============================================================================
// EXECUTOR.C
// =============================================================================
void	executor(void);
int		execute_cmd(t_ast *ast);
char	*redir_output(t_ast *ast);

/// ============================================================================
// EXECUTOR_UTIL.C
// =============================================================================
void	match_cmd(t_ast *ast);
bool	is_builtin(char *cmd);
bool	is_operator(t_token *token);
char	*get_cmd_path(char *cmd);
bool	is_forkable(char *cmd);

/// ============================================================================
// PIPES.C
// =============================================================================
void	pipe_create(void);
void	pipe_connect(int ast_pos);
void	execute_fork(t_ast *ast);

/// ============================================================================
// REDIRECTIONS.C
// =============================================================================
void	redirect_io(void);
void	restore_io(int node_pos);

#endif