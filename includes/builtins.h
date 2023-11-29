/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:12:00 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/29 16:44:32 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**
 * @brief Prints the arguments to the standard output.
 *

	* This function prints the arguments provided in the `ast` structure to the standard output.
 * If the first argument is "-n",
	the newline character is not printed at the end.
 *
 * @param ast The abstract syntax tree containing the arguments.
 * @return Returns EXIT_SUCCESS if the function executes successfully.
 */
int		echo(t_ast *ast);

/**
 * @brief Runs the "env" command, which displays the environment variables.
 *

	* This function scans and prints the key-value pairs of the environment variables.

	* It uses the scanner_env function to iterate through the environment variables.
 *
 * @return Returns EXIT_SUCCESS if the command is executed successfully.
 */
int		run_env(void);

/**

	* @brief Removes environment variables specified by the arguments from the environment list.
 * 
 * @param ast The abstract syntax tree representing the command.
 * @return Returns 0 on success
 */

int		run_unset(t_ast *ast);

/**
 * @brief Removes the current node from a linked list.
 * 
 * @param head The head of the linked list.
 * @param current The node to be removed.
 */

void	remove_current_node(t_list **head, t_list *current);

void	run_export(t_ast *ast);

#endif