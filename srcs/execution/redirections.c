/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:30:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 14:36:53 by achabrer         ###   ########.fr       */
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

void	restore_io(void)
{
	if (sh()->fd_in != STDIN_FILENO)
		close(sh()->fd_in);
	if (sh()->fd_out != STDOUT_FILENO)
		close(sh()->fd_out);
	sh()->fd_in = STDIN_FILENO;
	sh()->fd_out = STDOUT_FILENO;
}