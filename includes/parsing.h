/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/11 13:42:16 by jgomes-v         ###   ########.fr       */
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
 * @brief returns a string containing the operator found in s.
 * (allocated on the heap)
 * 
 * @param s 
 * @return char* 
 */
char	*get_operator(char *s);

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

void	main_loop(t_shell *shell);

/// ============================================================================
// SIGNALS.C
// =============================================================================
void	signals(int sig);
void	back_to_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
void    rl_replace_line(const char *text);

void	env_len(t_shell *shell);
void	init_env(t_shell *shell);
void	create_env(t_shell *shell, char **my_env);

#endif