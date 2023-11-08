/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 15:33:27 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_token(t_token *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->next = NULL;
	token->next = new;
}
