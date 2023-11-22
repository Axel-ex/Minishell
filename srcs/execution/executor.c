/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:48:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/22 14:41:31 by achabrer         ###   ########.fr       */
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
		echo(ast);
	else if (!ft_strncmp("exit", args[0], 5))
		free_shell(false);
	else if (!ft_strncmp("pwd", args[0], 4))
		printf("%s\n", getenv("PWD"));
	else
		execute_cmd(ast);
}

void	execute_child(t_ast *ast)
{
	char		*cmd_path;

	cmd_path = get_cmd_path(ast->args[0]);
	if (check_cmd_path(cmd_path) != EXIT_SUCCESS)
		return ;
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

	cmd_path = get_cmd_path(ast->args[0]);
	redir_output(ast);
	execve(cmd_path, ast->args, sh()->envp);
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
			execute_child(ast);
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
