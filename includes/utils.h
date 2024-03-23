/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:03:26 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/23 20:03:35 by Axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

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

/**
 * @brief removes empty arguments from the beggining of the matrix.
 * 
 * @param mat 
 * @return char** cleaned matrix
 */
char	**matrix_cleaner(char **mat);

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
char	*remove_quotes(char *cnt);

/**
 * @brief Get the first occuring quote to remove quotes of the line
 * 
 * @param line 
 * @return char 
 */
char	get_first_quote(char *content);

/**
 * @brief assess if the char c is a quote.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool	is_quote(char c);

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

/**
 * @brief merge the string to_append to the content of the lastly added
 * token.
 * 
 * @param to_append 
 */
void	token_content_append(char *to_append);

/// ============================================================================
// EXECUTOR_UTIL.C
// =============================================================================
/**
 * @brief check cmd path and set exit_status accordingly
 * 
 * @param cmd 
 * @return int 
 */
int		check_cmd_path(char *cmd);

/**
 * @brief check if the token is an operator
 * 
 * @param token 
 * @return true 
 * @return false 
 */
bool	is_operator(t_type type);

/**
 * @brief Get the cmd path, either absolute or relative
 * 
 * @param cmd 
 * @return char* 
 */
char	*get_cmd_path(char *cmd);

/**
 * @brief check if a command is forkable. non forkable are command
 * that need to be executed by the main process for it's changes to be
 * reflected in the program
 * 
 * @param cmd 
 * @return true 
 * @return false 
 */
bool	is_forkable(char *cmd);

/// ============================================================================
// CAT_HELPER.C
// =============================================================================
/**
 * @brief check if the pipeline contains only cat.
 * 
 * @return true 
 * @return false 
 */
bool	only_cats(void);

/**
 * @brief count the number of cat command in the token list.
 * 
 * @return int 
 */
int		count_cat(void);

/**
 * @brief handle signal when prompt hangs for cat.
 * 
 * @param signo 
 */
void	sigint_hand(int signo);

/**
 * @brief print a new line on ENTER press.
 * 
 * @param cat_count 
 */

/// ============================================================================
// DEBUG
// =============================================================================
/**
 * @brief print the type and content of a token.
 * 
 * @param token 
 */
void	print_token_content(t_token *token);

/**
 * @brief Get the type of a token
 * 
 * @param type 
 * @return char* 
 */
char	*get_type(t_type type);

/**
 * @brief print the contents of the tokens.
 * 
 * @param token list to print
 */
void	print_token_lst(void);

/**
 * @brief prints the ast structure.
 * 
 * @param ast 
 * @param position 
 */
void	print_ast(t_ast *ast, int position);

/// ============================================================================
// SIGNALS.C
// =============================================================================
void	rl_replace_line(const char *text, int clear_undo);
void	signals(int sig);
//void	back_to_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);

/// ============================================================================
// EXPORT_UTILS.C
// =============================================================================
/**
 * @brief Copies the environment list.
 *
 * This function creates a copy of the environment list passed as a parameter.
 * The copy is stored in the shell's copy_env_lst variable.
 *
 * @param env_list The environment list to be copied.
 */
void	copy_env_list(void);

/**
 * @brief Sorts the copied environment list.
 *
 * This function sorts the copied environment list stored in the shell's
 * copy_env_lst variable. The sorting is done in lexicographical order.
 */
void	sort_copy_env_list(void);

/**
 * @brief Frees the copied environment list.
 *
 * This function frees the memory allocated for the copied environment list
 * stored in the shell's copy_env_lst variable. It also sets the copy_env_lst
 * variable to NULL to indicate that the list has been freed.
 */
void	free_copy_env_lst(void);

/// ============================================================================
// HEREDOC_UTILS.C
// =============================================================================
void	handle_hang(int cat_count);
void	sigint_handler(int sig);
void	handle_sigint(char *line, int fd_temp);
void	handle_null_line(char *line, char *end_of_file);
int		handle_end_of_file(char *line, char *end_of_file);
void	handle_line_processing(char *line, int fd_temp);

/// ============================================================================
// EXPANDER_UTILS.C
// =============================================================================
void	free_resources(char *old_res, char *key, char *value);
char	*expand_variable(char *cnt);
int		count_first_quote(char *cnt);
char	*get_key_exp(char *cnt);
char	*replace_var(char *cnt, char *key, char *value);

#endif
