/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:31:57 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/13 14:37:40 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;



/// ============================================================================
// ENV_LST.C
// =============================================================================
/**
 * @brief Get the key from an environment variable string.
 * 
 * @param envp The environment variable string.
 * @return char* The key of the environment variable.
 */
char	*get_key(char *envp);

/**
 * @brief Get the value from an environment variable string.
 * 
 * @param envp The environment variable string.
 * @return char* The value of the environment variable.
 */
char	*get_value(char *envp);

/**
 * @brief Add a new environment variable to the end of the list.
 * 
 * @param key The key of the environment variable.
 * @param value The value of the environment variable.
 */
int	env_add_back(char *key, char *value);

/**
 * @brief Populate the environment variable list from an array of strings.
 * 
 * @param envp The array of environment variable strings.
 */
void	get_env_list(char **envp);

t_env	*env_find(char *key);




/// ============================================================================
// ENV_MANIP.C
// =============================================================================
/**
 * @brief scans trhough the list of environment variable and perform
 * the operatiuon specified by op.
 * 
 * @param op 
 * @return t_env* 
 */
t_env	*scanner_env(t_operation op);

/**
 * @brief Get value of the variable associated with the key in our
 * envlist. equivalent of getenv for our own environment
 * 
 * @param key 
 * @return char* 
 */
char	*getenv_var(char *key);

/**
 * @brief updates the value associated with the key if it exists
 * 
 * @param key 
 * @param new_value 
 * @return int 
 */
int		update_env_if_key_found(char *key, char *new_value);

#endif