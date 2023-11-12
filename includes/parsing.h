/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:37:49 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef enum s_type			t_type;
typedef enum s_operation	t_operation;

/// ============================================================================
// LEXER.C
// =============================================================================
/**
 * @brief returns a pointer to a token list.
 * 
 * @param line to tokenize
 * @return t_token* 
 */
void	get_token(char *line);

/**
 * @brief Get the token pointed to by *s and return a substr of s
 * 
 * @param s 
 * @return char* token content
 */
char	*get_token_content(char *s);

/**
 * @brief identifies the token_content type and returns it.
 * 
 * @param token_content 
 * @param path to identify commands
 * @return t_type 
 */
t_type	get_token_type(char *token_content);

/// ============================================================================
// PARSER.C
// =============================================================================
/**
 * @brief calls functions needed for tokenization, syntax check
 * expender.
 * 
 * @param shell 
 * @param line 
 * @return int EXIT_SUCCESS
 */
int		parser(void);

/// ============================================================================
// PARSER_UTIL.C
// =============================================================================
/**
 * @brief perform operation specified by op code on token list.
 * 
 * @param op 
 * @return t_token* 
 */
t_token	*scanner(t_operation op);

/**
 * @brief returns a string containing the operator found in s.
 * (allocated on the heap)
 * 
 * @param s 
 * @return char* 
 */
char	*get_operator(char *s);

/**
 * @brief checks if c is an operator.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool	is_operator(char c);

/**
 * @brief count quotes that are not found inside of quotes.
 * 
 * @param line 
 * @return int 
 */
int		count_quotes(char *line);

#endif