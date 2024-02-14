/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2024/02/14 14:23:39 by achabrer         ###   ########.fr       */
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
// AST_GENERATOR.C
// =============================================================================
/**
 * @brief generates an abstarct synthax tree by capturing the
 * hierarchical relationship of synthactic elements.
 * 
 */
void	ast_generator(void);


/// ============================================================================
// EXPANDER.C
// =============================================================================
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