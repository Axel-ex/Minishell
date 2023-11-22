/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:34:32 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/22 14:35:55 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

void	expander(void);
void	expand_variables(t_token *token);

#endif