/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:10:26 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/11 11:28:13 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_token_type(t_token *token_lst)
{
	t_token	*curr;

	curr = token_lst;
	while (curr)
	{
		if (curr->type == OTHER)
			curr->type = CMD;
		if (curr->type == REDIR_IN)
			curr->next->type = FILE_IN;
		if (curr->type == REDIR_OUT)
			curr->next->type = FILE_TRUNC;
		if (curr->type == REDIR2_IN)
			curr->next->type = HEREDOC;
		if (curr->type == REDIR2_OUT)
			curr->next->type = FILE_APEND;
		curr = curr->next;
	}
}

void	command_table_generator(t_shell	*shell)
{
	trim_token(shell->token);
	split_token_type(shell->token);
}
