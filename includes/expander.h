/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:34:32 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/22 17:01:50 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/**
 * @file expander.c
 * @brief Functions for expanding variables in tokens.
 */

/**
 * @brief Retrieves the key for variable expansion.
 * 
 * This function takes a pointer to a string and extracts the key for variable expansion.
 * The key consists of alphanumeric characters and underscores.
 * 
 * @param temp A pointer to the string containing the variable.
 * @return The key for variable expansion.
 */
char *get_key_expansion(char **temp);

/**
 * @brief Expands variables in a token's content.
 * 
 * This function expands variables in a token's content by replacing them with their corresponding values.
 * The variables are identified by a dollar sign ($) followed by an alphabetic character.
 * The expanded content is stored in a new string and replaces the original content of the token.
 * 
 * @param token The token to expand variables in.
 */
void expand_variables(t_token *token);

/**
 * @brief Expands variables in the token list.
 * 
 * This function iterates over the token list and expands variables in tokens of type OTHER.
 * It skips tokens of type REDIR2_OUT.
 */
void expander(void);

#endif