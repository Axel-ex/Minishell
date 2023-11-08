/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 17:41:19 by achabrer         ###   ########.fr       */
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
t_token	*get_token(char *line, char **path);

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
 * @param path to identify comands
 * @return t_type 
 */
t_type	get_token_type(char *token_content, char **path);

/// ============================================================================
// LEXER_UTIL.C
// =============================================================================
/**
 * @brief add a new empty token at the end of the list of token
 * 
 * @param token list of tokens
 */
void	add_new_token(t_token *token);

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

#endif