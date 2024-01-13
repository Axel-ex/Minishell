/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:41:58 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/12 17:21:16 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_EXIT_H
# define INIT_EXIT_H

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

/// ============================================================================
// ERROR CODE
// =============================================================================
# define SYNTAX_ERROR	2
# define DIR_NT_FD		126
# define CMD_NT_FD		127

/// ============================================================================
// ERROR MSG
// =============================================================================
# define ERR_UNCLOSED_QUOTES	"command contains unclosed quotes"
# define SYNTH_ERR_TOKEN		"syntax error near unexpected token "
# define ERR_CMD				"command not found"
# define ERR_DIR				"No such file or directory"
# define PERM_DEN				"Permission denied"



/// ============================================================================
// INIT.C
// =============================================================================
/**
 * @brief init shell structure. Alloc space for shell struct, get path variable.
 *
 * @param envp  
 * @return t_shell* 
 */
void	init_shell(char **envp);



/// ============================================================================
// ERROR.C
// =============================================================================
/**
 * @brief print error message and set exit value.
 * 
 * @param exit_status 
 * @param msg 
 * @param var to print before msg
 * @return int 
 */
int		print_error(int exit_status, char *msg, char *var);

/**
 * @brief prints the msg pointed to by *msg and return NULL.
 * 
 * @param msg to print
 * @return void* NULL
 */
void	*alloc_error(char *msg);



/// ============================================================================
// FREE.C
// =============================================================================
/**
 * @brief free the shell struct. if keep iterating is true, variables
 * like path and the shell struct itself are conserved 
 * 
 * @param shell 
 * @param keep_iterating 
 */
void	free_shell(bool keep_iterating);

/**
 * @brief free the list of tokens (pointers and content).
 * 
 * @param token 
 */
void	free_token(t_token *token);

/**
 * @brief free object of type char **.
 * 
 * @param matrix 
 */
void	free_matrix(char **matrix);

/**
 * @brief free pipes
 * 
 * @param pipes 
 */
void	free_pipes(int **pipes);

int	print_error_export(int exit_status, char *msg, char *var,char *arg);


#endif