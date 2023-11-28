/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:30:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/28 14:47:47 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redir_in(t_ast *ast)
{
	struct stat	stats;
	char		*file;

	file = ast->args[0];
	if (stat(file, &stats))
		return (print_error(DIR_NT_FD, ERR_DIR, file));
	sh()->fd_in = open(file, O_RDONLY);
	return (EXIT_SUCCESS);
}

void	handle_heredoc(t_ast *ast)
{
	char	*line;
	char	*end_of_file;
	int		fd_temp;

	end_of_file = ast->args[0];
	fd_temp = open("tempfile", O_WRONLY | O_APPEND | O_CREAT, 0666);
	while (ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1) != 0)
	{
		line = readline("> ");
		if (!ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd_temp);
		free(line);
	}
	close(fd_temp);
	fd_temp = open("tempfile", O_RDONLY);
	sh()->fd_in = fd_temp;
}

int	handle_redir(t_ast *ast)
{
	t_ast	*temp;

	temp = ast->left;
	if (!temp)
		return (EXIT_SUCCESS);
	if (temp->token->type == REDIR_OUT)
		sh()->fd_out = open(temp->args[0], O_CREAT | O_TRUNC
			| O_WRONLY, 0777);
	else if (temp->token->type == REDIR2_OUT)
		sh()->fd_out = open(temp->args[0], O_CREAT | O_APPEND
			| O_WRONLY, 0777);
	else if (temp->token->type == REDIR_IN)
	{
		if (handle_redir_in(temp) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (temp->token->type == HEREDOC)
		handle_heredoc(temp);
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
