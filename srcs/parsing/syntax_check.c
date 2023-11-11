/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:19:03 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/10 21:55:04 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_checker(t_token *token)
{
	t_token	*temp;
	t_token	*next;

	temp = token;
	if (temp->type != OTHER)
		return (print_error("Syntax Error : First token should be a command",
				20));
	while (temp && temp->next)
	{
		next = temp->next;
		if (temp->type != OTHER && next->type != OTHER)
			return (print_error("Syntax Error : unexpected sequence of tokens",
					20));
		temp = temp->next;
	}
	if (temp->type != OTHER)
		return (print_error("Syntax Error: Prompt should not end as separator",
				20));
	return (EXIT_SUCCESS);
}
