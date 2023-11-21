/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:30:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/21 14:33:24 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*redir_output(t_ast *ast)
{
	t_ast	*temp;

	temp = ast->left;
	if (!temp)
		return (NULL);
	if (temp->token->type == REDIR_OUT)
	{
		sh()->fd_out = open(ast->left->args[0], O_CREAT | O_TRUNC
			| O_WRONLY, 0777);
		if (!sh()->fd_out)
			return (NULL);
	}
	else if (temp->token->type == REDIR2_OUT)
	{
		sh()->fd_out = open(ast->left->args[0], O_CREAT | O_APPEND
			| O_WRONLY, 0777);
		if (!sh()->fd_out)
			return (NULL);
	}
	dup2(sh()->fd_out, STDOUT_FILENO);
	return (ast->left->args[0]);
}

void	redirect_io(void)
{
	dup2(sh()->fd_in, STDIN_FILENO);
	dup2(sh()->fd_out, STDOUT_FILENO);
}

void	restore_io(int node_pos)
{
	if (sh()->fd_in > STDIN_FILENO)
		close(sh()->fd_in);
	if (sh()->fd_out > STDOUT_FILENO)
		close(sh()->fd_out);
	if (node_pos > 0)
		close(sh()->pipes[node_pos - 1][0]);
	if (node_pos == sh()->nb_cmds - 1 && sh()->nb_cmds > 1)
		close(sh()->pipes[node_pos -1][1]);
	sh()->fd_in = STDIN_FILENO;
	sh()->fd_out = STDOUT_FILENO;
}
