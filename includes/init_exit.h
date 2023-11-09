/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:41:58 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 12:44:57 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_EXIT_H
# define INIT_EXIT_H

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

/// ============================================================================
// INIT.C
// =============================================================================
t_token	**init_token(char **line);
t_shell	*init_shell(void);

/// ============================================================================
// ERROR.C
// =============================================================================
/**
 * @brief prints the msg pointed to by *msg and return EXIT_FAILURE.
 * 
 * @param msg to_print 
 */
int		print_error(char *msg);

/**
 * @brief prints the msg pointed to by *msg and return NULL.
 * 
 * @param msg to print
 * @return void* NULL
 */
void	*alloc_error(char *msg);

/// ============================================================================
// FREE.C
// =============================================================================
void	free_shell(t_shell *shell, bool keep_iterating);
void	free_tokens(t_token	**token);
void	free_matrix(char **matrix);

#endif