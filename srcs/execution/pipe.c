/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:02:51 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/17 15:37:21 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_create(void)
{
	int	i;

	i = -1;
	sh()->pipes = ft_calloc(sizeof(int *), sh()->nb_cmds);
	if (!sh()->pipes)
		return ;
	while (++i < sh()->nb_cmds)
	{
		sh()->pipes[i] = ft_calloc(sizeof(int), 2);
		if (pipe(sh()->pipes[i]))
			print_error(errno, "pipe call", NULL);
	}
}

void	pipe_connect(int ast_pos)
{
	if (sh()->nb_cmds < 2)
		return ;
	if (ast_pos && sh()->fd_in == STDIN_FILENO)
	{
		sh()->fd_in = sh()->pipes[ast_pos - 1][0];
		close(sh()->pipes[ast_pos - 1][1]);
	}
	if (ast_pos != sh()->nb_cmds - 1 && sh()->fd_out == STDOUT_FILENO)
	{
		sh()->fd_out = sh()->pipes[ast_pos][1];
		close(sh()->pipes[ast_pos][0]);
	}
}
