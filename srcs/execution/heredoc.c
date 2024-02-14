/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:46:14 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/31 12:43:27 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc_loop(int fd_temp, char *end_of_file)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (sh()->sigint_flag)
		{
			handle_sigint(line, fd_temp);
			break ;
		}
		if (!line)
		{
			handle_null_line(line, end_of_file);
			break ;
		}
		if (handle_end_of_file(line, end_of_file))
			break ;
		handle_line_processing(line, fd_temp);
	}
}

void	handle_heredoc(t_ast *ast)
{
	char	*end_of_file;
	int		fd_temp;

	end_of_file = ast->args[0];
	fd_temp = open("tempfile", O_WRONLY | O_APPEND | O_CREAT, 0666);
	signal(SIGINT, sigint_handler);
	handle_heredoc_loop(fd_temp, end_of_file);
	if (!sh()->sigint_flag)
	{
		close(fd_temp);
		fd_temp = open("tempfile", O_RDONLY);
		sh()->fd_in = fd_temp;
	}
}
