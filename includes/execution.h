/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:06:20 by achabrer          #+#    #+#             */
/*   Updated: 2023/12/01 11:37:01 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/// ============================================================================
// EXECUTOR.C
// =============================================================================
/**
 * @brief Creates pipes and executes the ast. waits for all child to finish
 * their task.
 * 
 */
void	executor(void);

/**
 * @brief check if the command is not builtin and execute accordingly
 * 
 * @param ast 
 */
void	match_cmd(t_ast *ast);

/**
 * @brief executes forkable commands. the function first checks if the command
 * is valid and sets exit_status. checks for redirection and set
 * fd accordingly. then for and connect in/output to the corresponding pipes.
 * executes the command and restore in/output.
 * 
 * @param ast 
 * @return int 
 */
void	execute_child(t_ast *ast);

/**
 * @brief call execve on the command path.
 * 
 * @param ast 
 * @return int 
 */
int		execute_cmd(t_ast *ast);



/// ============================================================================
// EXECUTOR_UTIL.C
// =============================================================================
/**
 * @brief check cmd path and set exit_status accordingly
 * 
 * @param cmd 
 * @return int 
 */
int		check_cmd_path(char *cmd);

/**
 * @brief check if the token is an operator
 * 
 * @param token 
 * @return true 
 * @return false 
 */
bool	is_operator(t_token *token);

/**
 * @brief Get the cmd path, either absolute or relative
 * 
 * @param cmd 
 * @return char* 
 */
char	*get_cmd_path(char *cmd);

/**
 * @brief check if a command is forkable. non forkable are command
 * that need to be executed by the main process for it's changes to be
 * reflected in the program
 * 
 * @param cmd 
 * @return true 
 * @return false 
 */
bool	is_forkable(char *cmd);



/// ============================================================================
// PIPES.C
// =============================================================================
/**
 * @brief creates the pipes array.
 * 
 */
void	pipe_create(void);

/**
 * @brief connect the io of the commands to the appropriate pipes
 * 
 * @param ast_pos 
 */
void	pipe_connect(int ast_pos);




/// ============================================================================
// REDIRECTIONS.C
// =============================================================================
/**
 * @brief handle the four different types of redirection
 * 
 * @param ast 
 * @return int 
 */
int		handle_redir(t_ast *ast);

/**
 * @brief calls dup2 on fd_in and fd_out that has been set previously
 * to pipes or files.
 * 
 */
void	redirect_io(void);

/**
 * @brief close the fd that have been open, restore STDIN and STDOUT
 * as the fd by default.
 * 
 * @param node_pos 
 */
void	restore_io(int node_pos);

/**
 * @brief creates a temporary file that will store the content inputed
 * during the heredoc and associate fd with the command
 * 
 * @param ast 
 */
void	handle_heredoc(t_ast *ast);

#endif