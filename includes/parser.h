/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:41 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 15:25:50 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_token	t_token;

/// ============================================================================
// LEXER.C
// =============================================================================
/**
 * @brief returns a pointer to a token list.
 * 
 * @param line to tokenize
 * @return t_token* 
 */
t_token	*get_token(char *line);

/// ============================================================================
// TOKEN_UTIL.C
// =============================================================================
char	*get_token_content(char *s);
void	add_new_token(t_token *token);

#endif