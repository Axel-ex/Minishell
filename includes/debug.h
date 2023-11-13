/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:02:07 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 15:04:05 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef enum s_type		t_type;

/// ============================================================================
// TOKEN.C
// =============================================================================
void	print_token_content(t_token *token);

char	*get_type(t_type type);

/**
 * @brief print the contents of the tokens.
 * 
 * @param token list to print
 */
void	print_token_lst(void);

void	print_ast(t_ast *ast, int position);
#endif