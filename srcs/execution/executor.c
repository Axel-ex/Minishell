/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:06 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/16 11:54:28 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	match_cmd(t_ast *ast)
{
	char	**args;

	args = ast->args;
	if (!ft_strncmp("cd", args[0], 3))
		run_cd(ast);
	else if (!ft_strncmp("echo", args[0], 5))
		run_echo(ast);
	else if (!ft_strncmp("exit", args[0], 5))
		run_exit(ast);
	else if (!ft_strncmp("pwd", args[0], 4))
		run_pwd();
	else if (!ft_strncmp("env", args[0], 3))
		run_env();
	else if (!ft_strncmp("unset", args[0], 6))
		run_unset(ast);
	else if (!ft_strncmp("export", args[0], 7))
		run_export(ast);
	else
		execute_cmd(ast);
}

void	execute_child(t_ast *ast)
{
	check_cmd_path(ast->args[0]);
	sh()->pid = fork();
	if (!sh()->pid)
	{
		if (sh()->fd_in == -1 || sh()->fd_out == -1)
			free_shell(false);
		pipe_connect(ast->pos);
		redirect_io();
		match_cmd(ast);
		free_shell(false);
	}
	restore_io(ast->pos);
}

void	execute_cmd(t_ast *ast)
{
	char		*cmd_path;

	cmd_path = get_cmd_path(ast->args[0]);
	execve(cmd_path, ast->args, sh()->envp);
	free(cmd_path);
}

void	execute_ast(t_ast *ast)
{
	static bool	fail_redir = false;

	if (!ast)
		return ;
	execute_ast(ast->left);
	execute_ast(ast->right);
	if (!is_operator(ast->token))
	{
		if (!is_forkable(ast->token->content))
			match_cmd(ast);
		else
			execute_child(ast);
		fail_redir = false;
	}
	else if (is_redirection(ast->token))
		handle_redir(ast, &fail_redir);
}

void	executor(void)
{
	int	status;

	status = 127;
	pipe_create();
	execute_ast(sh()->ast);
	while (wait(&status) > 0)
		continue ;
	if (WIFEXITED(status))
		sh()->exit_status = WEXITSTATUS(status);
}
