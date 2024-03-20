/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:04:09 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/20 15:06:31 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_UTILS_H
# define EXPORT_UTILS_H

# include "minishell.h"

/**
 * @brief Copies the environment list.
 *
 * This function creates a copy of the environment list passed as a parameter.
 * The copy is stored in the shell's copy_env_lst variable.
 *
 * @param env_list The environment list to be copied.
 */
void	copy_env_list(void);

/**
 * @brief Sorts the copied environment list.
 *
 * This function sorts the copied environment list stored in the shell's
 * copy_env_lst variable. The sorting is done in lexicographical order.
 */
void	sort_copy_env_list(void);

/**
 * @brief Frees the copied environment list.
 *
 * This function frees the memory allocated for the copied environment list
 * stored in the shell's copy_env_lst variable. It also sets the copy_env_lst
 * variable to NULL to indicate that the list has been freed.
 */
void	free_copy_env_lst(void);

#endif