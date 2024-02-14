/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:40:41 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/31 12:45:40 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	sh()->sigint_flag = 1;
}

void	handle_sigint(char *line, int fd_temp)
{
	free(line);
	close(fd_temp);
	unlink("tempfile");
}

void	handle_null_line(char *line, char *end_of_file)
{
	ft_putstr_fd("minishell: warning: here-document at", 2);
	ft_putstr_fd("line delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(end_of_file, 2);
	ft_putendl_fd("`)", 2);
	free(line);
}

int	handle_end_of_file(char *line, char *end_of_file)
{
	if (!ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1))
	{
		free(line);
		return (1);
	}
	return (0);
}

void	handle_line_processing(char *line, int fd_temp)
{
	char	*temp;

	temp = expand_variable(line);
	free(line);
	ft_putendl_fd(temp, fd_temp);
	free(temp);
}
