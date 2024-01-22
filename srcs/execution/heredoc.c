/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:46:14 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/22 11:33:29 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
