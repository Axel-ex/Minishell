/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/18 11:45:05 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
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
 * @brief Get the token content pointed to by *s and return a substr of s
 * depending on the char pointed to by *line, get_operater, get_quoted_content
 * and get_other functions are called.
 * 
 * @param s 
 * @return char* token content
 */
char	*get_token_content(char *line);

/**
 * @brief identifies the token_content type and returns it.
 * 
 * @param token_content 
 * @param path to identify commands
 * @return t_type 
 */
t_type	get_token_type(char *token_content);

/**
 * @brief Get content in the case of a quoted string
 * 
 * @param line 
 * @return char* 
 */
char	*get_quoted_content(char *line);

/**
 * @brief Get content if it's neither an operator or quoted string
 * 
 * @param line 
 * @return char* 
 */
char	*get_other(char *line);

/// ============================================================================
// TOKEN_UTILS.C
// =============================================================================
/**
 * @brief creates a new_token.
 * 
 * @param content 
 * @param type 
 * @return t_token* 
 */
t_token	*new_token(char *content, t_type type);

/**
 * @brief duplicates the token pointed to by *token.
 * 
 * @param token 
 * @return t_token* 
 */
t_token	*token_dup(t_token *token);

/**
 * @brief adds a new token to the list of tokens.
 * 
 * @param content 
 * @param type 
 */
void	token_add_back(char *content, t_type type);

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
// PARSER_UTILS.C
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

/// ============================================================================
// AST_GENERATOR.C
// =============================================================================
/**
 * @brief generates an abstarct synthax tree by capturing the
 * hierarchical relationship of synthactic elements.
 * 
 */
void	ast_generator(void);

/// ============================================================================
// AST_UTILS.C
// =============================================================================
/**
 * @brief creates a new ast node filled with the token pointed 
 * to by *token and returns it.
 * 
 * @param token 
 * @return t_ast* 
 */
t_ast	*new_ast_node(t_token *token);

int	get_matrix_len(char **matrix);

/**
 * @brief creates a new matrix containing the element *to_append,
 * free the old matrix and returns the new.
 * 
 * @param matrix 
 * @param to_append 
 * @return char** 
 */
char	**matrix_append(char **matrix, char *to_append);

#endif