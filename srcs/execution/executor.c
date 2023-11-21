/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/21 14:53:56 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	match_cmd(t_ast *ast)
{
	char	**args;

	args = ast->args;
	if (!ft_strncmp("cd", args[0], 3))
		return ;
	else if (!ft_strncmp("echo", args[0], 5))
		echo(args);
	else if (!ft_strncmp("exit", args[0], 5))
		free_shell(false);
	else if (!ft_strncmp("pwd", args[0], 4))
		printf("%s\n", getenv("PWD"));
	else
		execute_cmd(ast);
}

void	execute_fork(t_ast *ast)
{
	sh()->pid = fork();
	if (!sh()->pid)
	{
		pipe_connect(ast->pos);
		redirect_io();
		match_cmd(ast);
		free_shell(false);
	}
	restore_io(ast->pos);
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
	file_name = redir_output(ast);
	if (execve(cmd_path, ast->args, sh()->envp))
		return (print_error(PERM_DENIED, ERR_PERM, file_name));
	free(cmd_path);
	return (EXIT_SUCCESS);
}

void	execute_ast(t_ast *ast)
{
	if (!ast)
		return ;
	execute_ast(ast->left);
	execute_ast(ast->right);
	if (!is_operator(ast->token))
	{
		if (!is_forkable(ast->token->content))
			match_cmd(ast);
		else
			execute_fork(ast);
	}
}

void	executor(void)
{
	int	status;

	status = 127;
	pipe_create();
	execute_ast(sh()->ast);
	while (waitpid(-1, &status, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		sh()->exit_status = WEXITSTATUS(status);
}
