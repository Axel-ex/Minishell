/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 15:32:42 by achabrer         ###   ########.fr       */
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

/**
 * @brief check for syntax errors. e.g if first token is not command
 *        if two consecutive tokens are separators
 *        if last token is separator
 * 
 * @param token 
 * @return int exit_status
 */
int		syntax_checker(void);

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

/// ============================================================================
// COMMAND_TABLE.C
// =============================================================================
/**
 * @brief 
 * 
 * @param shell 
 */
void	command_table_generator(t_shell	*shell);

/// ============================================================================
// COMMAND_TABLE_UTILS.C
// =============================================================================
/**
 * @brief trims tokens from their double or simple quotes.
 * 
 * @param token_lst 
 */
void	trim_token(t_token *token_lst);
#endif