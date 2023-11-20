/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:02:51 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 15:13:57 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_create(void)
{
	int	i;

	i = -1;
	sh()->pipes = (int **)malloc(sizeof(int *));
	if (!sh()->pipes)
		return ;
	while (++i < sh()->nb_cmds)
	{
		sh()->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(sh()->pipes[i]))
			print_error(errno, "pipe call", NULL);
	}
}

void	pipe_connect(int ast_pos)
{
	if (sh()->nb_cmds < 2)
		return ;
	if (ast_pos)
		sh()->fd_in = sh()->pipes[ast_pos - 1][0];
	if (ast_pos != sh()->nb_cmds)
		sh()->fd_out = sh()->pipes[ast_pos][1];
}

pid_t	execute_forkable(t_ast *ast)
{
	sh()->pid = fork();
	if (!sh()->pid)
	{
		pipe_connect(ast->pos);
		redirect_io();
		execute_cmd(ast);
	}
	restore_io();
	return (sh()->pid);
}
