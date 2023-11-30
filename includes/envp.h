/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:31:57 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/30 13:32:13 by jgomes-v         ###   ########.fr       */
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
void	env_add_back(char *key, char *value);

/**
 * @brief Populate the environment variable list from an array of strings.
 * 
 * @param envp The array of environment variable strings.
 */
void	get_env_list(char **envp);

char	*getenv_var(char *key);

t_env	*scanner_env(t_operation op);

int	update_env_if_key_found(char *key, char *new_value);


#endif