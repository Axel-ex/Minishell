/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:12:00 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/30 14:08:11 by jgomes-v         ###   ########.fr       */
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

/**
 * @brief Runs the export command.
 * 
 * This function is responsible for executing the export command in the shell.
 * It takes an abstract syntax tree (AST) as input and performs the necessary operations.
 * If no arguments are provided, it prints all the exported variables.
 * If the first character of the argument is not a letter, it displays an error message.
 * If the argument contains an equal sign '=', it adds the variable to the environment.
 * 
 * @param ast The abstract syntax tree representing the export command.
 */
void	run_export(t_ast *ast);

int	cd_goto_old_pwd(void);

/**
 * @brief Updates the value of an environment variable if the key is found.
 *
 * This function searches for an environment variable with the specified key
 * and updates its value with the new value provided. If the key is found,
 * the function returns EXIT_SUCCESS. Otherwise, it returns EXIT_FAILURE.
 *
 * @param key The key of the environment variable to update.
 * @param new_value The new value to assign to the environment variable.
 * @return int Returns EXIT_SUCCESS if the key is found and the value is updated,
 *         otherwise returns EXIT_FAILURE.
 */
int update_if_key_found(char *key, char *new_value);

/**
 * cd_get_path - Returns the value of the environment variable specified by key.
 * @param key: The key of the environment variable.
 * @return The value of the environment variable.
 */
char	*cd_get_path(char *key);

/**
 * cd_update_old_pwd - Updates the OLDPWD environment variable with the current working directory.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	cd_update_old_pwd(void);

/**
 * cd_goto_old_pwd - Changes the current directory to the directory specified by the OLDPWD environment variable.
 * @return EXIT_SUCCESS on success.
 */
int	cd_goto_old_pwd(void);

/**
 * cd_goto_home - Changes the current directory to the directory specified by the HOME environment variable.
 * @return EXIT_SUCCESS on success.
 */
int	cd_goto_home(void);

/**
 * run_cd - Changes the current directory based on the arguments provided.
 * @param ast: The abstract syntax tree containing the arguments.
 * @return EXIT_SUCCESS on success.
 */
int	run_cd(t_ast *ast);

int	run_pwd(void);

#endif