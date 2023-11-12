/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:41:58 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:14:25 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_EXIT_H
# define INIT_EXIT_H

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

/// ============================================================================
// ERROR CODE
// =============================================================================
# define SYNTAX_ERROR 2

/// ============================================================================
// ERROR MSG
// =============================================================================
# define ERR_UNCLOSED_QUOTES	"command contains unclosed quotes"
# define ERR_OPERATOR_END		"Syntax Error: Prompt should not\
 								end with an operator"
# define ERR_TOKEN_SEQ			"Syntax Error : unexpected sequence\
								of tokens"
# define ERR_OPERATOR_BEGIN		"Syntax Error : First token should be\
								a command"

/// ============================================================================
// INIT.C
// =============================================================================
/**
 * @brief init shell structure. Alloc space for shell struct, get path variable.
 * 
 * @return t_shell* 
 */
void	init_shell(void);

/// ============================================================================
// ERROR.C
// =============================================================================
/**
 * @brief prints the msg pointed to by *msg and return EXIT_FAILURE.
 * 
 * @param msg to_print 
 */
int		print_error(char *msg, int exit_status);

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
void	free_tokens(t_token **tokens);

/**
 * @brief free object of type char **.
 * 
 * @param matrix 
 */
void	free_matrix(char **matrix);

#endif