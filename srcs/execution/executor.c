/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 15:20:12 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	file_name = redir_output(ast);
	if (execve(cmd_path, ast->args, sh()->envp))
		return (print_error(PERM_DENIED, ERR_PERM, file_name));
	free(cmd_path);
	return (EXIT_SUCCESS);
}

pid_t	execute_ast(t_ast *ast)
{
	pid_t	last_child;

	if (!ast)
		return (-1);
	last_child = execute_ast(ast->left);
	last_child = execute_ast(ast->right);
	if (!is_operator(ast->token))
	{
		if (!is_forkable(ast->token->content))
			match_cmd(ast);
		else
			last_child = execute_forkable(ast);
	}
	return (last_child);
}

void	executor(void)
{
	pid_t	last_child;
	int		status;

	status = 0;
	pipe_create();
	last_child = execute_ast(sh()->ast);
	last_child = waitpid(last_child, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	if (WIFEXITED(status))
		sh()->exit_status = WEXITSTATUS(status);
}
