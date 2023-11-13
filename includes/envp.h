/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:31:57 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/13 17:32:17 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

typedef struct s_env	t_env;

/**
 * @brief Copies the key and content from an environment variable to a t_env structure.
 *
 * This function calculates the length of the key, allocates memory for the key and
 * content arrays, copies the key and content, and ensures proper null-termination.
 *
 * @param env   Pointer to the t_env structure.
 * @param equals Pointer to the '=' character in the environment variable.
 * @param index Index of the current environment variable.
 */
void    copy_key_content(t_env *env, char *equals, int index);

/**
 * @brief Populates the t_env structure with keys and contents from environment variables.
 *
 * This function determines the length of the environment variables, allocates memory
 * for the key and content arrays, and uses copy_key_content to populate the structure.
 *
 * @param env Pointer to the t_env structure to be populated.
 */
void    populate_env_struct(t_env *env);

/**
 * @brief Frees the memory allocated for keys and contents in the t_env structure.
 *
 * This function iterates through the keys and contents, freeing their allocated memory,
 * and then frees the arrays containing keys and contents.
 *
 * @param env Pointer to the t_env structure.
 */
void    free_memory(t_env *env);

/**
 * @brief Determines the length of the environment variable array.
 *
 * This function calculates the length of the environment variable array by counting
 * elements until a NULL terminator is encountered.
 *
 * @param env Pointer to the t_env structure containing the environment variables.
 */
void    env_len(t_env *env);

/**
 * @brief Allocates memory for key and content arrays in the t_env structure.
 *
 * This function allocates memory for the key and content arrays based on the length
 * of the environment variable array in the t_env structure.
 *
 * @param env Pointer to the t_env structure.
 */
void    allocate_memory(t_env *env);


#endif