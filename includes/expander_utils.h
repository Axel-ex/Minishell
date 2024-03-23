/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Axel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:59 by Axel              #+#    #+#             */
/*   Updated: 2024/03/23 20:01:02 by Axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

# include "minishell.h"

void	free_resources(char *old_res, char *key, char *value);
char	*expand_variable(char *cnt);
int		count_first_quote(char *cnt);
char	*get_key_exp(char *cnt);
char	*replace_var(char *cnt, char *key, char *value);

#endif
