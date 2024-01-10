/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:30:21 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/10 14:49:56 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redir_error(char *file)
{
	struct stat	stats;

	stat(file, &stats);
	if (!access(file, F_OK) && access(file, X_OK))
		return (print_error(1, PERM_DEN, file));
	else
		return (print_error(DIR_NT_FD, ERR_DIR, file));
}

int	handle_redir(t_ast *ast)
{
	char	*file;

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
		return (handle_redir_error(file));
	return (EXIT_SUCCESS);
}

void	handle_heredoc(t_ast *ast)
{
	char	*line;
	char	*temp;
	char	*end_of_file;
	int		fd_temp;

	end_of_file = ast->args[0];
	fd_temp = open("tempfile", O_WRONLY | O_APPEND | O_CREAT, 0666);
	while (42)
	{
		line = readline("> ");
		if (!ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1))
		{
			free(line);
			break ;
		}
		temp = expand_variable(line);
		free(line);
		ft_putendl_fd(temp, fd_temp);
		free(temp);
	}
	close(fd_temp);
	fd_temp = open("tempfile", O_RDONLY);
	sh()->fd_in = fd_temp;
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
