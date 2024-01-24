/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/24 10:40:03 by achabrer         ###   ########.fr       */
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
 * @brief Get the token content pointed to by *line and return a substr of line
 * depending on the char pointed to by *line, get_operator, get_quoted_content
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
 * @brief scans through the token list perform and operation specified by op
 * code on token list. READ returns a token, RESET resets pointer to list
 * 
 * @param op 
 * @return t_token* 
 */
t_token	*scanner(t_operation op);

/**
 * @brief creates a new_token containing content and type.
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
void	token_add_back(char *content, t_type type, int count_space);

void	token_content_append(char *to_append);

/// ============================================================================
// PARSER.C
// =============================================================================
/**
 * @brief tokenize the content of the read line, perform synthax checks
 * and lexical analysis, remove the quotes and expand variable inside
 * of the line. The output is a tidy ast ready to be executed
 * 
 * @param shell 
 * @param line 
 * @return int EXIT_SUCCESS
 */
int		parser(void);

/**
 * @brief  check if the line is empty
 * 
 * @param line 
 * @return true 
 * @return false 
 */
bool	is_empty(char *line);

/// ============================================================================
// QUOTES.C
// =============================================================================

/**
 * @brief Get the last quote position. the last quote is the same type
 * as the first one.
 * 
 * @param line 
 * @return int 
 */
int		get_last_quote_pos(char *line);

/**
 * @brief returns a string containing the operator found in s.
 * (allocated on the heap)
 * 
 * @param s 
 * @return char* 
 */
char	*get_operator(char *s);

/**
 * @brief count quotes that are not found inside of quotes.
 * 
 * @param line 
 * @return int 
 */
int		count_quotes(char *line);

/**
 * @brief Removes the quotes from token content
 * 
 * @param content 
 * @return char* 
 */
char	*remove_quotes(char *content);

/**
 * @brief Get the first occuring quote to remove quotes of the line
 * 
 * @param line 
 * @return char 
 */
char	get_first_quote(char *content);

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

/**
 * @brief creates a new matrix containing the element *to_append,
 * free the old matrix and returns the new.
 * 
 * @param matrix 
 * @param to_append 
 * @return char** 
 */
char	**matrix_append(char **matrix, char *to_append);

/**
 * @brief Get the len of a matrix.
 * 
 * @param matrix 
 * @return int 
 */
int		get_matrix_len(char **matrix);

/// ============================================================================
// EXPANDER.C
// =============================================================================
/**
 * @brief Retrieves the key for variable expansion.
 * 
 * This function takes a pointer to a string and extracts the key
 * for variable expansion. The key consists of alphanumeric characters
 * and underscores.
 * 
 * @param temp A pointer to the string containing the variable.
 * @return The key for variable expansion.
 */
char	*get_key_expansion(char **temp);

/**
 * @brief Expands variables in a token's content.
 * 
 * This function expands variables in a token's content by replacing
 * them with their corresponding values. The variables are identified
 * by a dollar sign ($) followed by an alphabetic character. The expanded
 * content is stored in a new string and replaces the original content of
 * the token.
 * 
 * @param token The token to expand variables in.
 */
char	*expand_variable(char *content);

/**
 * @brief Expands variables in the token list.
 * 
 * This function iterates over the token list and expands variables in tokens
 * of type OTHER.
 * It skips tokens of type REDIR2_OUT.
 */
void	expander(void);

#endif