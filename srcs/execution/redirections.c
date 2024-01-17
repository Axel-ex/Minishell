/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:30:21 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/17 19:41:51 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirection(t_token *token)
{
	if (is_operator(token) && token->type != PIPE)
		return (true);
	return (false);
}

int	handle_redir_error(char *file)
{
	struct stat	stats;

	stat(file, &stats);
	if (!access(file, F_OK) && access(file, X_OK))
		return (print_error(1, PERM_DEN, file));
	if (S_ISDIR(stats.st_mode))
		return(print_error(1, "Is a directory", file));
	return (print_error(1, ERR_DIR, file));
}

int	handle_redir(t_ast *ast, bool *fail_redir)
{
	char	*file;

	if (*fail_redir == true)
		return (EXIT_SUCCESS);
	file = ast->args[0];
	if (ast->token->type == REDIR_OUT)
		sh()->fd_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	else if (ast->token->type == REDIR2_OUT)
		sh()->fd_out = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
	else if (ast->token->type == REDIR_IN)
		sh()->fd_in = open(file, O_RDONLY);
	else if (ast->token->type == HEREDOC)
		handle_heredoc(ast);
	if (sh()->fd_in == -1 || sh()->fd_out == -1)
	{
		*fail_redir = true;
		return (handle_redir_error(file));
	}
	return (EXIT_SUCCESS);
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
	if (node_pos != sh()->nb_cmds - 1)
		close(sh()->pipes[node_pos][1]);
	sh()->fd_in = STDIN_FILENO;
	sh()->fd_out = STDOUT_FILENO;
	unlink("tempfile");
}
