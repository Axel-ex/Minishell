/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/14 17:32:29 by achabrer         ###   ########.fr       */
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

int	execute_cmd(t_ast *ast)
{
	char		*cmd_path;
	char		*file_name;
	struct stat	path;

	cmd_path = get_cmd_path(ast->token->content);
	if (!cmd_path)
		return (print_error(CMD_NT_FD, ERR_CMD, ast->token->content));
	stat(cmd_path, &path);
	if (S_ISDIR(path.st_mode))
		return (print_error(DIR_NT_FD, ERR_DIR, cmd_path));
	sh()->pid = fork();
	if (!sh()->pid)
	{
		file_name = redir_output(ast);
		if (execve(cmd_path, ast->args, sh()->envp))
			return (print_error(PERM_DENIED, ERR_PERM, file_name));
	}
	wait(NULL);
	free(cmd_path);
	return (EXIT_SUCCESS);
}

void	executor(t_ast *ast)
{
	if (!is_not_operator(ast->token))
		return ;
		// execute_pipe(ast);
	else
	{
		// if (!exec_builtin(ast))
		// 	return ;
		execute_cmd(ast);
	}
}
