/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 17:18:53 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef enum s_type		t_type;

/// ============================================================================
// LEXER.C
// =============================================================================
/**
 * @brief returns a pointer to a token list.
 * 
 * @param line to tokenize
 * @return t_token* 
 */
void	get_token(t_shell *shell, char *line);

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
// LEXER_UTIL.C
// =============================================================================
/**
 * @brief add token at the back of token list. if **token doesn't
 * exists create it.
 * 
 * @param tokens pointer to the list
 * @param content of new token
 * @param type of new token
 */
void	add_back_token(t_token **tokens, char *content, t_type type);

/**
 * @brief try to access through the path the executable specified
 * by token_content. return true upon success (token_content is a 
 * command).
 * 
 * @param token_content 
 * @param path 
 * @return true
 * @return false 
 */
bool	is_command(char *token_content, char **path);

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
int		parser(t_shell *shell, char *line);
/// ============================================================================
// SYNTAX_CHECK.C
// =============================================================================
/**
 * @brief check for syntax errors. e.g if first token is not command
 *        if two consecutive tokens are separators
 *        if last token is separator
 * 
 * @param token 
 * @return int exit_status
 */
int		syntax_checker(t_token *token);

#endif