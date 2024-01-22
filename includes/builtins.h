/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:12:00 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/22 11:57:00 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**
 * @brief Prints the arguments to the standard output.
 *

 * This function prints the arguments provided in the `ast` structure to 
 * the standard output. If the first argument is "-n", the newline character
 * is not printed at the end.
 *
 * @param ast The abstract syntax tree containing the arguments.
 * @return Returns EXIT_SUCCESS if the function executes successfully.
 */
int		run_echo(t_ast *ast);

/**
 * @brief Runs the "env" command, which displays the environment variables.
 *
 * This function scans and prints the key-value pairs of the environment
 * variables. It uses the scanner_env function to iterate through the 
 * environment variables.
 *
 * @return Returns EXIT_SUCCESS if the command is executed successfully.
 */
int		run_env(void);

/**

 * @brief Removes environment variables specified by the arguments from 
 * the environment list.
 * 
 * @param ast The abstract syntax tree representing the command.
 */

void	run_unset(t_ast *ast);

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
 * It takes an abstract syntax tree (AST) as input and performs the necessary 
 * operations. If no arguments are provided, it prints all the exported 
 * variables. If the first character of the argument is not a letter, it 
 * displays an error message. If the argument contains an equal sign '=',
 * it adds the variable to the environment.
 * 
 * @param ast The abstract syntax tree representing the export command.
 */
void	run_export(t_ast *ast);

/**
 * cd_update_old_pwd - Updates the OLDPWD environment variable with the current 
 * working directory.
 * 
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int		cd_update_old_pwd(void);

/**
 * cd_goto_old_pwd - Changes the current directory to the directory specified by
 * the OLDPWD environment variable.
 * 
 * @return EXIT_SUCCESS on success.
 */
int		cd_goto_old_pwd(void);

/**
 * cd_goto_home - Changes the current directory to the directory specified by
 * the HOME environment variable.
 * 
 * @return EXIT_SUCCESS on success.
 */
int		cd_goto_home(void);

/**
 * run_cd - Changes the current directory based on the arguments provided.
 * 
 * @param ast: The abstract syntax tree containing the arguments.
 * @return EXIT_SUCCESS on success.
 */
int		run_cd(t_ast *ast);

/**
 * @brief prints the current directory.
 * 
 * @return int 
 */
int		run_pwd(void);

/**
 * @brief exit the program.
 * 
 * @param ast 
 */
void	run_exit(t_ast *ast);

#endif